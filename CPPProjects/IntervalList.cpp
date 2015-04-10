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
  freopen("input3.txt", "w", stdout);
  cout << 100 << endl;
  repeat(100) {
    cout << 7 << endl;
    repeat(7) {
      int l = rand() % 10 + 1;
      int len = rand() % 10 + 1;
      int r = l + len;
      cout << l << " " << r << endl;
    }
  }
  fclose(stdout);
}

class BinarySearch {
public:
  template<class T> static T binarySearchMin(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = maxIndex + 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        rightIndex = midIndex - 1;
      } else {
        leftIndex = midIndex + 1;
      }
    }
    return ret;
  }
  
  template<class T> static T binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = minIndex - 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        leftIndex = midIndex + 1;
      } else {
        rightIndex = midIndex - 1;
      }
    }
    return ret;
  }
  
  static double binarySearchMaxReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        ret = m;
        l = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
  static double binarySearchMinReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        l = m;
        ret = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
};

template<class T> class Interval : public pair<T, T> {
public:
  Interval() {}
  
  Interval(T l, T r) {
    set(l, r);
  }
  
  void set(T l, T r) {
    assert(l <= r);
    this->first = l;
    this->second = r;
  }
  
  inline int getLeft() const {
    return this->first;
  }
  
  inline int getRight() const {
    return this->second;
  }
  
  inline bool contains(T x) const {
    return this->first <= x && x <= this->second;
  }
  
  static bool compareRight(const Interval<T> &i1, const Interval<T> &i2) {
    return i1.getRight() < i2.getRight();
  }
  
  static bool compareLeft(const Interval<T> &i1, const Interval<T> &i2) {
    return i1.getLeft() < i2.getLeft();
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const Interval<T>& i) {
    stream << "[interval: " << i.getLeft() << " to " << i.getRight() << "]";
    return stream;
  }
};

template<class T> class IntervalList {
  vector<Interval<T>> a;
  bool _lock = false;
  
  vector<int> sortRight;
  vector<int> sortLeft;
  
  int n;
public:
  void addInterval(const Interval<T> &i) {
    a.emplace_back(i);
  }
  
  void addInterval(T l, T r) {
    a.emplace_back(l, r);
  }
  
  void lock() {
    _lock = true;
    
    n =  (int) a.size();
    
    sortRight.resize(n);
    for_inc(i, n) {
      sortRight[i] = i;
    }
    sort(sortRight.begin(), sortRight.end(), [&] (int i, int j) {
      return a[i].getRight() < a[j].getRight();
    });
    
    sortLeft.resize(n);
    for_inc(i, n) {
      sortLeft[i] = i;
    }
    sort(sortLeft.begin(), sortLeft.end(), [&] (int i, int j) {
      return a[i].getLeft() < a[j].getLeft();
    });
  }
  
  const Interval<T>& getInterval(int idx) const {
    assert(_lock);
    assert(1 <= idx && idx <= n);
    return a[idx - 1];
  }
  
  const Interval<T>& getSortedLeftInterval(int rank) const {
    assert(_lock);
    return a[sortLeft[rank - 1]];
  }
  
  const Interval<T>& getSortedRightInterval(int rank) const {
    assert(_lock);
    return a[sortRight[rank - 1]];
  }
  
  int getSize() const {
    return n;
  }
  
  // Compress coordinates to range 0 .. n - 1
  void compressCoordinates() {
    set<T> c;
    for_inc(i, n) {
      c.insert(a[i].getLeft());
      c.insert(a[i].getRight());
    }
    vector<T> v(c.begin(), c.end());
    map<T, int> m;
    for_inc(i, v.size()) {
      m[v[i]] = i;
    }
    for_inc(i, n) {
      a[i].first = m[a[i].first];
      a[i].second = m[a[i].second];
    }
  }
  
  // Create a new interval list with right endpoints < x.
  IntervalList<T> filterRightBefore(T x) const {
    IntervalList<T> ret;
    vector<int> mapId(n);
    for_inc(i, n) {
      if (a[i].getRight() < x) {
        ret.a.push_back(a[i]);
        mapId[i] = (int) ret.a.size() - 1;
      }
    }
    for_inc(i,n) {
      if (a[sortLeft[i]].getRight() < x) {
        ret.sortLeft.push_back(mapId[sortLeft[i]]);
      }
      if (a[sortRight[i]].getRight() < x) {
        ret.sortRight.push_back(mapId[sortRight[i]]);
      }
    }
    ret._lock = true;
    ret.n = (int) ret.a.size();
    return ret;
  }
};

