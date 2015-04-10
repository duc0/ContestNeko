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

#define LOG(l, x)                                                              \
if (l <= LOGLEVEL)                                                           \
cout << x << endl

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
  if (r < 0)
    r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  int n = 1000;
  cout << n << endl;
  repeat(n) {
    repeat(1000) {
      cout << (char)(rand() % 1 + 'a');
    }
    cout << endl;
  }
  fclose(stdout);
}

template <int BASE, int64 MODULO> class StringHash {
  template <int B, int64 M> friend class StringHasher;
  vector<int64> hash;
  
public:
  size_t getSize() const { return hash.size(); }
};

template <int BASE, int64 MODULO> class StringHasher {
  static int64 getBasePower(int n) {
    static vector<int64> power; // cache
    if (n > (int)power.size() - 1) {
      int cur = (int)power.size() - 1;
      power.resize(n + 1);
      for_inc_range(i, cur + 1, n) {
        if (i == 0) {
          power[i] = 1;
        } else {
          power[i] = (power[i - 1] * BASE) % MODULO;
        }
      }
    }
    return power[n];
  }
  
public:
  template <class Iterator>
  static StringHash<BASE, MODULO> getHash(Iterator begin, Iterator end) {
    StringHash<BASE, MODULO> h;
    int n = (int)(end - begin);
    h.hash.resize(n);
    int idx = 0;
    int64 last = 0;
    for (auto it = begin; it != end; ++it) {
      h.hash[idx] = (last * BASE + *it) % MODULO;
      last = h.hash[idx];
      idx++;
    }
    return h;
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh) {
    return sh.hash[sh.getSize() - 1];
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh, int first,
                            int len) {
    if (len == 0) return 0;
    assert(0 <= first && first < sh.getSize());
    assert(len >= 1);
    assert(first + len - 1 < sh.getSize());
    
    int last = first + len - 1;
    
    if (first == 0)
      return sh.hash[last];
    
    int64 ret =
    (sh.hash[last] - sh.hash[first - 1] * getBasePower(len)) % MODULO;
    if (ret < 0)
      ret += MODULO;
    return ret;
  }
  
  static int64 getHashValueConcat(const StringHash<BASE, MODULO> &sh1,
                                  const StringHash<BASE, MODULO> &sh2) {
    
    return (getHashValue(sh1) * getBasePower((int)sh2.getSize()) +
            getHashValue(sh2)) %
    MODULO;
  }
};

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

#define BASE 31
#define HMOD 1000001927

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  string ss;
  cin >> ss;
  
  vector<int> s(n);
  for_inc(i, n) s[i] = ss[i] - 'a';
  
  StringHash<BASE, HMOD> rhash = StringHasher<BASE, HMOD>::getHash(s.rbegin(), s.rend());
  StringHash<BASE, HMOD> hash = StringHasher<BASE, HMOD>::getHash(s.begin(), s.end());
  
  int maxOdd = (BinarySearch::binarySearchMax<int>(0, n / 2, [&](int x) {
    int l = 2 * x + 1;
    for_inc(i, n - l + 1) {
      if (StringHasher<BASE, HMOD>::getHashValue(hash, i, l) == StringHasher<BASE, HMOD>::getHashValue(rhash, n - i - l, l)) {
        return true;
      }
    }
    return false;
  })) * 2 + 1;

  int maxEven = (BinarySearch::binarySearchMax<int>(0, n / 2, [&](int x) {
    int l = 2 * x;
    for_inc(i, n - l + 1) {
      if (StringHasher<BASE, HMOD>::getHashValue(hash, i, l) == StringHasher<BASE, HMOD>::getHashValue(rhash, n - i - l, l)) {
        return true;
      }
    }
    return false;
  })) * 2;
  
  cout << max(maxOdd, maxEven) << endl;
  
  return 0;
}
