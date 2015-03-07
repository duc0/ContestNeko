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

int rnd(double x) {
  return (int)(x+0.5);
}

bool isSquare(int n) {
  int p=rnd(sqrt(n));
  return p*p==n;
}


int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int a, b;
  cin >> a >> b;
  for_inc_range(x1, 1, a - 1) {
    int sqy1 = a * a - x1 * x1;
    if (!isSquare(sqy1)) continue;
    int y1 = (int)(sqrt(sqy1));
    for_inc_range(x2, 1, b - 1) {
      int sqy2 = b * b - x2 * x2;
      if (!isSquare(sqy2)) continue;
      int y2 = (int)(sqrt(sqy2));
      
      for_inc(sx1, 2) {
        int ax1 = x1 * (2 * sx1 - 1);
        for_inc(sy1, 2) {
          int ay1 = y1 * (2 * sy1 - 1);
          for_inc(sx2, 2) {
            int ax2 = x2 * (2 * sx2 - 1);
            for_inc(sy2, 2) {
              int ay2 = y2 * (2 * sy2 - 1);
              if ((ax1 * ax2 + ay1 * ay2 == 0) && (ax1 != ax2) && (ay1 != ay2)) {
                cout << "YES" << endl;
                cout << "0 0" << endl;
                cout << ax1 << " " << ay1 << endl;
                cout << ax2 << " " << ay2 << endl;
                return 0;
              }
              
            }
          }
        }
      }
    }
  }
  
  cout << "NO" << endl;
  return 0;
}
