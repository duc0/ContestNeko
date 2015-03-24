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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n, target;
  cin >> n >> target;

  string s;
  cin >> s;
  vector<int> a(n + 1);
  for_inc_range(i, 1, n) {
    a[i] = s[i - 1] - 'a';
  }
  
  vector<vector<int>> f(n + 2, vector<int>(target + 1));
  vector<vector<int>> g(n + 2, vector<int>(target + 1));
  
  f[n + 1][0] = 1;
  g[n + 1][0] = 0;
  
  for_dec_range(i, n, 1) {
    for_inc_range(k, 0, target) {
      int ret = 0;
      if (k == 0) {
        // Everything is equal.
        ret = 1;
      }
      int maxJ = i - 1;
      for_inc_range(j, i, n) {
        // b[x] = a[x] for i <= x < j
        // and b[j] > a[j]
        int contribute = (n - j + 1) * (j - i + 1); // Quadratic function...
        if (k - contribute < 0) break;
  
        ret = MODP(ret + (int64)(25 - a[j]) * f[j + 1][k - contribute]);
        maxJ = j;
      }
      
      if (maxJ < n) {
        for_dec_range(j, n, i) {
          int contribute = (n - j + 1) * (j - i + 1);
          if (k - contribute < 0) break;
          
          ret = MODP(ret + (int64)(25 - a[j]) * f[j + 1][k - contribute]);
        }
      }
      
      g[i][k] = MODP((int64)a[i] * f[i + 1][k] + g[i + 1][k]);
      ret = MODP(ret + g[i][k]);
      
      f[i][k] = ret;
    }
  }
  
  cout << f[1][target] << endl;
  return 0;
}
