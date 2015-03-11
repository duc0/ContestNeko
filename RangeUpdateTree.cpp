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
    for (auto &e : adj[u]) {
      int v = e.first;
      int c = e.second;
      if (p[v].first == -1) {
        p[v] = make_pair(u, c);
        depth[v] = depth[u] + 1;
        dfs(v);
      }
    }
  }
  
  int getParent(int u) const { return p[u].first; }
  
  T getWeight(int u) const { return p[u].second; }
  
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

template<class T> class TreeToArray {
  const WeightedTree<T> &tree;
  
  int timeStamp;
  // sequence[start[u], finish[u]] = subtree rooted at u
  vector<int> start, finish, sequence;
  
  void dfs(int u) {
    timeStamp++;
    sequence[timeStamp] = u;
    start[u] = timeStamp;
    for (auto &v: tree.getAdjacent(u)) {
      if (start[v.first] == 0) {
        dfs(v.first);
      }
    }
    finish[u] = timeStamp;
  }
  
public:
  TreeToArray(const WeightedTree<T> &tree): tree(tree) {
    timeStamp = 0;
    start.resize(tree.getSize() + 1);
    finish.resize(tree.getSize() + 1);
    sequence.resize(tree.getSize() + 1);
    dfs(tree.getRoot());
  }
  
  const WeightedTree<T>& getTree() const {
    return tree;
  }
  
  int getStartTime(int u) const {
    return start[u];
  }
  
  int getFinishTime(int u) const {
    return finish[u];
  }
};

template <class T> class BinaryIndexedTree {
  vector<T> val;
  int n, minIndex, maxIndex;
  
public:
  BinaryIndexedTree(int n): BinaryIndexedTree(1, n) {}
  
  BinaryIndexedTree(int minIndex, int maxIndex) {
    init(minIndex, maxIndex);
  }
  
  BinaryIndexedTree() {}
  
  void init(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    this->n = maxIndex - minIndex + 1;
    val.resize(n + 1);
  }
  
  void add(int i, int v) {
    i = i - minIndex + 1;
    for (; i <= n; i += i & -i) {
      val[i] += v;
    }
  }
  T sum(int i) {
    i = i - minIndex + 1;
    if (i <= 0) return 0;
    if (i > n) i = n;
    T s = 0;
    for (; i > 0; i -= i & -i)
      s += val[i];
    return s;
  }
  
  T sum(int i1, int i2) { return sum(i2) - sum(i1 - 1); }
};

template <class T> class RangeUpdateArray {
  BinaryIndexedTree<T> tree;
  int minIndex, maxIndex;
  
public:
  RangeUpdateArray() {}
  
  RangeUpdateArray(int n) {
    init(1, n);
  }
  
  RangeUpdateArray(int minIndex, int maxIndex) {
    init(minIndex, maxIndex);
  }
  
  void init(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    tree.init(minIndex, maxIndex);
  }
  
  // Do a[k] = a[k] + v for i <= k <= j
  // O(logn)
  void add(int i, int j, T v) {
    assert(minIndex <= i && i <= j && j <= maxIndex);
    if (j < maxIndex) {
      tree.add(j + 1, -v);
    }
    tree.add(i, v);
  }
  
  // Return a[i] in O(logn)
  T get(int i) {
    assert (minIndex <= i && i <= maxIndex);
    return tree.sum(i);
  }
  
  const T operator[](int i) {
    return get(i);
  }
};

template <class T, class W> class RangeUpdateTree {
  const TreeToArray<W> &treeToArray;
  RangeUpdateArray<T> a;
  int n;
public:
  RangeUpdateTree(const TreeToArray<W> &treeToArray): treeToArray(treeToArray) {
    n = (int) treeToArray.getTree().getSize();
    a.init(1, n);
  }
  
  // Add a value to a node
  void addNode(int u, const T &val) {
    assert(1 <= u && u <= n);
    int p = treeToArray.getStartTime(u);
    a.add(p, p, val);
  }
  
  // Add a value to all node at a rooted-subtree
  void addSubtree(int u, const T &val) {
    assert(1 <= u && u <= n);
    a.add(treeToArray.getStartTime(u), treeToArray.getFinishTime(u), val);
  }
  
  // Return the value at node u
  T get(int u) {
    assert(1 <= u && u <= n);
    return a.get(treeToArray.getStartTime(u));
  }
  
  const T operator[](int u) {
    return get(u);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// CF 225 - C
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 1);
  for_inc_range(i, 1, n) cin >> a[i];
  
  WeightedTree<int> tree(n);
  repeat(n - 1) {
    int u, v;
    cin >> u >> v;
    tree.addEdge(u, v, 1);
  }
  tree.setRoot(1);
  
  TreeToArray<int> treeToArray(tree);
  
  RangeUpdateTree<int, int> odd(treeToArray);
  RangeUpdateTree<int, int> even(treeToArray);
  for_inc_range(u, 1, n) {
    odd.addNode(u, a[u]);
    even.addNode(u, a[u]);
  }
  
  repeat(q) {
    int t;
    cin >> t;
    if (t == 1) {
      int u, val;
      cin >> u >> val;
      
      if (tree.getDepth(u) % 2 == 0) {
        even.addSubtree(u, val);
        odd.addSubtree(u, -val);
      } else {
        odd.addSubtree(u, val);
        even.addSubtree(u, -val);
      }
    } else {
      int u;
      cin >> u;
      
      if (tree.getDepth(u) % 2 == 0) {
        cout << even[u] << endl;
      } else {
        cout << odd[u] << endl;
      }
    }
  }
  
  return 0;
}
