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

template <class T, class Q>
using TreeMergeFunction = function<Q(const Q &, const Q &)>;
template <class T, class Q>
using TreeUpdateLeafFunction = function<Q(const Q &, const T &, const T &, int, int)>;
template <class T, class Q>
using TreeSplitFunction = function<void(Q &, Q &, Q &, T, int, int, int)>;
template <class T, class Q>
using TreeInitFunction = function<Q(const T&, int, int)>;


template <class T, class Q> struct SegmentTree {
  struct TreeNode {
    bool leaf = true; // All elements in the leaf node's segment are the same
    T value;
    Q query;
    int leftChild = -1,
    rightChild =
    -1; // index of the left and right children, -1 for no child
  };
  
  vector<TreeNode> node;
  TreeMergeFunction<T, Q> merge;
  TreeUpdateLeafFunction<T, Q> updateLeaf;
  TreeSplitFunction<T, Q> split;
  TreeInitFunction<T, Q> init;
  const T defaultValue;
  
  int addNode(int l, int r) {
    TreeNode newNode;
    newNode.value = defaultValue;
    node.push_back(newNode);
    return (int)node.size() - 1;
  }
  
  void splitNode(int p, int l, int r) {
    assert(node[p].leaf);
    int m = (l + r) / 2;
    node[p].leaf = false;
    if (node[p].leftChild == -1) {
      int c = addNode(l, m);
      node[p].leftChild = c;
      c = addNode(m + 1, r);
      node[p].rightChild = c;
    }
    int lc = node[p].leftChild;
    int rc = node[p].rightChild;
    node[lc].leaf = true;
    node[rc].leaf = true;
    node[lc].value = node[p].value;
    node[rc].value = node[p].value;
    split(node[p].query, node[lc].query, node[rc].query, node[p].value, l, m, r);
  }
  
  void update(int p, int l, int r, int i, int j, const T &v) {
    if (j < l || i > r)
      return;
    int m = (l + r) / 2;
    if (i <= l && r <= j) { // [i,j] covers [l,r]
      if (node[p].leaf) {
        node[p].query = updateLeaf(node[p].query, node[p].value, v, l, r);
        node[p].value = v;
        return;
      } else {
        node[p].leaf = true;
        node[p].value = v;
      }
    } else if (node[p].leaf) { // [i,j] intersects [l, r]
      splitNode(p, l, r);
    }
    update(node[p].leftChild, l, m, i, j, v);
    update(node[p].rightChild, m + 1, r, i, j, v);
    node[p].query = merge(node[node[p].leftChild].query,
                          node[node[p].rightChild].query);
  }
  
  Q query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) { // [i,j] contains [l,r]
      return node[p].query;
    }
    if (node[p].leaf) { // [i,j] intersects [l, r]
      splitNode(p, l, r);
    }
    int m = (l + r) / 2;
    Q ret;
    if (j <= m) {
      ret = query(node[p].leftChild, l, m, i, j);
    } else if (i >= m + 1) {
      ret = query(node[p].rightChild, m + 1, r, i, j);
    } else {
      ret = merge(query(node[p].leftChild, l, m, i, j), query(node[p].rightChild, m + 1, r, i, j));
    }
    node[p].query = merge(node[node[p].leftChild].query,
                          node[node[p].rightChild].query);
    return ret;
  }
  
  int minIndex, maxIndex;
  int root;
  
public:
  // First way to specify a segment tree, usually use when lazy propagation is needed.
  // Q merge(Q, Q) that merges the query from left and right children
  // Q updateLeaf(Q cur, T oldV, T curV, int l, int r) return the updated
  //   query in a leaf node if its old value is oldV and new value is curV
  // split(Q& cur, Q &lChild, Q &rChild, int curV, int l, int m, int r)
  //   modify the query in the current node and it's left and right children when
  // a split action happens.
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const TreeMergeFunction<T, Q> &merge,
              const TreeUpdateLeafFunction<T, Q> &updateLeaf,
              const TreeSplitFunction<T, Q> &split)
  : merge(merge), updateLeaf(updateLeaf), split(split),
  defaultValue(defaultValue), minIndex(minIndex), maxIndex(maxIndex) {
    root = addNode(minIndex, maxIndex);
  }
  
  // The second way to specify a segment tree:
  // a merge function
  // an init function (v, l, r) that initilize the query based on
  // the value of the node and the node interval
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const TreeMergeFunction<T, Q> &merge,
              const function<Q(T, int, int)> &init)
  : merge(merge),
  defaultValue(defaultValue), minIndex(minIndex), maxIndex(maxIndex), init(init) {
    updateLeaf = [&] (const Q &cur, T oldV, T curV, int l, int r) {
      return this->init(curV, l, r);
    };
    split = [&](Q &cur, Q &lQ, Q &rQ, T v, int l, int m, int r) {
      lQ = this->init(v, l, m);
      rQ = this->init(v, m + 1, r);
    };
    root = addNode(minIndex, maxIndex);
  }
  
  
  // Set all elements in [i, j] to be v
  void update(int i, int j, T v) { update(root, minIndex, maxIndex, i, j, v); }
  
  // Query augmented data in [i, j]
  Q query(int i, int j) { return query(root, minIndex, maxIndex, i, j); }
  
  // Query augmented data in the whole range
  Q query() { return query(root, minIndex, maxIndex, minIndex, maxIndex); }
};

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


