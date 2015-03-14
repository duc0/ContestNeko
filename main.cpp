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

// Usage:
// Construct comboUtils(n): Compute some combo numbers with up to n objects.

template<class T> class ComboUtils {
  vector<T> factorial;
  vector<T> inverseFactorial;
  int maxN;
public:
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
  
  // Number of ways to choose k objects from n objects
  T C(int n, int k) {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] * inverseFactorial[k] * inverseFactorial[n - k];
  }
  
  // Number of ways to choose k objects from n objects and ordering is important
  T A(int n, int k) {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] * inverseFactorial[n - k];
  }
  
  // Number of ways to arrange n objects
  T P(int n) {
    assert (0 <= n && n <= maxN);
    return factorial[n];
  }
  
  // Number of ways to choose k objects from n objects, with repetition
  T repeatC(int n, int k) {
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

// k = 0
int solve(int n) {
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

int f[20][20], g[20][20];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
/*  for_inc_range(n, 1, 9) {
    cout << solve(n) << endl;
  }*/

  int MAX = 10;
  fill0(f);
  fill0(g);
  f[0][0] = 1;
  for_inc_range(n, 1, MAX) {
    f[n][0] = 1;
    g[n][0] = 1;
    for_inc_range(k, 1, n) {
      f[n][k] = 0;
      g[n][k] = 0;
      
      if (n >= 1) {
        f[n][k] += f[n - 1][k];
      }
      if (k >= 2) {
        f[n][k] += f[n - 2][k - 2];
      }
      if (k >= 1) {
        f[n][k] += 2 * g[n - 1][k - 1];
      }
      
      if (n >= 1) {
        g[n][k] += f[n - 1][k];
        if (k >= 1) {
          g[n][k] += g[n - 1][k - 1];
        }
      }
     
//      cout << f[n][k] << " ";
    }
//    cout << endl;
  }
  
  ComboUtils<int> combo(MAX);
  
  for_inc_range(n, 1, MAX) {
    int ret = 0;
    int sign = 1;
    for_inc_range(i, 0, n) {
      ret += sign * f[n][i] * combo.P(n - i);
      sign = -sign;
    }
    cout << ret << endl;
  }
  return 0;
  
  
}
