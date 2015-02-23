#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
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
  static T modulo(int64 a, T b) {
    T r = a % b;
    if (r < 0)
      r += b;
    return r;
  }
  static T modularInverse(T a, T m) {
    T x, y;
    extendedEuclid(a, m, x, y);
    return modulo(x, m);
  }
};

template <class T, T M> class ModInt {
  T x = 0;
  static T modp(int64 x) { return NumberTheory<T>::modulo(x, M); }
  static T get(ModInt x) { return x.get(); }
  static T get(T x) { return x; }

public:
  ModInt() : ModInt(0) {}
  ModInt(T y) { x = modp(y); }
  T get() { return x; }
  template <class Q> ModInt operator+(const Q &y) {
    return ModInt(modp(x + get(y)));
  }
  template <class Q> ModInt operator-(const Q &y) {
    return ModInt(modp(x - get(y)));
  }
  template <class Q> ModInt operator*(const Q &y) {
    return ModInt(modp((int64)x * get(y)));
  }
  template <class Q> ModInt operator/(const Q &y) {
    return ModInt(
        modp((int64)x * NumberTheory<T>::modularInverse(get(y), MOD)));
  }
  template <class Q> ModInt &operator=(const Q &y) {
    x = modp(get(y));
    return *this;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Sample: CF263 _ B

int n;
vector<int> parent;
vector<int> color;
vector<vector<int>> child;

vector<vector<int>> f;

void dfs(int u) {
  ModInt<int, MOD> prod = 1, f0, f1;
  for (auto &v : child[u]) {
    dfs(v);
    prod = prod * (f[0][v] + f[1][v]);
  }
  if (color[u] == 1) {
    f0 = 0;
    f1 = prod;
  } else {
    f0 = prod;
    f1 = 0;
    for (auto &v : child[u]) {
      if (f[1][v] > 0) {
        f1 = f1 + prod * f[1][v] / (f[0][v] + f[1][v]);
      }
    }
  }
  f[0][u] = f0.get();
  f[1][u] = f1.get();
}

int main() {
  // freopen("input2.txt", "r", stdin);
  cin >> n;
  parent.resize(n + 1);
  child.resize(n + 1);
  color.resize(n + 1);
  parent[1] = -1;
  int p;
  for_inc_range(u, 2, n) {
    cin >> p;
    parent[u] = p + 1;
    child[p + 1].push_back(u);
  }
  for_inc_range(u, 1, n) { cin >> color[u]; }

  f.resize(2);
  for_inc_range(i, 0, 1) { f[i].resize(n + 1); }
  dfs(1);
  cout << f[1][1] << endl;
  return 0;
}