template<class T> class HeavyLightDecomposition {
  const WeightedTree<T> &tree;
  int timeStamp;
  vector<int> start;
  vector<int> head;
  vector<int> node;
  int n;
  
  void dfs(int u, const SubtreeSize<T> &subtreeSize) {
    stack<int> s;
    s.push(u);
    while (!s.empty()) {
      u = s.top();
      s.pop();
      
      timeStamp++;
      node[timeStamp] = u;
      start[u] = timeStamp;
      
      int heavyCutoff = subtreeSize[u] / 2;
      int nextNode = -1;
      
      for (auto &v: tree.getAdjacent(u)) {
        if (v.first != tree.getParent(u)) {
          if (subtreeSize[v.first] > heavyCutoff) {
            nextNode = v.first;
            break;
          }
        }
      }
      
      for (auto &v: tree.getAdjacent(u)) {
        if (v.first != tree.getParent(u) && v.first != nextNode) {
          head[v.first] = v.first;
          s.push(v.first);
        }
      }
      
      if (nextNode != -1) {
        head[nextNode] = head[u];
        // Tricky: in non-recursive DFS, if you want to visit nextNode first,
        // you have to push it last into the stack
        s.push(nextNode);
      }
    }
  }
  
public:
  HeavyLightDecomposition(const WeightedTree<T> &tree): tree(tree) {
    n = (int) tree.getSize();
    timeStamp = 0;
    SubtreeSize<int> subtreeSize(tree);
    start.resize(n + 1);
    head.resize(n + 1);
    node.resize(n + 1);
    head[tree.getRoot()] = tree.getRoot();
    dfs(tree.getRoot(), subtreeSize);
  }
  
  // is the path parent[u] to u light?
  bool isLight(int u) const {
    assert(u != tree.getRoot());
    assert(1 <= u && u <= n);
    return head[u] == u;
  }
  
  bool isHeavy(int u) const {
    return !isLight(u);
  }
  
  int getHead(int u) const {
    assert(1 <= u && u <= n);
    return head[u];
  }
  
  int getStartTime(int u) const {
    assert(1 <= u && u <= n);
    return start[u];
  }
  
  int getNodeAtTime(int timeStamp) const {
    return node[timeStamp];
  }
  
  int getHeadTime(int u) const {
    assert(1 <= u && u <= n);
    return start[head[u]];
  }
  
  bool inSameHeavyPath(int u, int v) const {
    assert(1 <= u && u <= n);
    return head[u] == head[v];
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int queryUp(int u, int v, const vector<int> &color, const WeightedTree<int> &tree, const HeavyLightDecomposition<int> &hld, SegmentTree<int, int>  &seg) {
  // v is ancestor of u
  int res = INT_INF;
  while (1) {
    if (color[u] == 1) {
      res = u;
    }
    if (u == v) {
      break;
    }
    if (hld.isLight(u)) {
      u = tree.getParent(u);
    } else {
      if (hld.inSameHeavyPath(u, v)) {
        int t = seg.query(hld.getStartTime(v), hld.getStartTime(u));
        if (t != INT_INF) {
          res = hld.getNodeAtTime(t);
        }
        return res;
      } else {
        int t = seg.query(hld.getHeadTime(u), hld.getStartTime(u));
        if (t != INT_INF) {
          res = hld.getNodeAtTime(t);
        }
        u = hld.getHead(u);
      }
    }
  }
  
  return res;
}

// Sample: SPOJ - QTREE3
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("biginput1.txt", "r", stdin);
  freopen("biginput1.out", "w", stdout);
#endif
  
  int n, q;
  scanf("%d%d", &n, &q);
  
  WeightedTree<int> tree;
  tree.reset(n);
  vector<pair<int, int>> edge;
  
  repeat(n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    tree.addEdge(u, v, 1);
    edge.push_back(make_pair(u, v));
  }
  tree.setRoot(1);
  
  HeavyLightDecomposition<int> hld(tree);
  
  SegmentTree<int, int> seg(1, n, 0, [](int l, int r) {return min(l, r);}, [](int v, int l, int r) {return (v == 1) ? l : INT_INF;});
  
  seg.update(1, n, 0);
  vector<int> color(n + 1);
  
  repeat(q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int u;
      scanf("%d", &u);
      color[u] = 1 - color[u];
      int s = hld.getStartTime(u);
      seg.update(s, s, color[u]);
    } else if (t == 1) {
      int u;
      scanf("%d", &u);
      int res = queryUp(u, 1, color, tree, hld, seg);
      if (res == INT_INF) res = -1;
      printf("%d\n", res);
    }
  }
  return 0;
}
