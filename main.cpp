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
  int nTest = 100;
  cout << nTest << endl;
  repeat(nTest) {
    int n = 100, k = 105;
    cout << n << " " << k << endl;
    repeat(n) {
      cout << rand() % 200 + 1 << " ";
    }
    cout << endl;
  }
  fclose(stdout);
}

int64 solve(const vector<int> &a, int k) {
  int n = (int) a.size();
  int lastP = -1;
  int64 ret = 0;
  for_inc(i, n) {
    if (a[i] > k) {
      lastP = i;
    }
    if (lastP != - 1) {
      ret += lastP + 1;
    }
  }
  return ret;
}

int64 solveSlow(const vector<int> &a, int k) {
  int n = (int) a.size();

  int64 ret = 0;
  for_inc(i, n) {
    int best = 0;
    for_inc_range(j, i, n - 1) {
      best = max(best, a[j]);
      if (best > k) {
        ret++;
      }
    }
  }
  
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("biginput1.txt", "r", stdin);
#endif
  int nTest;
  cin >> nTest;
  repeat(nTest) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for_inc(i, n) {
      cin >> a[i];
    }
    cout << solve(a, k) << endl;
    assert(solveSlow(a, k) == solve(a, k));
  }
  return 0;
}
