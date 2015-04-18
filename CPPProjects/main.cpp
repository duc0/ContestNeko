//#define SUBMIT

#define C11

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
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11
#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>
#endif

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

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
  //testGen();
  freopen("biginput1.txt", "r", stdin);
  freopen("biginput1.out", "w", stdout);
#endif
  
  int nTest;
  cin >> nTest;
  for_inc_range(test, 1, nTest) {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    
    
    for_inc_range(i, 1, n) {
      cin >> a[i];
    }
    
    int ans1 = 0, maxDiff = 0;
    for_inc_range(i, 2, n) {
      if (a[i] < a[i - 1]) {
        ans1 += a[i - 1] - a[i];
        maxDiff = max(maxDiff, a[i - 1] - a[i]);
      }
    }
    
    int ans2 = 0;
    for_inc_range(i, 1, n - 1) {
      ans2 += min(a[i], maxDiff);
    }
    
    cout << "Case #" << test << ": " << ans1 << " " << ans2 << endl;
  }
  return 0;
}
