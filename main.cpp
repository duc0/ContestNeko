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
#define update_max(x, y) x = max(x, y)

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

#define MAXN 100100

int f[2][4][4][4][4];

#define NONE 3
int getScore(int a, int b, int c) {
  if (a == NONE && b == NONE) {
    return 1;
  }
  if (a == NONE) {
    if (b == c) {
      return 1;
    } else {
      return 2;
    }
  }
  if (a == b && a == c) {
    return 1;
  }
  if (a == b || b == c || a == c) {
    return 2;
  }
  return 3;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  
  string s;
  cin >> s;

  memset(f, 0, sizeof(f));
  
  vector<int> a(n);
  for_inc(i, n) {
    if (s[i] == 'M') {
      a[i] = 0;
    } else if (s[i] == 'F') {
      a[i] = 1;
    } else if (s[i] == 'B') {
      a[i] = 2;
    }
  }
  
  int cur = 0;
  for_inc(prev1, 4) for_inc(cur1, 4) for_inc(prev2, 4) for_inc(cur2, 4) {
    f[cur][prev1][cur1][prev2][cur2] = -INT_INF;
    f[1 - cur][prev1][cur1][prev2][cur2] = -INT_INF;
  }
  
  f[cur][NONE][NONE][NONE][NONE] = 0;
  
  for_inc(i, n) {
    LOG(1, "Position " << i <<" : " << a[i]);
    for_inc(prev1, 4) for_inc(cur1, 4) for_inc(prev2, 4) for_inc(cur2, 4) {
      int curF = f[cur][prev1][cur1][prev2][cur2];
      if (curF == -INT_INF) continue;
      LOG(1, "Score " << prev1 << " " << cur1 << " " << a[i] << " " << getScore(prev1, cur1, a[i]));
      f[1 - cur][cur1][a[i]][prev2][cur2] = max(f[1 - cur][cur1][a[i]][prev2][cur2], curF + getScore(prev1, cur1, a[i]));;
      LOG(1, "Updating " << cur1 << " "<< a[i] <<" " << prev2 << " "<< cur2 << " with " << f[1 - cur][cur1][a[i]][prev2][cur2]);
      f[1 - cur][prev1][cur1][cur2][a[i]] = max(f[1 - cur][prev1][cur1][cur2][a[i]], curF + getScore(prev2, cur2, a[i]));
      LOG(1, "Updating " << prev1 << " "<< cur1 <<" " << cur2 << " "<< a[i] << " with " << f[1 - cur][prev1][cur1][cur2][a[i]]);
      
    }
    cur = 1 - cur;
  }
  
  int best = 0;
  for_inc(prev1, 4) for_inc(cur1, 4) for_inc(prev2, 4) for_inc(cur2, 4) {
    best = max(best, f[cur][prev1][cur1][prev2][cur2]);
  }
  
  cout << best << endl;
  return 0;
}
