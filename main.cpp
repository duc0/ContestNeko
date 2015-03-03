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
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  map<int, int> c;
  repeat(n) {
    int x;
    cin >> x;
    c[x]++;
  }
  vector<pair<int, int>> a;
  for (auto &p: c) {
    a.push_back(p);
  }
  
  n = (int)a.size();
  vector<int64> f(n);
  for_inc(i, n) {
    int64 p = (int64)a[i].first * a[i].second;
    if (i == 0) {
      f[i] = p;
    } else {
      if (a[i - 1].first + 1 < a[i].first) {
        f[i] = p + f[i - 1];
      } else {
        f[i] = max(f[i - 1], p + ((i >= 2) ? f[ i - 2] : 0));
      }
    }
  }
  cout << f[n - 1];
  return 0;
}
