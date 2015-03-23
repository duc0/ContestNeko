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
#include <bitset>

using namespace std;

#define LOG(l, x)                                                              \
if (l <= LOGLEVEL)                                                           \
cout << x << endl

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
  if (r < 0)
    r += MOD;
  return r;
}

template <class T> class FourierTransform {
  // (a^b) % p
  static int64 power(int64 a, int64 b, int64 p) {
    int64 r = 1;
    while (b > 0) {
      if (b % 2 == 1) {
        r = (r * a) % p;
      }
      a = (a * a) % p;
      b /= 2;
    }
    return r;
  }
  
  static const int64 P = 2013265921;   // P == 15*(1<<27)+1
  static const int64 ROOT = 440564289; // order (2^27)
  
  vector<int64> e, er;
  void fft(vector<T> &x, int d = 1) {
    int n = (int)x.size();
    if (n != e.size()) {
      e.resize(n);
      er.resize(n);
      e[0] = 1;
      e[1] = power(ROOT, (1 << 27) / n, P);
      er[0] = 1;
      er[1] = power(e[1], P - 2, P);
      for_inc_range(i, 2, n - 1) {
        e[i] = (e[i - 1] * e[1]) % P;
        er[i] = (er[i - 1] * er[1]) % P;
      }
    }
    if (d == -1) {
      swap(e, er);
    }
    for_inc(i, n) {
      int j = 0;
      for (int k = 1; k < n; k <<= 1, j <<= 1) {
        if (k & i) {
          j++;
        }
      }
      j >>= 1;
      if (i < j) {
        swap(x[i], x[j]);
      }
    }
    int k = 0;
    while ((1 << k) < n) {
      k++;
    }
    for (int s = 1; s < n; s <<= 1) {
      k--;
      for (int i = 0; i < n; i += 2 * s)
        for_inc(j, s) {
          int64 u = x[i + j];
          int64 v = (x[i + j + s] * e[j << k]);
          x[i + j] = (u + v) % P;
          if (x[i + j] < 0)
            x[i + j] += P;
          x[i + j + s] = (u - v) % P;
          if (x[i + j + s] < 0)
            x[i + j + s] += P;
        }
    }
    if (d == -1) {
      swap(e, er);
    }
  }
  
  vector<T> convolution(const vector<T> &s1, const vector<T> &s2) {
    vector<T> a = s1;
    vector<T> b = s2;
    int n = 1;
    while (n < (int)max(a.size(), b.size())) {
      n *= 2;
    }
    n *= 2;
    a.resize(n);
    b.resize(n);
    fft(a);
    fft(b);
    int64 tmp = power(n, P - 2, P);
    for_inc(i, n) {
      a[i] = ((((int64)a[i] * b[i]) % P) * tmp) % P;
    }
    fft(a, -1);
    return a;
  }
  
public:
  vector<T> crossCorelation(const vector<T> &s1, const vector<T> &s2) {
    vector<T> a = s1;
    vector<T> b = s2;
    reverse(b.begin(), b.end());
    return convolution(a, b);
  }
};

char validC[] = {'A', 'C', 'G', 'T'};
void testGen() {
  freopen("biginput1.txt", "w", stdout);
  int n = 200000;
  int m = 1000;
  int k = 10;
  cout << n << " " << m << " " << k << endl;
  for_inc(i, n) {
    int c = rand() % 4;
    cout << validC[c];
  }
  cout << endl;
  for_inc(i, m) {
    int c = rand() % 4;
    cout << validC[c];
  }
  cout << endl;
  
  fclose(stdout);
}

vector<int> validPos[4], conv[4];


// CF 296 - D
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("biginput1.txt", "r", stdin);
  // testGen();
#endif
  
  int ls, lt, k;
  cin >> ls >> lt >> k;
  
  string s, t;
  cin >> s >> t;
  
  vector<int> prev(ls), next(ls);
  
  for_inc(x, 4) {
    validPos[x].resize(ls);
    char c = validC[x];
    
    for_inc(i, ls) {
      prev[i] = -1;
      if (i > 0) {
        prev[i] = prev[i - 1];
      }
      if (s[i] == c) {
        prev[i] = i;
      }
    }
    
    for_dec(i, ls) {
      next[i] = ls;
      if (i + 1 < ls) {
        next[i] = next[i + 1];
      }
      if (s[i] == c) {
        next[i] = i;
      }
    }
    
    for_inc(i, ls) {
      if ((prev[i] != -1 && prev[i] >= i - k) ||
          (next[i] != ls && next[i] <= i + k)) {
        validPos[x][i] = 1;
      }
    }
    
    vector<int> posT(lt);
    for_inc(i, lt) {
      if (t[i] == c) {
        posT[i] = 1;
      }
    }
    
    conv[x] = FourierTransform<int>().crossCorelation(validPos[x], posT);
  }
  
  int ret = 0;
  for_inc(i, ls) {
    int sum = 0;
    for_inc(x, 4) { sum += conv[x][i]; }
    if (sum == lt) {
      ++ret;
    }
  }
  
  cout << ret << endl;
  return 0;
}
