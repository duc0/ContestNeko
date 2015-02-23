#include <cstdio>
#include <algorithm>
#include <cstring>

#define NDEBUG
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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)

#define for_inc(i,x) for(auto i=0; i < x;++i)
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
#define for_inc_range(i,x,y) for (auto i=x; i<=y; ++i)
#define for_dec_range(i,x,y) for (auto i=x; i>=y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

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
  T get() { return x; }
  template <class Q> ModInt operator+(const Q &y) {
    return ModInt(x + get(y));
  }
  template <class Q> ModInt operator-(const Q &y) {
    return ModInt(x - get(y));
  }
  template <class Q> ModInt operator*(const Q &y) {
    return ModInt((int64)x * get(y));
  }
  template <class Q> ModInt operator/(const Q &y) {
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
};

#define MAXN 5100

int n, a, b, k;
ModInt<int, MOD> f[MAXN][MAXN], s[MAXN][MAXN];

ModInt<int, MOD> getSum(int d, int i, int j) {
  return s[d][j] - s[d][i - 1];
}

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  cin >> n >> a >> b >> k;
  fill0(f);
  fill0(s);
  
  f[0][a] = 1;

  s[0][0] = 0;
  for_inc_range(i, 1, n) {
    s[0][i] = s[0][i - 1] + f[0][i];
  }
  
  for_inc_range(d, 1, k) {
    s[d][0] = 0;
    for_inc_range(i, 1, n) {
      if (i == b) continue;
      if (i > b) {
        f[d][i] = getSum(d - 1, (i + b) / 2 + 1, n) - f[d - 1][i];
      } else {
        int r = (i + b) / 2;
        if ((i + b) % 2 == 0) r--;
        f[d][i] = getSum(d - 1, 1, r) - f[d - 1][i];
      }
      
      s[d][i] = s[d][i - 1] + f[d][i];
    }
  }
  
  ModInt<int, MOD> ret = 0;
  for_inc_range(i, 1, n) {
    ret = ret + f[k][i];
  }
  cout << ret.get() << endl;
  return 0;
}