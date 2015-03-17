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
#include <sstream>

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

#define MAXN 200200
pair<int, int> p[MAXN];
int minVal[MAXN];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  
  for_inc_range(i, 1, n) {
    int x, w;
    cin >> x >> w;
    p[i] = make_pair(x, w);
  }
  
  sort(p + 1, p + 1 + n);
  
  int longest = 1;
  minVal[1] = p[1].first + p[1].second;
  
  longest = 1;
  for_inc_range(i, 2, n) {
    int k = BinarySearch::binarySearchMax<int>(1, longest, [&](int l) {return minVal[l] <= p[i].first - p[i].second;});
    if (k == longest) {
      longest++;
      minVal[longest] = p[i].first + p[i].second;
    } else {
      minVal[k + 1] = min(minVal[k + 1], p[i].first + p[i].second);
    }
  }

  cout << longest << endl;
  return 0;
}
