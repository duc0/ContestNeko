//#define SUBMIT

#define C11

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
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11
#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>
#endif

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

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
using TreeUpdateLeafFunction =
function<Q(const Q &, const T &, const T &, int, int)>;
template <class T, class Q>
using TreeSplitFunction = function<void(Q &, Q &, Q &, T, int, int, int)>;
template <class T, class Q>
using TreeInitFunction = function<Q(const T &, int, int)>;

template <class T, class Q> struct SegmentTree {
  struct TreeNode {
    bool leaf = true; // All elements in the leaf node's segment are the same
    T value;
    Q query;
    int leftChild = -1,
    rightChild =
    -1; // index of the left and right children, -1 for no child
  };
  
protected:
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
    split(node[p].query, node[lc].query, node[rc].query, node[p].value, l, m,
          r);
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
    node[p].query =
    merge(node[node[p].leftChild].query, node[node[p].rightChild].query);
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
      ret = merge(query(node[p].leftChild, l, m, i, j),
                  query(node[p].rightChild, m + 1, r, i, j));
    }
    node[p].query =
    merge(node[node[p].leftChild].query, node[node[p].rightChild].query);
    return ret;
  }
  
  int minIndex, maxIndex;
  int root;
  
public:
  // First way to specify a segment tree, usually use when lazy propagation is
  // needed.
  // Q merge(Q, Q) that merges the query from left and right children
  // Q updateLeaf(Q cur, T oldV, T curV, int l, int r) return the updated
  //   query in a leaf node if its old value is oldV and new value is curV
  // split(Q& cur, Q &lChild, Q &rChild, int curV, int l, int m, int r)
  //   modify the query in the current node and it's left and right children
  //   when
  // a split action happens.
  explicit SegmentTree(int minIndex, int maxIndex, T defaultValue,
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
  : merge(merge), defaultValue(defaultValue), minIndex(minIndex),
  maxIndex(maxIndex), init(init) {
    updateLeaf = [&](const Q &cur, T oldV, T curV, int l, int r) {
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

/******* PREDEFINE SOME COMMON SEG TREES ******* */

// A segment tree with two queries:
// add(i, j, v): add all elements in range [i, j] by V
// queryMax(i, j)
// all 0 initially.
template <class T> struct MaxTreeQ;
template <class T> class MaxTree : public SegmentTree<T, MaxTreeQ<T>> {
public:
  MaxTree(int minIndex, int maxIndex)
  : SegmentTree<T, MaxTreeQ<T>>(
                                minIndex, maxIndex, 0,
                                [](const MaxTreeQ<T> &l, const MaxTreeQ<T> &r) {
                                  return MaxTreeQ<T>(max(l.queryMax, r.queryMax), 0);
                                },
                                [](const MaxTreeQ<T> &cur, T oldV, T newV, int l, int r) {
                                  return MaxTreeQ<T>(cur.queryMax + newV, cur.lazy + newV);
                                },
                                [](MaxTreeQ<T> &cur, MaxTreeQ<T> & lChild, MaxTreeQ<T> & rChild,
                                   T curV, int l, int m, int r) {
                                  lChild.lazy += cur.lazy;
                                  rChild.lazy += cur.lazy;
                                  lChild.queryMax += cur.lazy;
                                  rChild.queryMax += cur.lazy;
                                  cur.lazy = 0;
                                }) {}
  
  T queryMax(int l, int r) {
    return SegmentTree<T, MaxTreeQ<T>>::query(l, r).queryMax;
  }
  
  T queryMax() { return SegmentTree<T, MaxTreeQ<T>>::query().queryMax; }
  
  void add(int l, int r, T v) { SegmentTree<T, MaxTreeQ<T>>::update(l, r, v); }
};

template <class T> struct MaxTreeQ {
  T queryMax = 0;
  T lazy = 0;
  MaxTreeQ(){};
  MaxTreeQ(T queryMax, T lazy) {
    this->queryMax = queryMax;
    this->lazy = lazy;
  }
};


void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXQ 200200

int n, q;
pair<int, int> query[MAXQ];
bool queryUp[MAXQ];

set<int> coord;
map<int, int> mapCoordCol, mapCoordRow;
int rowCoordById[MAXQ], colCoordById[MAXQ];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  cin >> n >> q;
  for_inc_range(i, 1, q) {
    int x, y;
    string s;
    cin >> x >> y >> s;
    query[i] = make_pair(x, y);
    queryUp[i] = s[0] == 'U';
    coord.insert(x);
  }
  
  int id = 0;
  for (auto &x: coord) {
    id++;
    mapCoordCol[x] = id;
    mapCoordRow[n + 1 - x] = id;
    colCoordById[id] = x;
    rowCoordById[id] = n + 1 - x;
  }
  
  MaxTree<int> maxCol(1, id);
  MaxTree<int> maxRow(1, id);
  
  for_inc_range(i, 1, q) {
    int ret = 0;
    if (queryUp[i]) {
      int qCol = mapCoordCol[query[i].first]; // col
      int qRow = mapCoordRow[query[i].second]; // row
      int rowUp = maxCol.queryMax(qCol, qCol); // row
      ret = rowCoordById[rowUp] - query[i].second; // uncompressed row
      maxRow.add(qRow, rowUp, qCol); // col
    } else {
      int qCol = mapCoordCol[query[i].first]; // col
      int qRow = mapCoordRow[query[i].second]; // row
      int colUp = maxRow.queryMax(qRow, qRow); // row
      ret = colCoordById[colUp] - query[i].first; // uncompressed row
      maxCol.add(qCol, colUp, qRow); // col
    }
    cout << ret << endl;
  }
  return 0;
}
