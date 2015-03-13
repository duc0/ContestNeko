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

void testGen() {
  freopen("biginput2.txt", "w", stdout);
  
  int n = 100000;
  int q = 100000;
  cout << n << endl;
  int u = 2;
  repeat(n - 1) {
    int r = rand() % (u - 1) + 1;
    cout << r << " " << u << endl;
    u++;
  }
  
  cout << q << endl;
  repeat(q) {
    if (rand() % 2 == 1) {
      int u = rand() % n + 1;
      int v = rand() % 20000 - 10000;
      cout << "add " << u << " " << v << endl;
    } else {
      int u = rand() % n + 1;
      int v = rand() % n + 1;
      cout << "max " << u << " " << v << endl;
    }
  }
  fclose(stdout);
}


vector<int> value;
WeightedTree<int> tree;

void dfsUpdate(int u, int val) {
  value[u] += val;
  for (auto &v: tree.getAdjacent(u)) {
    if (v.first != tree.getParent(u)) {
      dfsUpdate(v.first, val);
    }
  }
}

vector<bool> visit;

int queryMax(int u, int target) {
  visit[u] = true;
  if (u == target) {
    return value[u];
  }
  int best = -INT_INF;
  for (auto &v: tree.getAdjacent(u)) if (!visit[v.first]) {
    best = max(best, queryMax(v.first, target));
  }
  if (best == -INT_INF) {
    return best;
  }
  best = max(best, value[u]);
  return best;
}

// SPOJ QTREE3
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input5.txt", "r", stdin);
  freopen("input5.out.slow", "w", stdout);
#endif
  
  int n;
  scanf("%d", &n);
  
  tree.reset(n);
  vector<pair<int, int>> edge;
  
  repeat(n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree.addEdge(u, v, 1);
    edge.push_back(make_pair(u, v));
  }
  tree.setRoot(1);
  
  int q;
  scanf("%d", &q);
  char s[10];
  value.resize(n + 1);
  visit.resize(n + 1);
  repeat(q) {
    scanf("%s", s);
    if (s[0] == 'a') {
      int u, val;
      scanf("%d%d", &u, &val);
      dfsUpdate(u, val);
    } else {
      int u, v;
      scanf("%d%d", &u, &v);
      fill(visit.begin(), visit.end(), false);
      int res = queryMax(u, v);
      printf("%d\n", res);
    }
  }
  return 0;
}
