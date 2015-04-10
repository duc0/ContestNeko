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
    cout << 5 << endl;
    repeat(5) {
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
};

template <class T> class MaximumCliqueInterval {
  vector<int> maxClique;
  vector<int> culmMaxClique;
  int n;
  const IntervalList<T> &a;
public:
  MaximumCliqueInterval(const IntervalList<T> &a): a(a) {
    this->n = a.getSize();
    
    maxClique.resize(n + 1);
    culmMaxClique.resize(n + 1);
    
    for_inc_range(i, 1, n) {
      const Interval<T> &cur = a.getSortedRightInterval(i);
      int j = BinarySearch::binarySearchMin<int>(1, i, [&](int i){return a.getSortedRightInterval(i).getRight() >= cur.getLeft();});
      maxClique[i] = i - j + 1;
      culmMaxClique[i] = max(culmMaxClique[i - 1], maxClique[i]);
    }
  }
  
  // idx is the interval index when sorted by right endpoints.
  
  // Get max clique size that has the interval i when considering intervals 1..i.
  int getMaxCliqueSizeAtIdx(int idx) const {
    assert(1 <= idx && idx <= n);
    return maxClique[idx];
  }
  
  int getMaxCliqueSizeUntilIdx(int idx) const {
    assert(0 <= idx && idx <= n);
    return culmMaxClique[idx];
  }
  
  int getMaxCliqueSizeUntil(T x) const {
    int maxIdx = BinarySearch::binarySearchMax<int>(1, n, [&](int i){return a.getSortedRightInterval(i).getRight() <= x;});
    if (maxIdx == 0) return 0;
    return getMaxCliqueSizeUntilIdx(maxIdx);
  }
  
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

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input3.txt", "r", stdin);
#endif
  
  int nTest;
  cin >> nTest;
  for_inc_range(test, 1, nTest) {
    int n;
    cin >> n;
    IntervalList<int> a;
    for_inc_range(i, 1, n) {
      int l, r;
      cin >> l >> r;
      a.addInterval(l, r);
    }
  
    a.lock();
    
    MaximumCliqueInterval<int> mci(a);
    int ans = 0;
    for_inc_range(i, 1, n) {
      LOG(1, a.getSortedRightInterval(i));
      LOG(1, mci.getMaxCliqueSizeAtIdx(i) << " " << mci.getMaxCliqueSizeUntil(a.getSortedRightInterval(i).getLeft() - 1));
      
      int cur = mci.getMaxCliqueSizeAtIdx(i) + mci.getMaxCliqueSizeUntil(a.getSortedRightInterval(i).getLeft() - 1);
      ans = max(ans, cur);
    }
    
    for_inc_range(i, 1, n) {
      LOG(1, a.getInterval(i));
    }

    LOG(1, "Bruteforce: " << bruteForce(a));
    assert(ans == bruteForce(a));
    cout << "Case " << test << ": " << ans << endl;
  }
  return 0;
}
