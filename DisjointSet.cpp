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
#include <sstream>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)
#define pair(x, y) make_pair(x, y)
#define _1 first
#define _2 second

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
  vector<T> dist;
  
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
    dist.resize(n + 1);
    for_inc_range(i, 1, n) {
      p[i] = make_pair(-1, -1);
      depth[i] = 0;
      dist[i] = 0;
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
          dist[v] = dist[u] + e.second;
          node.push(v);
        }
      }
    }
  }
  
  T getDist(int u) const {return dist[u];}
  
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
    dist[root] = 0;
    dfs(root);
  }
  
  void addEdge(int u, int v, int c) {
    adj[u].push_back(make_pair(v, c));
    adj[v].push_back(make_pair(u, c));
  }
};

class DisjointSet {
  int n;
  vector<int> parent;
public:
  DisjointSet(int n) {
    this->n = n;
    parent.resize(n + 1);
    for_inc_range(i, 1, n) {
      parent[i] = i;
    }
  }
  
  int getRoot(int u) {
    if (parent[u] == u) {
      return u;
    } else {
      return parent[u] = getRoot(parent[u]);
    }
  }
  
  void merge(int u, int v) {
    parent[getRoot(u)] = getRoot(v);
  }
  
  bool inSameSet(int u, int v) {
    return getRoot(u) == getRoot(v);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

vector<vector<int>> d;

vector<pair<int, pair<int, int>>> edge;

// CF 270 - D
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input5.txt", "r", stdin);
#endif
  int n;
  scanf("%d", &n);
  d.resize(n + 1);
  for_inc_range(u, 1, n) {
    d[u].resize(n + 1);
    for_inc_range(v, 1, n) {
      scanf("%d", &d[u][v]);
      
      if (u == v && d[u][v] != 0) {
        cout << "NO" << endl;
        exit(0);
      }
      if (u != v && d[u][v] == 0) {
        cout << "NO" << endl;
        exit(0);
      }
      
      edge.push_back(pair(d[u][v], pair(u, v)));
    }
  }
  
  for_inc_range(u, 1, n) {
    for_inc_range(v, 1, n) {
      if (d[u][v] != d[v][u]) {
        cout << "NO" << endl;
        exit(0);
      }
    }
  }
  
  sort(edge.begin(), edge.end());
  DisjointSet ds(n);
  WeightedTree<int> tree(n);
  
  for (auto &e: edge) {
    int u = e._2._1;
    int v = e._2._2;
    if (!ds.inSameSet(u, v)) {
      ds.merge(u, v);
      tree.addEdge(u, v, e._1);
      LOG(1, u << " " << v);
    }
  }
  
  for_inc_range(u, 1, n) {
    tree.setRoot(u);
    
    for_inc_range(v, 1, n) {
      if (tree.getDist(v) != d[u][v]) {
        cout << "NO" << endl;
        exit(0);
      }
    }
  }
  
  cout << "YES" << endl;
  return 0;
}
