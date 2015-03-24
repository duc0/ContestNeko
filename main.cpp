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
#define INT_INF ((int)1E9L)
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
  
  int n, m;
  cin >> n >> m;
  
  vector<int> add(n + 1);
  
  vector<int> upper(n + 1);
  for_inc_range(i, 1, n) {
    upper[i] = INT_INF;
  }

  vector<int> qt(m + 1), ql(m + 1), qr(m + 1), qv(m + 1);
  
  for_inc_range(i, 1, m) {
    cin >> qt[i] >> ql[i] >> qr[i] >> qv[i];
  }
  for_inc_range(i, 1, m) {
    int t, l , r, v;
    t = qt[i];
    l = ql[i];
    r = qr[i];
    v = qv[i];
    if (t == 1) {
      for_inc_range(i, l, r) {
        add[i] += v;
      }
    } else {
      for_inc_range(i, l, r) {
        upper[i] = min(upper[i], v - add[i]);
      }
    }
  }
  
  vector<int> ans(n + 1);
  for_inc_range(i, 1, n) {
    ans[i] = upper[i];
  }
  vector<int> a = ans;
  
  for_inc_range(i, 1, m) {
    int t, l , r, v;
    t = qt[i];
    l = ql[i];
    r = qr[i];
    v = qv[i];
    if (t == 1) {
      for_inc_range(i, l, r) {
        a[i] += v;
      }
    } else {
      int best = a[l];
      for_inc_range(i, l, r) {
        best = max(best, a[i]);
      }
      if (best != v) {
        cout << "NO" << endl;
        return 0;
      }
    }
  }
  
  
  cout << "YES" << endl;
  for_inc_range(i, 1, n) {
    cout << ans[i] << " ";
  }
  return 0;
}
