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
#include <bitset>

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

int64 c, hr, hb, wr, wb;

int64 score(int64 x) {
  int64 remain = c - wr * x;
  int64 nb = remain / wb;
  return x * hr + nb * hb;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> c >> hr >> hb >> wr >> wb;
  
  int64 maxr = c / wr;
  
  int64 l = 0, r = maxr, ans = max(score(l), score(r));
  while (r >= l) {
    int64 m1 = (2 * l + r) / 3;
    int64 m2 = (l + 2 * r) / 3;
    int64 s1 = score(m1);
    int64 s2 = score(m2);
    if (s1 < s2) {
      l = m1 + 1;
    } else if (s1 > s2) {
      r = m2 - 1;
    } else {
      ans = s1;
      r = m2 -1;
    }
  }
  
  cout << ans << endl;
  
  return 0;
}
