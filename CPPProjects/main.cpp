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
int MOD;
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAX 550

int f[MAX][MAX];
int bugPerLine[MAX];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int nProg, nLine, maxBug;
  cin >> nProg >> nLine >> maxBug >> MOD;
  
  if (MOD == 1) {
    cout << 0 << endl;
    return 0;
  }
  
  for_inc_range(i, 1, nProg) {
    cin >> bugPerLine[i];
  }
  
  int cur = 0, next = 1;
  memset(f, 0, sizeof(f));
  
  for_inc_range(bug, 0, maxBug) {
    f[0][bug] = 1 % MOD;
  }
  
  for_inc_range(idx, 1, nProg) {
    
    for_inc_range(line, 1, nLine) {
      for_inc_range(bug, bugPerLine[idx], maxBug) {
        f[line][bug] = (f[line][bug] + f[line - 1][bug - bugPerLine[idx]]) % MOD;
        //LOG(1, line << " " << bug << " " << f[line][bug]);
      }
    }
    
    cur = 1 - cur;
    next = 1 - next;
  }
  
  cout << f[nLine][maxBug] << endl;
  return 0;
}
