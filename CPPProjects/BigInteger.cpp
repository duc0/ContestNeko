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

template <int base = 10> class BigInteger {
  vector<int> d;
  bool isInfinity = false;
  
  inline int getDigit(int i) const { return i >= d.size() ? 0 : d[i]; }
  
public:
  static BigInteger getMaxValue() {
    BigInteger r;
    r.isInfinity = true;
    return r;
  }
  
  template <class Iterator> BigInteger(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; ++it) {
      d.push_back(*it);
    }
    reverse(d.begin(), d.end());
  }
  
  BigInteger() : BigInteger(0) {}
  
  template <class T> BigInteger(T n) {
    if (n == 0) {
      d.push_back(0);
      return;
    }
    while (n > 0) {
      d.push_back(n % base);
      n /= base;
    }
  }
  
  BigInteger operator+(const BigInteger &a) {
    BigInteger r;
    size_t m = max(d.size(), a.d.size());
    r.d.resize(m + 1);
    for (int i = 0, c = 0; i < m + 1; ++i) {
      r.d[i] = getDigit(i) + a.getDigit(i) + c;
      if (r.d[i] >= base) {
        c = 1;
        r.d[i] -= base;
      } else
        c = 0;
    }
    return r;
  }
  
  template <class T> T mod(T p) {
    T r = 0;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
      r = (r * base + *it) % p;
    }
    return r;
  }
  
  bool operator<(const BigInteger &a) const {
    if (a.isInfinity) {
      return true;
    }
    if (isInfinity) {
      return false;
    }
    size_t m = max(d.size(), a.d.size());
    for (int i = (int)m - 1; i >= 0; --i) {
      if (getDigit(i) < a.getDigit(i))
        return true;
      if (getDigit(i) > a.getDigit(i))
        return false;
    }
    return false;
  }
  
  string toString() {
    string s;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
      s += (char)(*it + '0');
    }
    return s;
  }
};