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
#define INT64_INF ((int64)10000000000000000LL)
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
    int nBarber, place;
    cin >> nBarber >> place;
    vector<int> duration(nBarber + 1);
    for_inc_range(i, 1, nBarber) {
      cin >> duration[i];
    }
    
    
    int64 l = 0, r = INT64_INF, mid, minTime = -1;
    while (l <= r) {
      mid = (l + r) / 2;
     
      int64 cap = 0;
      for_inc_range(i, 1, nBarber) {
        cap += mid / duration[i] + 1;
      }
      if (cap >= place) {
        minTime = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    
    cout << "Case #" << test << ": ";
    int total = 0;
    for_inc_range(i, 1, nBarber) {
      total += minTime / duration[i];
      if (minTime % duration[i] != 0) {
        total++;
      }
    }
    for_inc_range(i, 1, nBarber) {
      if (minTime % duration[i] == 0) {
        total++;
        if (total == place) {
          cout << i << endl;
          break;
        }
      }
    }
    
  }
  return 0;
}
