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
#define INT64_INF 2E18LL

#define MOD 1000000007
inline int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0)
    r += MOD;
  return r;
}

#define UPDATE_MIN(a, b) ((a) = (a) < (b) ? (a) : (b))

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  repeat(2000) cout << 1;
  fclose(stdout);
}

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

string s;
vector<vector<int>> f, minPrint, val;

int main() {
  // testGen();
  // freopen("biginput1.txt", "r", stdin);
  // freopen("output1.txt", "w", stdout);

  cin >> s;

  int n = (int)s.length();

  f.resize(n + 1);
  for_inc_range(i, 1, n) f[i].resize(n + 1);

  minPrint.resize(n + 1);
  for_inc_range(i, 1, n) minPrint[i].resize(n + 1);
  for_inc_range(i, 1, n) for_inc_range(j, 1, n) minPrint[i][j] = INT_INF;

  val.resize(n + 1);
  for_inc_range(i, 1, n) val[i].resize(n + 1);
  for_inc_range(i, 1, n) {
    val[i][i] = s[i - 1] - '0';
    for_inc_range(j, i + 1, n) {
      val[i][j] = MODP(val[i][j - 1] * 2 + (s[j - 1] - '0'));
    }
  }

  f[1][1] = 1;
  minPrint[1][1] = 1;

  for_inc_range(i, 1, n) {
    if (s[i - 1] == '0')
      continue;

    for_inc_range(j, i, n - 1) {
      if (minPrint[i][j] == INT_INF)
        continue;

      f[i][j + 1] = MODP(f[i][j + 1] + f[i][j]);
      UPDATE_MIN(minPrint[i][j + 1], minPrint[i][j]);

      if (s[j] == '0')
        continue;

      int k = 2 * j - i + 1;
      if (k <= n) {
        if (s.substr(i - 1, j - i + 1) > s.substr(j, k - j)) {
          ++k;
        }
      }
      if (k <= n) {
        f[j + 1][k] = MODP(f[j + 1][k] + f[i][j]);
        UPDATE_MIN(minPrint[j + 1][k], minPrint[i][j] + 1);
      }
    }
  }

  int ret = 0;

  BigInteger<2> bestL = BigInteger<2>::getMaxValue();

  vector<int> digit(n);
  for_inc(i, n) digit[i] = s[i] - '0';

  for_inc_range(i, 1, n) {
    if (minPrint[i][n] != INT_INF) {
      ret = MODP(ret + f[i][n]);
      BigInteger<2> a = BigInteger<2>(minPrint[i][n]);
      BigInteger<2> b = BigInteger<2>(digit.begin() + i - 1, digit.end());
      bestL = min(bestL, a + b);
    }
  }

  cout << ret << endl;
  cout << bestL.mod<int64>(MOD) << endl;

  return 0;
}
