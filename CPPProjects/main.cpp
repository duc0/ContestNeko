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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

struct Range {
  int64 l, r;
  int id;
};

void noSol() {
  cout << "No" << endl;
  exit(0);
}

vector<Range> range;

vector<pair<int64, int>> point;

#define MAXN 200200
int lBound[MAXN];
bool used[MAXN];
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int nRange;
  
  cin >> nRange;
  nRange--;
  
  int nPoint;
  
  cin >> nPoint;

  int64 lastL = -1, lastR = -1;
  for_inc_range(i, 1, nRange + 1) {
    int64 l, r;
    cin >> l >> r;
    if (lastL != -1) {
      range.push_back(Range{l - lastR, r - lastL, i - 1});
    }
    lastL = l;
    lastR = r;
  }
  
  auto cmpRange = [](const Range &range1, const Range &range2) {
    return (range1.l < range2.l) || (range1.l == range2.l && range1.id < range2.id);
  };
  
  for_inc_range(i, 1, nPoint) {
    int64 x;
    
    cin >> x;
    point.push_back(make_pair(x, i));
  }
  
  sort(range.begin(), range.end(), cmpRange);
  sort(point.begin(), point.end());
  
  for_inc(rangeId, nRange) {
    int64 lRange = range[rangeId].l;
    int start = BinarySearch::binarySearchMin<int>(0, nPoint - 1, [&](int i){return point[i].first >= lRange;});
    if (start == nPoint) {
      noSol();
    }
    lBound[rangeId] = start;
    
  }
  
  return 0;
}
