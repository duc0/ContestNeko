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

int n;
string s;

bool good(int i) {
  if (i < 0 || i >= n) return false;
  if (s[i] != '*') return false;
  return true;
}
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  cin >> n;
  cin >> s;
  for_inc(start, n) {
    for_inc(len, n) {
      if (len == 0) continue;
      
      bool bad = false;
      for_inc(k, 5) {
        if (!good(start + k * len)) {
          bad = true;
          break;
        }
      }
      if (!bad) {
        cout << "yes" << endl;
        return 0;
      }
    }
  }
  cout << "no" << endl;
  return 0;
}
