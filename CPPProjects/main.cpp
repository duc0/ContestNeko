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
  template <class Q> ModInt& operator-=(const Q &y) {
    x = NumberTheory<T>::modulo(x - get(y), M);
    return *this;
  }
  template <class Q> bool operator!=(const Q &y) const {
    return x != get(y);
  }
  template <class Q> ModInt operator*(const Q &y) const {
    return ModInt((int64)x * get(y));
  }
  template <class Q> ModInt& operator*=(const Q &y) {
    x = NumberTheory<T>::modulo((int64)x * get(y), M);
    return *this;
  }
  template <class Q> ModInt operator/(const Q &y) const {
    return ModInt(
                  (int64)x * NumberTheory<T>::modularInverse(get(y), MOD));
  }
  template <class Q> ModInt& operator/=(const Q &y) {
    x = NumberTheory<T>::modulo((int64)x * NumberTheory<T>::modularInverse(get(y), MOD), M);
    return *this;
  }
  ModInt &operator=(const T &y) {
    x = NumberTheory<T>::modulo(y, M);
    return *this;
  }
  ModInt &operator=(const ModInt &y) {
    x = y.x;
    return *this;
  }
  template<class Q> bool operator ==(const Q &y) const {
    return x == get(y);
  }
  template<class Q> bool operator > (const Q &y) const {
    return x > get(y);
  }
  template<class Q> bool operator >= (const Q &y) const {
    return x >= get(y);
  }
  template<class Q> bool operator < (const Q &y) const {
    return x < get(y);
  }
  template<class Q> bool operator <= (const Q &y) const {
    return x <= get(y);
  }
  friend std::ostream& operator<< (std::ostream& stream, const ModInt& y) {
    stream << get(y);
    return stream;
  }
  
};

template<class T> class ComboUtils {
  vector<T> factorial;
  int maxN;
public:
  int getMaxN() const {
    return maxN;
  }
  
  ComboUtils(int n) {
    this->maxN = n;
    factorial.resize(n + 1);
    factorial[0] = 1;
    for_inc_range(i, 1, n) {
      factorial[i] = factorial[i - 1] * i;
    }
  }
  
  // Number of ways to choose k objects from n objects
  T C(int n, int k) const {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] / factorial[k] / factorial[n - k];
  }
  
  // Number of ways to choose k objects from n objects and ordering is important
  T A(int n, int k) const {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] / factorial[n - k];
  }
  
  // Number of ways to arrange n objects
  T P(int n) const {
    assert (0 <= n && n <= maxN);
    return factorial[n];
  }
  
  // Number of ways to choose k objects from n objects, with repetition
  T repeatC(int n, int k) const {
    return C(n + k - 1, k);
  }
  
  // Return a vector c[i] = C(i, k) for i <= n, O(n)
  static vector<T> getCombByK(int n, int k) {
    vector<T> c(n + 1);
    c[k] = 1;
    for_inc_range(i, k + 1, n) {
      c[i] = c[i - 1] * i / (i - k);
    }
    return c;
  }
  
  // Return a vector c[i] = C(n, i) for i <= n, O(n)
  static vector<T> getCombByN(int n) {
    vector<T> c(n + 1);
    c[0] = 1;
    for_inc_range(i, 1, n) {
      c[i] = c[i - 1] * (n - i + 1)/ i;
    }
    return c;
  }
  
  // Return a vector p[i] = a^i for i <= n, O(n)
  static vector<T> getPower(int n, T a) {
    vector<T> p(n + 1);
    p[0] = 1;
    for_inc_range(i, 1, n) {
      p[i] = p[i - 1] * a;
    }
    return p;
  }
};


void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  n++;
  vector<ModInt<int, MOD>> bell(n + 1);
  bell[0] = 1;
  ComboUtils<ModInt<int, MOD>> combo(n);
  for_inc_range(i, 0, n - 1) {
    bell[i + 1] = 0;
    vector<ModInt<int, MOD>> c = combo.getCombByN(i);
    for_inc_range(k, 0, i) {
      bell[i + 1] = bell[i + 1] + c[k] * bell[k];
    }
  }
  cout << bell[n] - bell[n - 1] << endl;
  return 0;
}
