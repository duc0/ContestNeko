#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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
#include <deque>

using namespace std;

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template <class T, class Q> struct SegmentTree {
  struct TreeNode {
    bool leaf = true; // All elements in the leaf node's segment are the same
    T value;
    Q query;
    int leftChild = -1,
        rightChild = -1; // index of the left and right children, -1 for no child
    TreeNode(T value, Q query): value(value), query(query) {}
  };

  vector<TreeNode> node;
  const function<Q(Q, Q)> &combine;
  const function<Q(T, int, int)> &initial;
  const T defaultValue;

  int addNode(int l, int r) {
    TreeNode newNode(defaultValue, initial(defaultValue, l, r));
    node.push_back(newNode);
    return (int)node.size() - 1;
  }

  void update(int p, int l, int r, int i, int j, const T &v) {
    if (i <= l && r <= j) { // [i,j] covers [l,r]
      node[p] = TreeNode(v, initial(v, l, r));
    } else if (i <= r && l <= j) { // [i,j] intersects [l,r]
      int m = (l + r) / 2;
      if (node[p].leaf) {
        node[p].leaf = false;
        if (node[p].leftChild == -1) {
          node[p].leftChild = addNode(l, m);
        }
        if (node[p].rightChild == -1) {
          node[p].rightChild = addNode(m + 1, r);
        }
        // Propagate p's value to its children
        node[node[p].leftChild] =
            TreeNode(node[p].value, initial(node[p].value, l, m));
        node[node[p].rightChild] =
            TreeNode(node[p].value, initial(node[p].value, m + 1, r));
      }
      update(node[p].leftChild, l, m, i, j, v);
      update(node[p].rightChild, m + 1, r, i, j, v);
      node[p].query = combine(node[node[p].leftChild].query,
                              node[node[p].rightChild].query);
    }
  }

  Q query(int p, int l, int r, int i, int j) {
    if (j < l || i > r) { // [i,j] does not intersect [l,r]
      return initial(defaultValue, l, r);
    }
    if (i <= l && r <= j) { // [i,j] intersects [l,r]
      return node[p].query;
    }
    if (node[p].leaf) {
      return initial(node[p].value, max(i, l), min(j, r));
    }
    int m = (l + r) / 2;
    if (j <= m) {
      return query(node[p].leftChild, l, m, i, j);
    }
    if (i >= m + 1) {
      return query(node[p].rightChild, m + 1, r, i, j);
    }
    return combine(query(node[p].leftChild, l, m, i, j),
                   query(node[p].rightChild, m + 1, r, i, j));
  }

  int minIndex, maxIndex;
  int root;
  
public:
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const function<Q(Q, Q)> &combine,
              const function<Q(T, int, int)> &initial)
      : combine(combine), initial(initial), defaultValue(defaultValue), minIndex(minIndex), maxIndex(maxIndex) {
    root = addNode(minIndex, maxIndex);
  }

  // Set all elements in [i, j] to be v
  void update(int i, int j, T v) { update(root, minIndex, maxIndex, i, j, v); }

  // Query augmented data in [i, j]
  Q query(int i, int j) { return query(root, minIndex, maxIndex, i, j); }

  // Query augmented data in the whole range
  Q query() { return query(root, minIndex, maxIndex, minIndex, maxIndex); }
};

struct gss {
  int s, l, r, k; // s: sum, l: sum from left, r: sum from right, k: gss result
};

int main() {
  freopen("input1.txt", "r", stdin);

  int m, n, x, a, b;
  scanf("%d", &n);

  auto combine = [](gss a, gss b) {
    return gss{a.s + b.s, max(a.l, a.s + b.l), max(a.r + b.s, b.r),
               max(max(a.k, b.k), a.r + b.l)};
  };
  auto initial = [](int v, int l, int r) {
    return gss{v * (r - l + 1), v > 0 ? v * (r - l + 1) : v,
               v > 0 ? v * (r - l + 1) : v, v > 0 ? v * (r - l + 1) : v};
  };

  SegmentTree<int, gss> t(1, n, 0, combine, initial);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    t.update(i, i, x);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a, &b);
    printf("%d\n", t.query(a, b).k);
  }
  return 0;
}
