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
  
  int n, k;
  cin >> n >> k;
  vector<int> a( n + 1);
  set<int> s;
  for_inc_range(i, 1, n) {
    cin >> a[i];
    s.insert(a[i]);
  }
  
  int q;
  cin >> q;
  repeat(q) {
    int x;
    cin >> x;
    
    int best = k + 1;
    for_inc_range(i, 1, n) {
      bool found = false;
      for_inc_range(need, 0, k) {
        for_inc_range(t, 0, need) {
          int64 total = a[i] * t;
          int remain = need - t;
          if (remain == 0) {
            if (total == x) {
              found = true;
              break;
            }
          } else
          if ((x - total) % remain == 0) {
            int64 denom = (x - total) / remain;
            if (s.count((int)denom)) {
              found = true;
              break;
            }
          }
        }
        if (found) {
          best = min(best, need);
          break;
        }
      }
    }
    if (best == k + 1) {
      best = -1;
    }
    cout << best << endl;
  }
  
  
  return 0;
}
