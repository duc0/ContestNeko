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
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n;
int solve(const vector<int> &a, const vector<int> &b, const vector<int> &c) {
  vector<int> f[4];
  for_inc_range(k, 1, 3) {
    f[k].resize(n + 1);
  }
  
  f[1][0] = 0;
  for_inc_range(i, 1, n) {
    f[1][i] = a[i] + f[1][i - 1];
  }
  
  for_inc_range(i, 2, n) {
    f[2][i] = b[i] + f[1][i - 1];
    if (i > 2) {
      f[2][i] = min(f[2][i], b[i] + f[2][i - 1]);
    }
  }
  
  for_inc_range(i, 3, n) {
    f[3][i] = c[i] + f[2][i - 1];
    if (i > 3) {
      f[3][i] = min(f[3][i], c[i] + f[3][i - 1]);
    }
  }
  
  return f[3][n];
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input4.txt", "r", stdin);
#endif
  
  cin >> n;
  vector<int> a( n + 1), b( n + 1), c( n + 1);
  for_inc_range(i, 1, n) cin >> a[i];
  for_inc_range(i, 1, n) cin >> b[i];
  for_inc_range(i, 1, n) cin >> c[i];
  
  int ret = INT_INF;
  ret = min(ret, solve(a, b, c));
  ret = min(ret, solve(a, c, b));
  ret = min(ret, solve(b, a, c));
  ret = min(ret, solve(b, c, a));
  ret = min(ret, solve(c, a, b));
  ret = min(ret, solve(c, b, a));
  
  cout << ret << endl;
  
  return 0;
}
