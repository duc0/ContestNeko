//#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
//#define NDEBUG
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

template<class T, class Q> using TreeCombineFunction = function<Q(const Q&, const Q&, const Q&, int, int, int)>;
template<class T, class Q> using TreeLeafFunction = function<Q(const Q&, const T&, const T&, int, int)>;
template<class T, class Q> using TreeSplitFunction = function<void(Q&, Q&, Q&, int, int, int)>;

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
  const TreeCombineFunction<T,Q> combine;
  const TreeLeafFunction<T,Q> updateLeaf;
  const TreeSplitFunction<T,Q> split;
  const T defaultValue;
  
  int addNode(int l, int r) {
    TreeNode newNode;
    newNode.value = defaultValue;
    node.push_back(newNode);
    return (int)node.size() - 1;
  }
  
  void update(int p, int l, int r, int i, int j, const T &v) {
    if (j < l || i > r) return;
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
      node[p].leaf = false;
      if (node[p].leftChild == -1) {
        int c = addNode(l, m);
        node[p].leftChild = c;
        node[c].value = node[p].value;
        assert(node[p].rightChild == -1);
        c = addNode(m + 1, r);
        node[p].rightChild = c;
        node[c].value = node[p].value;
      }
      node[node[p].leftChild].leaf=true;
      node[node[p].rightChild].leaf=true;
      node[node[p].leftChild].value=node[p].value;
      node[node[p].rightChild].value=node[p].value;
      split(node[p].query, node[node[p].leftChild].query, node[node[p].rightChild].query, l, m, r);
    }
    assert(node[p].leftChild != -1);
    assert(node[p].rightChild != -1);
    update(node[p].leftChild, l, m, i, j, v);
    update(node[p].rightChild, m + 1, r, i, j, v);
    node[p].query = combine(node[p].query, node[node[p].leftChild].query,
                            node[node[p].rightChild].query, l, m, r);
  }
  
  Q query(int p, int l, int r, int i, int j) {
    if (i <= l && r <= j) { // [i,j] contains [l,r]
      return node[p].query;
    }
    /*if (node[p].leaf && node[p].leftChild == -1) {
      return initial(node[p].query, node[p].value, node[p].value, max(i, l), min(j, r));
    }*/
    int m = (l + r) / 2;    
    if (node[p].leaf) { // [i,j] intersects [l, r]
      node[p].leaf = false;
      if (node[p].leftChild == -1) {
        int c = addNode(l, m);
        node[p].leftChild = c;
        node[c].value = node[p].value;
        assert(node[p].rightChild == -1);
        c = addNode(m + 1, r);
        node[p].rightChild = c;
        node[c].value = node[p].value;
      }
      node[node[p].leftChild].leaf=true;
      node[node[p].rightChild].leaf=true;
      node[node[p].leftChild].value=node[p].value;
      node[node[p].rightChild].value=node[p].value;
      split(node[p].query, node[node[p].leftChild].query, node[node[p].rightChild].query, l, m, r);
    }
    assert(node[p].leftChild != -1);
    assert(node[p].rightChild != -1);
    Q qLeft;
    Q qRight;
    if (i <= m) {
      qLeft = query(node[p].leftChild, l, m, i, j);
    }
    if (j >= m + 1) {
      qRight = query(node[p].rightChild, m + 1, r, i, j);
    }
    node[p].query = combine(node[p].query, node[node[p].leftChild].query,
                            node[node[p].rightChild].query, l, m, r);
    return combine(node[p].query, qLeft, qRight, l, m, r);
  }
  
  int minIndex, maxIndex;
  int root;
  
public:
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const TreeCombineFunction<T,Q> &combine,
              const TreeLeafFunction<T,Q> &updateLeaf,
              const TreeSplitFunction<T,Q> &split)
  : combine(combine), updateLeaf(updateLeaf), split(split), defaultValue(defaultValue),
  minIndex(minIndex), maxIndex(maxIndex) {
    root = addNode(minIndex, maxIndex);
  }
  
  // Set all elements in [i, j] to be v
  void update(int i, int j, T v) { update(root, minIndex, maxIndex, i, j, v); }
  
  // Query augmented data in [i, j]
  Q query(int i, int j) { return query(root, minIndex, maxIndex, i, j); }
  
  // Query augmented data in the whole range
  Q query() { return query(root, minIndex, maxIndex, minIndex, maxIndex); }
};

// Sample: SPOJ_GSS

struct ColorsQuery {
  // Sum of colourfulness
  int64 sum;
  
  // The amount of colourfulness caused by the segments that cover the range on each element in the range
  int64 delta;
  
  ColorsQuery() {
    sum = 0;
    delta = 0;
  }
  
  ColorsQuery(int64 sum, int64 delta) {
    this->sum = sum;
    this->delta = delta;
  }
};

int main() {
#ifndef SUBMIT
  freopen("input4.txt", "r", stdin);
#endif
  
  int n, q, t, l, r, x;
  cin >> n >> q;
  auto combine = [](const ColorsQuery &cur, const ColorsQuery &lNode, const ColorsQuery &rNode, int leftIndex, int midIndex, int rightIndex) {
    return ColorsQuery(lNode.sum + rNode.sum, 0);
  };
  
  auto leaf = [](const ColorsQuery &cur, const int &oldV, const int &newV, int lIndex, int rIndex) {
    return ColorsQuery(cur.sum + 1LL * abs(newV - oldV) * (rIndex - lIndex + 1), cur.delta + 1LL * abs(newV - oldV));
  };
  
  auto split = [](ColorsQuery &cur, ColorsQuery &lNode, ColorsQuery &rNode, int leftIndex, int midIndex, int rightIndex) {
    lNode.sum += cur.delta * (midIndex - leftIndex + 1);
    lNode.delta += cur.delta;
    rNode.sum += cur.delta * (rightIndex - midIndex);
    rNode.delta += cur.delta;
    
    cur.delta = 0;
  };
  
  SegmentTree<int64, ColorsQuery> tree(1, n, 0, combine, leaf, split);
  for_inc_range(i, 1, n) {
    tree.update(i, i, i);
  }
  repeat(q) {
    cin >> t;
    if (t == 1) {
      cin >> l >> r >> x;
      tree.update(l, r, x);
    } else {
      cin >> l >> r;
      int64 exclude = (int64)(r - l + 1) * (r + l) / 2;
      cout << tree.query(l, r).sum  - exclude << endl;
    }
  }
  
  return 0;
}
