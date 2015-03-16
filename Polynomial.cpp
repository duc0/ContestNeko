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

// Usage:
// Construct comboUtils(n): Compute some combo numbers with up to n objects.

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

template <class T> class Polynomial {
  vector<T> deg;
  int n;
  
public:
  Polynomial() {
    n = 0;
    deg.resize(1);
    deg[0] = 0;
  }
  
  Polynomial(int n) {
    deg.resize(n + 1);
    this->n = n;
  }
  
  Polynomial(const vector<T> &deg) : deg(deg) {
    this->n = (int)deg.size() - 1;
  }
  
  T getCoef(int k) const {
    assert ( 0 <= k);
    if (k > n) return 0;
    return deg[k];
  }
  
  static Polynomial<T> identity() {
    Polynomial<T> p(0);
    p.deg[0] = 1;
    return p;
  }
  
  Polynomial<T> operator+(const Polynomial<T> &p) {
    int newDeg = max(n, p.n);
    Polynomial<T> r(newDeg);
    for_inc_range(i, 0, newDeg) {
      r.deg[i] = getCoef(i) + p.getCoef(i);
    }
    return r;
  }
  
  Polynomial<T> operator*(const T &a) {
    Polynomial<T> r(n);
    for_inc_range(i, 0, n) {
      r.deg[i] = deg[i] * a;
    }
    return r;
  }
  
  Polynomial<T> operator*(const Polynomial<T> &p) {
    int newDeg = n + p.n;
    Polynomial<T> r(newDeg);
    for_inc_range(i, 0, newDeg) {
      r.deg[i] = 0;
      int jmin = max(0, i - p.n);
      int jmax = min(i, n);
      for_inc_range(j, jmin, jmax) {
        r.deg[i] += deg[j] * p.deg[i - j];
      }
    }
    return r;
  }
  
  void printDebug() const {
    ostringstream s;
    for_dec_range(i, n, 0) {
      if (deg[i] == 1 && i > 0) {
        if (i < n) s << " + ";
      } else if (deg[i] == -1 && i > 0) {
        s << " - ";
      } else {
        if (i < n && deg[i] >= 0) {
          s << " + ";
        }
        s << deg[i];
      }
      if (i >= 2) {
        s << "x^" << i;
      } else if (i == 1) {
        s << "x";
      }
    }
    LOG(1, s.str());
  }
  
  // (ax + b)^n
  static Polynomial<T> simplePower(T a, T b, int n, const ComboUtils<T> &comboUtils)  {
    assert(a != 0);
    assert(comboUtils.getMaxN() >= n);
    vector<T> aPower(n + 1);
    vector<T> bPower(n + 1);
    aPower[0] = 1;
    bPower[0] = 1;
    for_inc_range(i, 1, n) {
      aPower[i] = aPower[i - 1] * a;
      bPower[i] = bPower[i - 1] * b;
    }
    
    Polynomial<T> p(n);
    for_inc_range(i, 0, n) {
      p.deg[i] = bPower[n - i] * aPower[i] * comboUtils.C(n, i);
    }
    
    return p;
  }
  
  // h[k] = number of permutations with exactly k restricted positions.
  static Polynomial<T> getHitPolynomial(int n, const Polynomial<T> &rook, const ComboUtils<T> &comboUtils) {
    assert(comboUtils.getMaxN() >= n);
    Polynomial<T> hit(0);
    auto xminus1 = Polynomial<T>({-1, 1});
    auto p = Polynomial<T>::identity();
    for_inc_range(k, 0, n) {
      hit = hit + p * (rook.getCoef(k) * comboUtils.P(n - k));
      p = p * xminus1;
    }
    return hit;
  }
};



void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// k = 0
int solveSlow(int n) {
  vector<int> a(n + 1);
  for_inc_range(i, 1, n) a[i] = i;
  int ret = 0;
  do {
    bool good = true;
    for_inc_range(i, 1, n) if (a[i] == i - 1 || a[i] == i + 1) {
      good = false;
      break;
    }
    if (good) ret++;
  } while (next_permutation(a.begin() + 1, a.end()));
  return ret;
}

// CF 175 Div2 - E
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, k;
  cin >> n >> k;
  
  Polynomial<ModInt<int, MOD>> pxsquare({0,0,1});
  Polynomial<ModInt<int, MOD>> px({0,1});
  
  vector<Polynomial<ModInt<int, MOD>>> f(n + 1);
  vector<Polynomial<ModInt<int, MOD>>> g(n + 1);
  
  f[0] = Polynomial<ModInt<int, MOD>>(vector<ModInt<int, MOD>>{1});
  g[0] = Polynomial<ModInt<int, MOD>>(vector<ModInt<int, MOD>>{0});
  for_inc_range(i, 1, n) {
    f[i] = f[i] + f[i - 1] + g[i - 1] * px * ModInt<int, MOD>(2);
    if (i >= 2) {
      f[i] = f[i] + f[i - 2] * pxsquare;
    }
    g[i] = g[i] + f[i - 1] + g[i - 1] * px;
  }
  
  ComboUtils<ModInt<int, MOD>> comboUtils(n);
  auto hit = Polynomial<ModInt<int, MOD>>::getHitPolynomial(n, f[n], comboUtils);
  cout << hit.getCoef(k);
  return 0;
  
  
}
