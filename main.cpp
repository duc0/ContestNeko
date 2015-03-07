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

int64 choose2(int64 k) {
  return k * (k - 1) / 2;
}

int64 choose3(int64 k) {
  return k * (k - 1) * (k - 2) / 6;
}


int64 solve1(int k) {
  if (k < 2) {
    return 0;
  }
  int64 nNode = 20;
  
  int64 ret2 = choose2(k) * 2;
  
  int64 ret3 = 0;
  if (k >= 3) {
    ret3 = choose3(k) * (3LL * (1LL << (nNode - 1)) - 3 * 2);
  }
  
  return ret2 + ret3;
}

int64 solve2(int k) {
  if (k < 3) {
    return 0;
  }
  return choose3(k) * 3 * (1 << 5);
}

int64 solve3(int k) {
  if (k < 2) {
    return 0;
  }
  
  int64 ret2 = choose2(k) * 2;
  
  int64 ret3 = 0;
  if (k >= 3) {
    ret3 = choose3(k) * (3 * (1 << 3) - 3 * 2);
  }
  
  return ret2 + ret3;
}

int64 solve4(int k) {
  if (k < 2) {
    return 0;
  }
  int64 ret2 = choose2(k) * 2;
  int64 ret3 = 0;
  if (k >= 3) {
    ret3 = choose3(k) * (3 * (1 << 13) - 3 * 2);
  }
  return ret2 + ret3;
}

int64 solve5(int k) {
  if (k < 3) {
    return 0;
  }
  return choose3(k) * 3 * 2 * 2;
}

int64 solve6(int k) {
  if (k < 3) {
    return 0;
  }
  return choose3(k) * 6;
}

int64 solve7(int k) {
  if (k < 3) {
    return 0;
  }
  return choose3(k) * 3 * (1 << 5);
}

int64 solve8(int k) {
  if (k < 2) {
    return 2;
  }
  int64 ret2 = choose2(k) * 2;
  int64 ret3 = 0;
  if (k >= 3) {
    int nNode = 30;
    int64 r = 0;
    for_inc_range(i, 2, nNode) {
      if (i % 2 == 0) {
        r = r * 2 + 1;
      } else {
        r = r * 2 - 1;
      }
    }
    r = r * 2;
    ret3 = choose3(k) * (3 * r  -  3 * 2);
  }
  return ret2 + ret3;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  int n, k;
  cin >> n >> k;
  
  int64 ret = 0;
  switch (n) {
    case 1:
      ret = solve1(k);
      break;
    case 2:
      ret = solve2(k);
      break;
    case 3:
      ret = solve3(k);
      break;
    case 4:
      ret = solve4(k);
      break;
    case 5:
      ret = solve5(k);
      break;
    case 6:
      ret = solve6(k);
      break;
    case 7:
      ret = solve7(k);
      break;
    case 8:
      ret = solve8(k);
      break;
  }
  
  cout << ret << endl;
  return 0;
}
