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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n, h, loseHeight;
  
  cin >> n >> h >> loseHeight;
  
  vector<vector<int>> nPeople(n + 1);
  for_inc_range(i, 1, n) {
    nPeople[i].resize(h + 1);
  }
  
  for_inc_range(i, 1, n) {
    int u;
    cin >> u;
    repeat(u) {
      int f;
      cin >> f;
      nPeople[i][f]++;
    }
  }
  
  vector<vector<int>> f;
  f.resize(h + 1);
  for_inc_range(i, 1, h) {
    f[i].resize(n + 1);
  }
  
  vector<int> g(h + 1);
  
  for_inc_range(curH, 1, h) {
    g[curH] = 0;
    for_inc_range(i, 1, n) {
      int p = nPeople[i][curH];
      if (curH == 1) {
        f[curH][i] = p;
      } else {
        f[curH][i] = p + f[curH - 1][i];
        if (curH > loseHeight) {
          f[curH][i] = max(f[curH][i], p + g[curH - loseHeight]);
        }
      }
      g[curH] = max(g[curH], f[curH][i]);
    }
  }

  cout << g[h] << endl;
  return 0;
}
