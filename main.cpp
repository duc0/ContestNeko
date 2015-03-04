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
  
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  
  if (x1 == x2) {
    int s = y2 - y1;
    cout << x1 + s << " " << y1 << " " << x1 + s << " " << y2 << endl;
  } else if (y1 == y2) {
    int s = x2 - x1;
    cout << x1 << " " << y1 + s << " " << x2 << " " << y1 + s << endl;
  } else {
    if (abs(x2 - x1) != abs(y2 - y1)) {
      cout << -1;
    } else {
      cout << x1 << " " << y2 << " " << x2 << " " << y1 << endl;
    }
  }
  return 0;
}
