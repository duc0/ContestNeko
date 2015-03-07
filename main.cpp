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

double binarySearchMaxReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
  double l = minRange, r = maxRange, m, ret = maxRange + 1;
  while (r - l > epsilon) {
    m = l + (r - l) / 2;
    if (predicate(m)) {
      ret = m;
      l = m;
    } else {
      r = m;
    }
  }
  return ret;
}

int n, k;
vector<int> a;

bool hasAtLeast(double average) {
  double sum = 0;
  for_inc_range(i, 1, k - 1) {
    sum += a[i] - average;
  }
  
  double bestNow = -1e18, best = -1e18;
  for_inc_range(i, k, n) {
    sum += a[i] - average;
    
    bestNow = max(sum, bestNow + a[i] - average);
    best = max(best, bestNow);
    
    sum -= a[i - k + 1] - average;
  }
  
  return best >= 0;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input4.txt", "r", stdin);
#endif
  
  cin >> n >> k;
  a.resize(n + 1);
  
  double sum = 0;
  for_inc_range(i, 1, n) {
    cin >> a[i];
    sum = max(sum, (double)a[i]);
  }
  
  
  double ret = binarySearchMaxReal(0, sum, 1e-4, [](double average) {return hasAtLeast(average);});
  
  printf("%.6lf", ret);
  
  return 0;
}
