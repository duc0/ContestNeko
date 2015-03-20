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

#define MAXN 200200
char validC[] = {'A', 'C', 'G', 'T'};

bitset<MAXN> validPos[4], result;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int ls, lt, k;
  cin >> ls >> lt >> k;
  
  string s, t;
  cin >> s >> t;
  
  
  vector<int> prev(ls), next(ls);
  
  for_inc(x, 4) {
    char c = validC[x];
    
    for_inc(i, ls) {
      prev[i] = -1;
      if (i > 0) {
        prev[i] = prev[i - 1];
      }
      if (s[i] == c) {
        prev[i] = i;
      }
    }
    
    for_dec(i, ls) {
      next[i] = ls;
      if (i + 1 < ls) {
        next[i] = next[i + 1];
      }
      if (s[i] == c) {
        next[i] = i;
      }
    }
    
    for_inc(i, ls) {
      if ((prev[i] != -1 && prev[i] >= i - k) || (next[i] != ls && next[i] <= i + k)) {
        validPos[x].set(i);
      }
    }
  }
  
  for_inc(i, ls) {
    result.set(i);
  }
  
  for_inc(i, lt) {
    for_inc(x, 4) {
      char c = validC[x];
      if (t[i] != c) continue;
      
      result &= validPos[x] >> i;
    }
  }
  
  int ret = 0;
  for_inc(i, ls) {
    if (result.test(i)) {
      ++ret;
    }
  }
  
  cout << ret << endl;
  return 0;
}
