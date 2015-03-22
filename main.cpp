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
  freopen("input3.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  
  vector<string> first(n + 1), last(n + 1);
  for_inc_range(i, 1, n) {
    cin >> first[i] >> last[i];
  }
  vector<int> p( n + 1);
  
  string cur;
  for_inc_range(i, 1, n) {
    cin >> p[i];
    if (i > 1 && first[p[i]] < cur && last[p[i]] < cur) {
      cout << "NO";
      exit(0);
    }
    if (min(first[p[i]], last[p[i]]) >= cur) {
      cur = min(first[p[i]], last[p[i]]);
    } else {
      cur = max(first[p[i]], last[p[i]]);
    }
    LOG(1, cur);
  }
  cout << "YES";
  return 0;
}
