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
  
  int n;
  int root;
  
public:
  const vector<pair<int, T>> &getAdjacent(int u) const { return adj[u]; }
  
  void reset(int size) {
    this->n = size;
    adj.resize(n + 1);
    for_inc_range(i, 1, n) adj[i].clear();
    p.resize(n + 1);
    depth.resize(n + 1);
    for_inc_range(i, 1, n) {
      p[i] = make_pair(-1, -1);
      depth[i] = 0;
    }
  }
  
  WeightedTree() {}
  
  WeightedTree(int n) { reset(n); }
  
  void dfs(int u) {
    stack<int> node;
    node.push(u);
    while (!node.empty()) {
      u = node.top();
      node.pop();
      for (auto &e : adj[u]) {
        int v = e.first;
        int c = e.second;
        if (p[v].first == -1) {
          p[v] = make_pair(u, c);
          depth[v] = depth[u] + 1;
          node.push(v);
        }
      }
    }
  }
  
  int getParent(int u) const { return p[u].first; }
  
  T getWeight(int u) const { return p[u].second; }
  
  void setWeight(int u, T w) { p[u].second = w; }
  
  int getDepth(int u) const { return depth[u]; }
  
  size_t getSize() const { return n; }
  
  int getRoot() const { return root; }
  
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
  
  Q queryAncestor(int u, int k) {
    assert(0 <= k && k <= t.getDepth(u));
    if (k == 0) {
      return u;
    }
    int b = 0;
    while ((1 << b) <= k) ++b;
    --b;
    return combine(anc[u][b].second, queryAncestor(anc[u][b].first, k - (1 << b)));
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

class BinarySearch {
public:
  template<class T> static T binarySearchMin(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = maxIndex + 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        rightIndex = midIndex - 1;
      } else {
        leftIndex = midIndex + 1;
      }
    }
    return ret;
  }
  
  template<class T> static T binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = minIndex - 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        leftIndex = midIndex + 1;
      } else {
        rightIndex = midIndex - 1;
      }
    }
    return ret;
  }
  
  static double binarySearchMaxReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        ret = m;
        l = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
  static double binarySearchMinReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        l = m;
        ret = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
};

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  int64 need;
  cin >> n >> need;
  
  vector<int> weight(n + 1);
  for_inc_range(i, 1, n) {
    cin >> weight[i];
  }
  
  WeightedTree<int> tree(n + 1);
  for_inc_range(i, 2, n) {
    int p;
    cin >> p;
    tree.addEdge(p, i, weight[i]);
  }
  tree.addEdge(1, n + 1, weight[1]);
  tree.setRoot(n + 1);
  
  auto initial = [](const WeightedTree<int> &tree, int u) {return tree.getWeight(u);};
  auto combine = [](int64 a, int64 b) {return a + b;};
  
  LowestCommonAncestor<int, int64> lca(tree, initial, combine);
  
  int best = INT_INF;
  int bestP = -1;
  
  for_inc_range(u, 1, n) {
    int d = tree.getDepth(u);
    int ans = BinarySearch::binarySearchMin<int>(0, d, [&](int k) {return lca.queryAncestor(u, k) >= need;});
    if (ans != d + 1) {
      if (ans - 1 < best) {
        best = ans - 1;
        bestP = u;
      }
    }
  }
  
  cout << bestP << endl;
  return 0;
}
