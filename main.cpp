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

template <class T> class NumberTheory {
  static void extendedEuclid(T a, T b, T &x, T &y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return;
    }
    T x2;
    extendedEuclid(b, a % b, x2, x);
    y = x2 - (a / b) * x;
  }
  
public:
  static inline T modulo(int64 a, T b) {
    T r = a % b;
    if (r < 0)
      r += b;
    return r;
  }
  static inline T modularInverse(T a, T m) {
    T x, y;
    extendedEuclid(a, m, x, y);
    return modulo(x, m);
  }
};

template <class T, T M> class ModInt {
  T x = 0;
  static inline T get(ModInt x) { return x.get(); }
  static inline T get(T x) { return x; }
  
public:
  ModInt() : ModInt(0) {}
  ModInt(int64 y) { x = NumberTheory<T>::modulo(y, M); }
  T get() const { return x; }
  template <class Q> ModInt operator+(const Q &y) const {
    return ModInt(x + get(y));
  }
  template <class Q> ModInt& operator+=(const Q &y) {
    x = NumberTheory<T>::modulo(x + get(y), M);
    return *this;
  }
  template <class Q> ModInt operator-(const Q &y) const {
    return ModInt(x - get(y));
  }
  template <class Q> bool operator!=(const Q &y) const {
    return x != get(y);
  }
  template <class Q> ModInt operator*(const Q &y) const {
    return ModInt((int64)x * get(y));
  }
  template <class Q> ModInt operator/(const Q &y) const {
    return ModInt(
                  (int64)x * NumberTheory<T>::modularInverse(get(y), MOD));
  }
  ModInt &operator=(const T &y) {
    x = NumberTheory<T>::modulo(y, M);
    return *this;
  }
  ModInt &operator=(const ModInt &y) {
    x = y.x;
    return *this;
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const ModInt& y) {
    stream << get(y);
    return stream;
  }
  
};
void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
#ifndef SUBMIT
  freopen("input5.txt", "r", stdin);
#endif
  
  int n, k;
  string s;
  cin >> n >> k;
  cin >> s;
  
  vector<ModInt<int, MOD>> combKMinus1(n + 1);
  if (k >= 1) {
    combKMinus1[k - 1] = 1;
    for_inc_range(i, k, n) {
      combKMinus1[i] = combKMinus1[i - 1] * i / (i - (k - 1));
    }
  }

  vector<ModInt<int, MOD>> combKMinus2(n + 1);
  if (k >= 2) {
    combKMinus2[k - 2] = 1;
    for_inc_range(i, k - 1, n) {
      combKMinus2[i] = combKMinus2[i - 1] * i / (i - (k - 2));
    }
  }
  
  vector<ModInt<int, MOD>> tenPower(n + 1);
  tenPower[0] = 1;
  for_inc_range(i, 1, n) {
    tenPower[i] = tenPower[i - 1] * 10;
  }

  ModInt<int, MOD> begin, end, ret, sum, last, sum1;
  
  if (k == 0) {
    begin = 0;
    for_inc_range(l, 1, n) {
      begin = begin * 10 + s[l - 1] - '0';
    }
    cout << begin << endl;
    return 0;
  }
  for_inc_range(l, 1, n - 1) {
    begin = begin * 10 + s[l - 1] - '0';
    if (n - l - 1 < k - 1) {
      break;
    }
    LOG(1, "Begin: " << begin);
    LOG(2, "Comb: " << k - 1 << " " << n - l - 1 << " " << combKMinus1[n - l - 1]);
    ret = ret + begin * combKMinus1[n - l - 1];
  }
  LOG(1, "Begin val: " << ret);
  
  end = 0;
  for_inc_range(l, 1, n - 1) {
    end = end + tenPower[l - 1] * (s[n - l] - '0');
    if (n - l - 1 < k - 1) {
      break;
    }
    LOG(1, "End: " << end);    
    ret = ret + end * combKMinus1[n - l - 1];
  }
  LOG(1, "End val: " << ret);
  
  if (n >= 3 && k >= 2) {
    sum = 0;
    last = s[n - 1 - 1] - '0';
    for_inc_range(i, 2, n - 1) {
      sum = sum + s[i - 1] - '0';
    }
    sum1 = sum;
    LOG(1, "Sum : " << sum);
    LOG(1, "Last " << last);
    ret = ret + sum * combKMinus2[n - 3];
    for_inc_range(l, 2, n - 2) {
      sum = sum - last;
      sum = sum * 10;
      sum1 = sum1 - (s[l - 1] - '0');
      sum = sum + sum1;
      last = last + tenPower[l - 1] * (s[n - l - 1] - '0');
      LOG(2, "Last " << last);
      LOG(2, "Sum1 " << sum1);
      ret = ret + sum * combKMinus2[n - l - 2];
    }
  }
  
  cout << ret << endl;
  return 0;
}
