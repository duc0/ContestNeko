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

template <class T> vector<T> getArrayFromDiffArray(const vector<T> &s, int minIndex, int maxIndex) {
  vector<T> a(s.size());
  a[minIndex] = s[minIndex];
  for_inc_range(i, minIndex + 1, maxIndex) {
    a[i] = a[i - 1] + s[i];
  }
  return a;
}


template<class T> class ComboUtils {
  vector<T> factorial;
  vector<T> inverseFactorial;
  int maxN;
public:
  // Compute some combo numbers with up to n objects.
  ComboUtils(int n) {
    this->maxN = n;
    factorial.resize(n + 1);
    factorial[0] = 1;
    for_inc_range(i, 1, n) {
      factorial[i] = factorial[i - 1] * i;
    }
    inverseFactorial.resize(n + 1);
    T one = 1;
    for_inc_range(i, 0, n) {
      inverseFactorial[i] = one / factorial[i];
    }
  }
  
  T C(int n, int k) {
    assert (1 <= n && n <= maxN);
    assert (0 <= k && k <= n);
    return factorial[n] * inverseFactorial[k] * inverseFactorial[n - k];
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

#define MAXK 100

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int n, q;
  cin >> n >> q;
  
  vector<ModInt<int, MOD>> a(n + 1);
  for_inc_range(i, 1, n) {
    int x;
    cin >> x;
    a[i] = x;
  }
  
  vector<ModInt<int, MOD>> diff[MAXK + 2];
  
  diff[0] = a;
  for_inc_range(i, 1, MAXK + 1) {
    diff[i].resize(n + 1);
  }
  
  ComboUtils<ModInt<int, MOD>> comboUtils(MAXK + n - 1);
  repeat(q) {
    int l, r, k;
    cin >> l >> r >> k;
    diff[k + 1][l] += 1;
    if (r < n) {
      for_inc_range(kk, 0, k) {
        diff[k + 1 - kk][r + 1] -= comboUtils.C(kk + r - l, kk);
      } 
    }
  }
  
  vector<ModInt<int, MOD>> ans = diff[MAXK + 1];
  for_dec_range(k, MAXK, 0) {
    ans = getArrayFromDiffArray(ans, 1, n);
    for_inc_range(i, 1, n) {
      ans[i] = ans[i] + diff[k][i];
    }
  }
  
  for_inc_range(i, 1, n) {
    cout << ans[i] << " ";
  }
  
  return 0;
}
