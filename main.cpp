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
  freopen("input2.txt", "r", stdin);
#endif
  string s;
  int n;
  cin >> n;
  cin >> s;
  vector<vector<int64>>f(n + 1, vector<int64>(n + 1));
  vector<int64> pow(n + 1);
  pow[0] = 1;
  for_inc_range(i, 1, n) {
    pow[i] = pow[i - 1] * 10;
  }
  
  for_inc_range(i, 0, n) {
    for_inc_range(j, 0, n) {
      int pos = i + j;
      
      if (pos == 0) {
        f[i][j] = 0;
      } else {
        
        int x = s[pos - 1] - '0';
        
        f[i][j] = 0;
        if (i > 0) {
          f[i][j] = f[i - 1][j] + pow[n - i] * x;
        }
        if (j > 0) {
          f[i][j] = max(f[i][j], f[i][j - 1] + pow[n - j] * x);
        }
      }
    }
  }
  LOG(1, f[n][n]);

  int curI = n;
  int curJ = n;
  string ans = s;
  while (curI > 0 || curJ > 0) {
    int pos = curI + curJ;

    int x = s[pos - 1] - '0';
    
    if (curI > 0 && (f[curI][curJ] == (f[curI - 1][curJ] + pow[n - curI] * x))) {
      ans[pos - 1] = 'M';
      curI--;
    } else if (curJ > 0 && (f[curI][curJ] == (f[curI][curJ - 1] + pow[n - curJ] * x))) {
      ans[pos - 1] = 'H';
      curJ--;
    }
  }
  
  cout << ans << endl;
  return 0;
}
