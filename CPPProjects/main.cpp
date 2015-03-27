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

template<class T> class SubtreeSize {
  const WeightedTree<T> &tree;
  vector<int> subtreeSize;
  vector<bool> visit;
  
  void dfs(int u) {
    stack<int> node;
    node.push(u);
    while (!node.empty()) {
      u = node.top();
      if (visit[u]) {
        node.pop();
        subtreeSize[u] = 1;
      }
      for (auto &v: tree.getAdjacent(u)) {
        if (v.first != tree.getParent(u)) {
          if (!visit[u]) {
            node.push(v.first);
          } else {
            subtreeSize[u] += subtreeSize[v.first];
          }
        }
      }
      visit[u] = true;
    }
  }
  
public:
  SubtreeSize(const WeightedTree<T> &tree): tree(tree) {
    subtreeSize.resize(tree.getSize() + 1);
    visit.resize(tree.getSize() + 1);
    dfs(tree.getRoot());
  }
  
  const int operator[](int u) const {
    assert(1 <= u && u <= tree.getSize());
    return subtreeSize[u];
  }
};

template <class T> class CentroidDecomposition {
  WeightedTree<T> &tree;
  vector<int> label;
  int centroid;
  
public:
  // This class can modify the tree's root.
  CentroidDecomposition(WeightedTree<T> &tree): tree(tree) {
    SubtreeSize<T> subtreeSize(tree);
    
    int n = (int) tree.getSize();
    int u = tree.getRoot();
    
    label.resize(n + 1);
    
    centroid = u;
    
    while (1) {
      int maxSubtreeSize = 0;
      int maxSubtreeRoot = -1;
      for (auto &v: tree.getAdjacent(u)) {
        if (v.first != tree.getParent(u) && subtreeSize[v.first] > maxSubtreeSize) {
          maxSubtreeSize = subtreeSize[v.first];
          maxSubtreeRoot = v.first;
        }
      }
      if (maxSubtreeSize <= n/2) {
        centroid = u;
        break;
      }
      u = maxSubtreeRoot;
    }
    
    label[centroid] = 1;
    
    WeightedTree<T> subtree;
    vector<int> pi(n + 1);
    for (auto &v: tree.getAdjacent(centroid)) {
      int subSize;
      if (tree.getParent(v.first) == centroid) {
        subSize = subtreeSize[v.first];
      } else {
        subSize = n - subtreeSize[centroid];
      }
      
      subtree.reset(subSize);
      vector<int> mapNode(n + 1);
      vector<int> inverseMapNode(subSize + 1);
      
      stack<int> node;
      node.push(v.first);
      
      int nodeCount = 1;
      mapNode[v.first] = 1;
      inverseMapNode[1] = v.first;
      pi[v.first] = centroid;
      
      while (!node.empty()) {
        int u = node.top();
        node.pop();
        for (auto &w : tree.getAdjacent(u)) if (w.first != pi[u]) {
          nodeCount++;
          mapNode[w.first] = nodeCount;
          inverseMapNode[nodeCount] = w.first;
          node.push(w.first);
          pi[w.first] = u;
          
          subtree.addEdge(mapNode[u], mapNode[w.first], w.second);
        }
      }
      subtree.setRoot(1);
      
      CentroidDecomposition<T> subCD(subtree);
      
      for_inc_range(u, 1, subSize) {
        label[inverseMapNode[u]] = subCD.getLabel(u) + 1;
      }
    }
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
