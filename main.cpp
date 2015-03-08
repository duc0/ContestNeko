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
  const TreeMergeFunction<T, Q> merge;
  const TreeUpdateLeafFunction<T, Q> updateLeaf;
  const TreeSplitFunction<T, Q> split;
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
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const TreeMergeFunction<T, Q> &merge,
              const TreeUpdateLeafFunction<T, Q> &updateLeaf,
              const TreeSplitFunction<T, Q> &split)
  : merge(merge), updateLeaf(updateLeaf), split(split),
  defaultValue(defaultValue), minIndex(minIndex), maxIndex(maxIndex) {
    root = addNode(minIndex, maxIndex);
  }
  
  // Set all elements in [i, j] to be v
  void update(int i, int j, T v) { update(root, minIndex, maxIndex, i, j, v); }
  
  // Query augmented data in [i, j]
  Q query(int i, int j) { return query(root, minIndex, maxIndex, i, j); }
  
  // Query augmented data in the whole range
  Q query() { return query(root, minIndex, maxIndex, minIndex, maxIndex); }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n, m, nQuery;
vector<int> a;
vector<pair<pair<int, int>, int>> query;
vector<int> countGroup;
vector<int> queryResult;
vector<int> maxPos;
vector<int> prevEq;

struct MinMaxPos {
  int minPos, maxPos;
  MinMaxPos() {
    minPos = n + 1;
    maxPos = 0;
  }
  MinMaxPos(int minPos, int maxPos) {
    this->minPos = minPos;
    this->maxPos = maxPos;
  }
};

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  cin >> n >> m >> nQuery;
  a.resize(n + 1);
  
  countGroup.resize(m + 1);
  maxPos.resize(m + 1);
  prevEq.resize(n + 1);
  for_inc_range(i, 1, n) {
    cin >> a[i];
    countGroup[a[i]]++;
  }
  
  queryResult.resize(nQuery);
  for_inc(i, nQuery) {
    int l, r;
    cin >> l >> r;
    query.push_back(make_pair(make_pair(r, l), i));
  }
  
  sort(query.begin(), query.end());
  
  int queryIdx = 0;
  
  // Threshold for small groups
  int cutOff = (int)sqrt(n);
  
  // maxLength[i] = max{j - i, a[j] = a[i]}
  SegmentTree<int, int> maxLength
  (
   1,
   n,
   0,
   [](int l, int r) {return max(l, r);},
   [](int cur, int oldV, int v, int l, int r) {return v;},
   [](int &curQ, int &lQ, int &rQ, int curV, int l, int mid, int r) {lQ = curV; rQ = curV;}
  );
  
  for_inc_range(i, 1, n) {
    LOG(1, "Start at index " << i);
    prevEq[i] = maxPos[a[i]];
    maxPos[a[i]] = i;
    LOG(1, "Previous element equal to a[i]: " << prevEq[i]);
    
    if (countGroup[a[i]] <= cutOff) {
      LOG(1, "Group of a[i]=" << a[i] << " is small");
      int j = prevEq[i];
      while (j > 0) {
      LOG(1, "Update max length at " << j << " to " << i - j);
        maxLength.update(j, j, i - j);
        j = prevEq[j];
      }
    }
    
    while (queryIdx < nQuery && query[queryIdx].first.first <= i) {
      int l = query[queryIdx].first.second, r = query[queryIdx].first.first;
      int mL = maxLength.query(l, r);
      LOG(1, "Process query " << l << " " << r << " result: " << mL);
      queryResult[query[queryIdx].second] = mL;
      ++queryIdx;
    }
  }
  
  SegmentTree<int, MinMaxPos> tree
  (
   1,
   n,
   0,
   [](const MinMaxPos &l, const MinMaxPos &r) {return MinMaxPos{min(l.minPos, r.minPos), max(l.maxPos, r.maxPos)};},
   [](const MinMaxPos &cur, int oldV, int v, int l, int r) {return (v == 1) ? MinMaxPos{l, r} : MinMaxPos();},
   [](MinMaxPos &curQ, MinMaxPos &lQ, MinMaxPos &rQ, int curV, int l, int mid, int r) {}
   );
  
  for_dec_range(i, n, 1) {
    if (countGroup[a[i]] > cutOff) {
      // Clear the tree
      tree.update(1, n, 0);
      
      LOG(1, "Group of a[i]=" << a[i] << " is big");
      // Big group
      int j = i;
      while (j > 0) {
        tree.update(j, j, 1);
        LOG(1, "Add element at " << j);
        j = prevEq[j];
      }
      for (auto &q: query) {
        int l = q.first.second, r = q.first.first, id = q.second;
        MinMaxPos ans = tree.query(l, r);
        LOG(1, "Process query  " << l << " " << r << " result " << ans.maxPos - ans.minPos);
        queryResult[id] = max(queryResult[id], ans.maxPos - ans.minPos);
      }
      
      // Just mark that this group has been processed.
      countGroup[a[i]] = 0;
    }
  }
  
  for_inc(i, nQuery) {
    cout << queryResult[i] << endl;
  }
  
  return 0;
}
