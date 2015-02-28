#define SUBMIT

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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template<class T, class Q> using TreeCombineFunction = function<Q(const Q&, const Q&, const Q&, int, int, int)>;
template<class T, class Q> using TreeLeafFunction = function<Q(const T&, int, int)>;

template <class T, class Q> struct SegmentTree {
  struct TreeNode {
    bool leaf = true; // All elements in the leaf node's segment are the same
    T value;
    Q query;
    int leftChild = -1,
    rightChild =
    -1; // index of the left and right children, -1 for no child
    void init(T value, Q query) {
      this->value = value;
      this->query = query;
      this->leftChild = -1;
      this->rightChild = -1;
      this->leaf = true;
    }
    TreeNode(T value, Q query) {
      init(value, query);
    }
  };
  
  vector<TreeNode> node;
  const TreeCombineFunction<T,Q> combine;
  const TreeLeafFunction<T,Q> initial;
  const T defaultValue;
  
  int addNode(int l, int r) {
    TreeNode newNode(defaultValue, initial(defaultValue, l, r));
    node.push_back(newNode);
    return (int)node.size() - 1;
  }
  
  void update(int p, int l, int r, int i, int j, const T &v) {
    if (j < l || i > r) return;
    int m = (l + r) / 2;
    if (i <= l && r <= j) { // [i,j] covers [l,r]
      if (node[p].leaf) {
        node[p].init(v, initial(v, l, r));
        return;
      } else {
        node[p].leaf = true;
      }
    } else if (node[p].leaf) { // [i,j] intersects [l, r]
      node[p].leaf = false;
      if (node[p].leftChild == -1) {
        int c = addNode(l, m);
        node[p].leftChild = c;
        node[c].init(node[p].value, initial(node[p].value, l, m));
        assert(node[p].rightChild == -1);
        c = addNode(m + 1, r);
        node[p].rightChild = c;
        node[c].init(node[p].value, initial(node[p].value, m + 1, r));
      }
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
    if (node[p].leaf && node[p].leftChild == -1) {
      return initial(node[p].value, max(i, l), min(j, r));
    }
    assert(node[p].leftChild != -1);
    assert(node[p].rightChild != -1);
    int m = (l + r) / 2;
    if (j <= m) {
      return query(node[p].leftChild, l, m, i, j);
    }
    if (i >= m + 1) {
      return query(node[p].rightChild, m + 1, r, i, j);
    }
    return combine(node[p].query, query(node[p].leftChild, l, m, i, j),
                   query(node[p].rightChild, m + 1, r, i, j), l, m, r);
  }
  
  int minIndex, maxIndex;
  int root;
  
public:
  SegmentTree(int minIndex, int maxIndex, T defaultValue,
              const TreeCombineFunction<T,Q> &combine,
              const TreeLeafFunction<T,Q> &initial)
  : combine(combine), initial(initial), defaultValue(defaultValue),
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

struct gss {
  int s, l, r, k; // s: sum, l: sum from left, r: sum from right, k: gss result
};

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int m, n, x, a, b;
  scanf("%d", &n);
  
  auto combine = [](const gss &cur, const gss &a, const gss &b, int leftIndex, int midIndex, int rightIndex) {
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
