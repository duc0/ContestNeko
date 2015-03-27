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
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cfloat>
#include <random>

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
public:
  const vector<pair<int, T>> &getAdjacent(int u) const { return adj[u]; }
  
  void reset(int size) {
    this->n = size;
    adj.resize(n + 1);
    for_inc_range(i, 1, n) adj[i].clear();
    p.resize(n + 1);
    depth.resize(n + 1);
    root = -1;
    for_inc_range(i, 1, n) {
      p[i] = make_pair(-1, -1);
      depth[i] = 0;
    }
  }
  
  WeightedTree() {}
  
  WeightedTree(int n) { reset(n); }
  
  int getParent(int u) const { assert(root != -1); return p[u].first; }
  
  T getWeight(int u) const { assert(root != -1); return p[u].second; }
  
  void setWeight(int u, T w) { assert(root != -1); p[u].second = w; }
  
  int getDepth(int u) const { assert(root != -1); return depth[u]; }
  
  size_t getSize() const { return n; }
  
  int getRoot() const { assert(root != -1); return root; }
  
  void setRoot(int u) {
    for_inc_range(v, 1, n) {
      p[v].first = -1;
    }
    root = u;
    p[root].first = -2;
    dfs(root);
  }
  
  void addEdge(int u, int v, T c) {
    adj[u].emplace_back(v, c);
    adj[v].emplace_back(u, c);
  }
};

template <class T> class CentroidDecomposition {
  const WeightedTree<T> &tree;
  vector<int> label;
  int centroid;
  vector<bool> erased;
  int n;
  vector<int> subtreeSize;
  
  void dfs(int parent, int u) {
    subtreeSize[u] = 1;
    for (auto &v: tree.getAdjacent(u)) {
      if (!erased[v.first] && v.first != parent) {
        dfs(u, v.first);
        subtreeSize[u] += subtreeSize[v.first];
      }
    }
  }
  
  int findCentroid(int x) {
    dfs(-1, x);
    
    int u = x;
    int parent = -1;
    
    while (1) {
      int maxSubtreeSize = 0;
      int maxSubtreeRoot = -1;
      for (auto &v: tree.getAdjacent(u)) {
        if (!erased[v.first] && v.first != parent && subtreeSize[v.first] > maxSubtreeSize) {
          maxSubtreeSize = subtreeSize[v.first];
          maxSubtreeRoot = v.first;
        }
      }
      if (maxSubtreeSize <= subtreeSize[x]/2) {
        return u;
      }
      parent = u;
      u = maxSubtreeRoot;
    }
  }
  
  int decompose(int x, int currentLayer) {
    int centroid = findCentroid(x);
    
    label[centroid] = currentLayer;
    erased[centroid] = true;
    for (auto &v: tree.getAdjacent(centroid)) {
      if (!erased[v.first]) {
        decompose(v.first, currentLayer + 1);
      }
    }
    return centroid;
  }
public:
  CentroidDecomposition(const WeightedTree<T> &tree): tree(tree) {
    n = (int)tree.getSize();
    erased.resize(n + 1);
    subtreeSize.resize(n + 1);
    label.resize(n + 1);
    centroid = decompose(1, 1);
  }
  
  int getCentroid() const {
    return centroid;
  }
  
  int getLabel(int u) const {
    assert(1 <= u && u <= tree.getSize());
    return label[u];
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  
  int n = 100000;
  cout << n << endl;
  for_inc_range(i, 1, n - 2) {
    cout << i << " " << i + 1 << endl;
  }
  fclose(stdout);
}


// Example: CF 190 - C

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("biginput1.txt", "r", stdin);
#endif
  
  WeightedTree<int> tree;
  int n;
  cin >> n;
  
  tree.reset(n);
  repeat(n - 1) {
    int u, v;
    cin >> u >> v;
    tree.addEdge(u, v, 1);
  }
  tree.setRoot(1);
  
  CentroidDecomposition<int> cd(tree);
  
  //cout << cd.getCentroid() << endl;
  for_inc_range(u, 1, n) {
    LOG(1, cd.getLabel(u));
  }
  
  for_inc_range(u, 1, n) {
    cout << (char)(cd.getLabel(u) - 1 + 'A') << " ";
  }
  return 0;
}
