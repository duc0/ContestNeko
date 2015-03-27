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
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cfloat>
#include <random>

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

#define MAXN 5010

bool e[MAXN][MAXN];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int m, n;
  cin >> n >> m;
  
  int64 maxEdge = (int64) n * (n - 1) / 2;
  
  if (m + m > maxEdge) {
    cout << -1 << endl;
    return 0;
  }
  
  if (n <= 5000) {
    fill0(e);
    repeat(m) {
      int u, v;
      cin >> u >> v;
      e[u][v] = e[v][u] = true;
    }
    
    int cnt = 0;
    for_inc_range(u, 1, n) {
      for_inc_range(v, u + 1, n) {
        if (!e[u][v]) {
          cout << u << " " << v << endl;
          cnt++;
          if (cnt == m) {
            return 0;
          }
        }
      }
    }
  } else {
    unordered_set<int64> exist;
    
    repeat(m) {
      int u, v;
      cin >> u >> v;
      if (u > v) {
        swap(u, v);
      }
      int64 code = (int64) u * n + v;
      exist.insert(code);
    }
    
    repeat(m) {
      while (1) {
        int u = rand() % n +1 , v = rand()% n + 1;
        if (u == v) continue;
        if (u > v) swap(u, v);
        int64 code = (int64) u * n + v;
        if (exist.count(code)) continue;
        exist.insert(code);
        cout << u << " " << v << endl;
        break;
      }
    }
  }
  
  
  
  return 0;
}
