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

#define MAX 20

bool notSame(int x1, int y1, int x2, int y2) {
  return x1 != x2 || y1 != y2;
}
int firstWin[2][MAX + 1][MAX + 1][MAX + 1][MAX + 1];
int solve(int playFirst, int x1, int y1, int x2, int y2) {
  assert(notSame(x1, y1, 0, 0) || notSame(x2, y2, 0, 0));
  
  if (firstWin[playFirst][x1][y1][x2][y2] != -1) {
    return firstWin[playFirst][x1][y1][x2][y2];
  }
  
  if (playFirst == 0) {
    if (x1 == 0 && y1 == 0) {
      return firstWin[playFirst][x1][y1][x2][y2] = 1;
    } else if (x2 == 0 && y2 == 0) {
      return firstWin[playFirst][x1][y1][x2][y2] = 0;
    }
    if (x1 - 1 >= 0 && notSame(x1 - 1, y1, x2, y2)) {
      if (solve(1 - playFirst, x1 - 1, y1, x2, y2)) {
        return firstWin[playFirst][x1][y1][x2][y2] = 1;
      }
    }
    if (y1 - 1 >= 0 && notSame(x1, y1 - 1, x2 , y2)) {
      if (solve(1 - playFirst, x1, y1 - 1, x2, y2)) {
        return firstWin[playFirst][x1][y1][x2][y2] = 1;
      }
    }
    return firstWin[playFirst][x1][y1][x2][y2] = 0;
  } else {
    if (x1 == 0 && y1 == 0) {
      return firstWin[playFirst][x1][y1][x2][y2] = 1;
    } else if (x2 == 0 && y2 == 0) {
      return firstWin[playFirst][x1][y1][x2][y2] = 0;
    }
    if (x2 - 1 >= 0 && notSame(x1, y1, x2 - 1, y2)) {
      if (!solve(1 - playFirst, x1, y1, x2 - 1, y2)) {
        return firstWin[playFirst][x1][y1][x2 - 1][y2] = 0;
      }
    }
    if (y2 - 1 >= 0 && notSame(x1, y1, x2, y2 - 1)) {
      if (!solve(1 - playFirst, x1, y1, x2, y2 - 1)) {
        return firstWin[playFirst][x1][y1][x2][y2 - 1] = 0;
      }
    }
    if (x2 - 1 >= 0 && y2 - 1 >= 0 && notSame(x1, y1, x2 - 1, y2 - 1)) {
      if (!solve(1 - playFirst, x1, y1, x2 - 1, y2 - 1)) {
        return firstWin[playFirst][x1][y1][x2 - 1][y2 - 1] = 0;
      }
    }
    return firstWin[playFirst][x1][y1][x2][y2] = 1;
  }
}

void solve() {
  memset(firstWin, -1, sizeof(firstWin));
  for_inc_range(x1, 0, MAX) for_inc_range(y1, 0, MAX) for_inc_range(x2, 0, MAX) for_inc_range(y2, 0, MAX) {
    if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) continue;
    if (!notSame(x1, y1, x2, y2)) continue;
    bool firstWin = false;
    if (x1 <= x2 && y1 <= y2) {
      firstWin = true;
    } else if (x1 + y1 <= max(x2, y2)) {
      firstWin = true;
    }
    if (solve(0, x1, y1, x2, y2)) {
//      cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
      assert(firstWin);
    } else {
      assert(!firstWin);
//      assert(x1 >= x2 || x2 >= y2);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  //solve();
  
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  bool firstWin = false;
  if (x1 <= x2 && y1 <= y2) {
    firstWin = true;
  } else if (x1 + y1 <= max(x2, y2)) {
    firstWin = true;
  }
  if (firstWin) {
    cout << "Polycarp";
  } else {
    cout << "Vasiliy";
  }

  
  return 0;
}