template <class T> class MaximumCliqueInterval {
  vector<int> maxLeft;
  vector<int> maxRight;
  vector<int> culmMaxRight;
  int n;
  const IntervalList<T> &a;
public:
  MaximumCliqueInterval(const IntervalList<T> &a): a(a) {
    this->n = a.getSize();
    maxLeft.resize(n + 1);
    maxRight.resize(n + 1);
    culmMaxRight.resize(n + 1);
    
    // Sweeping line
    int il = 1, ir = 1;
    int cur = 0;
    while (il <= n || ir <= n) {
      bool chooseL;
      if (il > n) {
        chooseL = false;
      } else if (ir > n) {
        chooseL = true;
      } else {
        // Note the tie breaker
        chooseL = a.getSortedLeftInterval(il).getLeft() <= a.getSortedRightInterval(ir).getRight();
      }
      if (chooseL) {
        cur++;
        maxLeft[il] = cur;
        il++;
      } else {
        maxRight[ir] = cur;
        culmMaxRight[ir] = max(culmMaxRight[ir - 1], cur);
        cur--;
        ir++;
      }
    }
    
  }
  
  // idx is the interval index when sorted by left endpoints.
  // Get max clique size that has the interval i when considering intervals 1..i.
  int getMaxCliqueSizeAtIdx(int idx) const {
    assert(1 <= idx && idx <= n);
    return maxLeft[idx];
  }
  
  // Get max clique size when all the intervals have the right endpoint <= x
  int getMaxCliqueSizeUntil(T x) const {
    int maxIdx = BinarySearch::binarySearchMax<int>(1, n, [&](int i){return a.getSortedRightInterval(i).getRight() <= x;});
    if (maxIdx == 0) return 0;
    return culmMaxRight[maxIdx];
  }
  
  int getMaxCliqueSize() const {
    return culmMaxRight[n];
  }
  
};

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


int bruteForce(IntervalList<int> &a) {
  int n = a.getSize();
  
  int ans = 0;
  for_inc_range(i, 1, n) {
    int p1 = a.getInterval(i).getLeft();
    for_inc_range(j, 1, n) {
      int p2 = a.getInterval(j).getLeft();
      int cur = 0;
      for_inc_range(k, 1, n) {
        if (a.getInterval(k).contains(p1) || a.getInterval(k).contains(p2)) {
          ++cur;
        }
        ans = max(ans, cur);
      }
    }
  }
  return ans;
}

// A segment tree with two queries:
// add(i, j, v): add all elements in range [i, j] by V
// queryMax(i, j)
// all 0 initially.
template<class T> struct MaxTreeQ ;
template<class T> class MaxTree : public SegmentTree<T, MaxTreeQ<T>> {
public:
  MaxTree(int minIndex, int maxIndex) :
  SegmentTree<T, MaxTreeQ<T>>(minIndex, maxIndex, 0,
                              [](const MaxTreeQ<T> &l, const MaxTreeQ<T> &r) {return MaxTreeQ<T>(max(l.queryMax, r.queryMax), 0);},
                              [](const MaxTreeQ<T> &cur, T oldV, T newV, int l, int r) {
                                return MaxTreeQ<T>(cur.queryMax + newV, cur.lazy + newV);
                              },
                              [](MaxTreeQ<T> &cur, MaxTreeQ<T> &lChild, MaxTreeQ<T> &rChild, T curV, int l, int m, int r) {
                                lChild.lazy += cur.lazy;
                                rChild.lazy += cur.lazy;
                                lChild.queryMax += cur.lazy;
                                rChild.queryMax += cur.lazy;
                                cur.lazy = 0;
                              }
                              )
  {
  }
  
  T queryMax(int l, int r) {
    return SegmentTree<T, MaxTreeQ<T>>::query(l, r).queryMax;
  }
  
  T queryMax() {
    return SegmentTree<T, MaxTreeQ<T>>::query().queryMax;
  }
  
  void add (int l, int r, T v) {
    SegmentTree<T, MaxTreeQ<T>>::update(l, r, v);
  }
};

template<class T> struct MaxTreeQ {
  T queryMax = 0;
  T lazy = 0;
  MaxTreeQ() {};
  MaxTreeQ(T queryMax, T lazy) {
    this->queryMax = queryMax;
    this->lazy = lazy;
  }
};



int solve(const IntervalList<int> &aa) {
  IntervalList<int> a = aa;
  int n = a.getSize();
  
  a.compressCoordinates();
  
  MaximumCliqueInterval<int> mci(a);
  
  int minCoord = a.getSortedLeftInterval(1).getLeft();
  int maxCoord = a.getSortedRightInterval(n).getRight();
  
  MaxTree<int> tree(minCoord, maxCoord);
  
  int ans = 0;
  int j = 1;
  for_inc_range(i, 1, n) {
    int m = mci.getMaxCliqueSizeAtIdx(i);
    
    const Interval<int> &cur = a.getSortedLeftInterval(i);
    int x = cur.getLeft();
    
    while (j <= n && a.getSortedRightInterval(j).getRight() < x) {
      const Interval<int> &add = a.getSortedRightInterval(j);
      tree.add(add.getLeft(), add.getRight(), 1);
      j++;
      //LOG(1, "Add " << add);
    }
    
    //LOG(1, "Query " << tree.query().queryMax);
    ans = max(ans, m + tree.queryMax());
  }
  
  return ans;
}


// Cisco 2015 - Touching segments
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input3.txt", "r", stdin);
#endif
  
  int nTest;
  scanf("%d", &nTest);
  for_inc_range(test, 1, nTest) {
    int n;
    scanf("%d", &n);
    IntervalList<int> a;
    for_inc_range(i, 1, n) {
      int l, r;
      scanf("%d%d", &l, &r);
      a.addInterval(l, r);
    }
    
    a.lock();
    
    int ans = solve(a);
    //LOG(1, "Bruteforce: " << bruteForce(a));
    cout << "Case " << test << ": " << ans << endl;
    assert(ans == bruteForce(a));
  }
  return 0;
}
