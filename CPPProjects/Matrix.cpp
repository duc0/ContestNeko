#define SUBMIT

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
#define INT_INF 2E9L
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

template<class T> class Matrix {
  vector<vector<T>> a;
  int nRow, nCol;
  
public:
  void init(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;
    a.resize(nRow);
    for_inc(r, nRow) {
      a[r].resize(nCol);
      for_inc(c, nCol) {
        a[r][c] = 0;
      }
    }
  }
  
  void init(int nRow, int nCol, const vector<vector<T>> &val) {
    assert(val.size() == nRow);
    assert(val[0].size() == nCol);
    init(nRow, nCol);
    for_inc(r, nRow) {
      for_inc(c, nCol) {
        a[r][c] = val[r][c];
      }
    }
  }
  
  void init(const vector<vector<T>> &val) {
    init((int)val.size(), (int)val[0].size(), val);
  }
  
  Matrix& operator=(const vector<vector<T>> &val) {
    init(val);
    return *this;
  }
  
  Matrix operator + (const Matrix &o) const {
    assert(nRow == o.nRow);
    assert(nCol == o.nCol);
    Matrix ret;
    ret.init(nRow, nCol);
    for_inc(r, nRow) for_inc(c, nCol) ret.a[r][c] = a[r][c] + o.a[r][c];
    return ret;
  }
  
  Matrix operator * (const Matrix &o) const {
    assert(nCol == o.nRow);
    Matrix ret;
    ret.init(nRow, o.nCol);
    for_inc(r, nRow) for_inc(c2, nCol) if (a[r][c2] != 0) for_inc(c, o.nCol) {
      ret.a[r][c] += a[r][c2] * o.a[c2][c];
    }
    return ret;
  }
  
  Matrix power(int k) const {
    assert(k >= 0);
    assert(nRow == nCol);
    if (k == 0) {
      Matrix ret;
      ret.init(nRow, nRow);
      for_inc(r, nRow) ret.a[r][r] = 1;
      return ret;
    } else if (k % 2 == 0) {
      Matrix tmp = power(k / 2);
      return tmp * tmp;
    } else {
      Matrix tmp = power(k - 1);
      return *this * tmp;
    }
  }
  
  vector<T>& operator[](int r) {
    return a[r];
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix) {
    stream << "[matrix: row = " << matrix.nRow << ", col = " << matrix.nCol << endl;
    for_inc(r, matrix.nRow) {
      for_inc(c, matrix.nCol) {
        stream << matrix.a[r][c] << " ";
      }
      stream << endl;
    }
    stream << "]" << endl;
    return stream;
  }
};

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

// Sample problem: CF 291 Div 2 - E

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n, x;
vector<int> d, cnt;

int main() {
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  cin >> n >> x;
  int m = 0;
  d.resize(n);
  for_inc(i, n) {
    cin >> d[i];
    m = max(m, d[i]);
  }
  cnt.resize(m + 1);
  for_inc(i, n) {
    cnt[d[i]]++;
  }
  
  Matrix<ModInt<int, MOD>> a;
  a.init(m + 1, m + 1);
  a[0][0] = 1;
  for_inc_range(r, 1, m - 1) {
    a[r][r + 1] = 1;
  }
  a[m][0] = 1;
  for_inc_range(c, 1, m) {
    a[m][c] = cnt[m - c + 1];
  }
  
  LOG(1, "Matrix: " << a);
  
  a = a.power(x);
  LOG(1, "Matrix power: " << x << " " << a);
  
  cout << (a[m][0] + a[m][m]).get() << endl;
  
  return 0;
}
