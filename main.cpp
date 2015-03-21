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
  freopen("input1.txt", "r", stdin);
#endif
  
  string s1, s2;
  cin >> s1;
  cin >> s2;
  
  int i1 = 0, i2 = 0;
  int l1 = (int) s1.size();
  int l2 = (int) s2.size();
  while (i1 < l1) {
    while (i2 < l2 && s2[i2] != s1[i1]) ++i2;
    if (i2 >= l2) {
      cout << 0 << endl;
      exit(0);
    }
    i1++;
    i2++;
  }
  
  int minL = i2 - 1;
  
  i1 = l1 - 1;
  i2 = l2 - 1;
  while (i1 >= 0) {
    while (i2 >= 0 && s2[i2] != s1[i1]) --i2;
    if (i2 < 0) {
      cout << 0 << endl;
      exit(0);
    }
    i1--;
    i2--;
  }
  
  int minR = i2 + 1;
  if (minL > minR) {
    cout << 0 << endl;
    exit(0);
  }
  
  LOG(1, minL);
  LOG(1, minR);
  cout << minR - minL;
  return 0;
}
