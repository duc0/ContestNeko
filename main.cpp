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

int b, n, d, m;

void solveSmall() {
  vector<vector<int>> p;
  repeat(n) {
    vector<int> point;
    repeat(b) {
      int x;
      cin >> x;
      point.push_back(x);
    }
    p.push_back(point);
  }
  int ret = 0;
  for_inc(i, n) {
    for_inc(j, i) {
      int dist = 0;
      for_inc(k, b) {
        dist += abs(p[i][k] - p[j][k]);
      }
      if (dist <= d) {
        ++ret;
      }
    }
  }
  cout << ret << endl;
}

void solve1() {
  vector<int> a;
  repeat(n) {
    int x;
    cin >> x;
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  int j = 0;
  int64 ret = 0;
  for_inc(i, n) {
    while (j < i && a[i] - a[j] > d) ++j;
    ret += i - j;
  }
  cout << ret << endl;
}
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> b >> n >> d >> m;
  if (n <= 2000) {
    solveSmall();
  } else {
    if (b == 1) {
      solve1();
    }
  }
  
  return 0;
}
