//#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <array>
#include <type_traits>
#include <queue>
#include <stack>
#include <functional>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Weighted undirected tree
template <class T> class WeightedTree {
  vector<vector<pair<int, T>>> adj;
  
  // p [u] = parent of u and weight p[u] -> u
  vector<pair<int, T>> p;
  
  vector<int> depth;
  vector<int> subtreeSize;
  
  int n;
  int root;
  
public:
  vector<pair<int, T>> &getAdjacent(int u) { return adj[u]; }
  
  void reset(int size) {
    this->n = size;
    adj.resize(n + 1);
    for_inc_range(i, 1, n) adj[i].clear();
    p.resize(n + 1);
    depth.resize(n + 1);
    subtreeSize.resize(n + 1);
    for_inc_range(i, 1, n) {
      p[i] = make_pair(-1, -1);
      depth[i] = 0;
      subtreeSize[i] = 0;
    }
  }
  
  WeightedTree() {}
  
  WeightedTree(int n) { reset(n); }
  
  void dfs(int u) {
    subtreeSize[u] = 1;
    for (auto &e : adj[u]) {
      int v = e.first;
      int c = e.second;
      if (p[v].first == -1) {
        p[v] = make_pair(u, c);
        depth[v] = depth[u] + 1;
        dfs(v);
        subtreeSize[u] += subtreeSize[v];
      }
    }
  }
  
  int getParent(int u) { return p[u].first; }
  
  T getWeight(int u) { return p[u].second; }
  
  int getDepth(int u) { return depth[u]; }
  
  int getSubtreeSize(int u) {return subtreeSize[u];}
  
  size_t getSize() { return n; }
  
  int getRoot() { return root; }
  
  void setRoot(int u) {
    for_inc_range(v, 1, n) {
      p[v].first = -1;
    }
    root = u;
    p[root].first = -2;
    dfs(root);
  }
  
  void addEdge(int u, int v, int c) {
    adj[u].push_back(make_pair(v, c));
    adj[v].push_back(make_pair(u, c));
  }
};

// LCA O(logn)
template <class T, class Q> class LowestCommonAncestor {
  // anc[i][j] = ancestor 2^j dist away from i and a combined value generated
  // from the path from i to that ancestor,
  // default to the min weight
  vector<vector<pair<int, Q>>> anc;
  WeightedTree<T> &t;
  function<Q(Q, Q)> combine;
  
public:
  LowestCommonAncestor(WeightedTree<T> &tree)
  : LowestCommonAncestor(
                         tree, [](WeightedTree<T> &t, int u) { return t.getWeight(u); },
                         [](Q a, Q b) { return min(a, b); }) {}
  
  LowestCommonAncestor(WeightedTree<T> &tree,
                       const function<Q(WeightedTree<T> &, int)> &getInitial,
                       const function<Q(Q, Q)> &combine)
  : t(tree), combine(combine) {
    anc.resize(t.getSize() + 1);
    for_inc_range(i, 1, t.getSize()) {
      if (i != t.getRoot()) {
        anc[i].push_back(make_pair(t.getParent(i), getInitial(t, i)));
      }
    }
    for (int k = 1;; ++k) {
      bool ok = false;
      for_inc_range(i, 1, t.getSize()) {
        if (anc[i].size() >= k) {
          int j = anc[i][k - 1].first;
          if (anc[j].size() >= k) {
            int x = anc[j][k - 1].first;
            anc[i].push_back(make_pair(
                                       x, combine(anc[i][k - 1].second, anc[j][k - 1].second)));
            ok = true;
          }
        }
      }
      if (!ok)
        break;
    }
  }
  
  // Get the kth ancestor of k, t = 0 .. depth[u]
  int getAncestor(int u, int k) {
    assert(0 <= k && k <= t.getDepth(u));
    if (k == 0) {
      return u;
    }
    int b = 0;
    while ((1 << b) <= k) ++b;
    --b;
    return getAncestor(anc[u][b].first, k - (1 << b));
  }
  
  pair<int, T> getLCA(int u, int v) {
    if (t.getDepth(u) > t.getDepth(v)) {
      swap(u, v);
    }
    if (t.getDepth(v) > t.getDepth(u)) {
      for_dec(i, anc[v].size()) {
        int w = anc[v][i].first;
        if (t.getDepth(w) >= t.getDepth(u)) {
          pair<int, T> p = getLCA(u, w);
          p.second = min(anc[v][i].second, p.second);
          return p;
        }
      }
    } else { // depth[v] == depth[u]
      if (u == v) {
        return make_pair(u, INT_INF);
      }
      for_dec(i, anc[u].size()) {
        int x = anc[u][i].first;
        int y = anc[v][i].first;
        if (x != y || i == 0) {
          pair<int, T> p = getLCA(x, y);
          p.second = combine(anc[u][i].second, p.second);
          p.second = combine(anc[v][i].second, p.second);
          return p;
        }
      }
    }
    return make_pair(-1, -1);
  }
};

WeightedTree<int> tree;

int main() {
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  int n;
  cin >> n;
  tree.reset(n);
  int a, b;
  repeat(n - 1) {
    cin >> a >> b;
    tree.addEdge(a, b, 1);
  }
  tree.setRoot(1);
  
  
  LowestCommonAncestor<int, int> lca(tree);
  
  int q, u, v;
  cin >> q;
  
  repeat(q) {
    cin >> u >> v;
    if (u == v) {
      cout << n  << endl;
      continue;
    }
    int common = lca.getLCA(u, v).first;
    int dist = tree.getDepth(u) + tree.getDepth(v) - 2 * tree.getDepth(common);
    if (dist % 2 == 1) {
      cout << 0 << endl;
    } else {
      if (tree.getDepth(u) < tree.getDepth(v)) swap(u, v);
      int bh = lca.getAncestor(u, dist/2 - 1);
      int h = tree.getParent(bh);
      int ret = 0;
      ret += tree.getSubtreeSize(h);
      ret -= tree.getSubtreeSize(bh);
      if (h == common) {
        int vh = lca.getAncestor(v, dist/2 - 1);
        ret += n - tree.getSubtreeSize(common);
        ret -= tree.getSubtreeSize(vh);
      }
      cout << ret << endl;
    }
  }
  return 0;
}
