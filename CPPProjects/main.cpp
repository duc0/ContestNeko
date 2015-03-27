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
  freopen("input5.txt", "r", stdin);
#endif
  
  vector<pair<int, int>> p;
  
  int a, b;
  cin >> a >> b;
  
  string s;
  cin >> s;
  
  int64 x = 0, y = 0;
  for (char c: s) {
    p.push_back(make_pair(x, y));
    switch (c) {
      case 'U': y++; break;
      case 'D': y--; break;
      case 'L': x--; break;
      case 'R': x++; break;
    }
  }
  
  for (auto u : p) {
    int64 dx = a - u.first;
    int64 dy = b - u.second;
    if (dx == 0 && dy == 0) {
      cout << "Yes" << endl;
      exit(0);
    }
    if (x != 0 && dx % x == 0) {
      int64 d = dx / x;
      if (d >= 0 && d * y == dy) {
        cout << "Yes" << endl;
        exit(0);
      }
    }
    if (y != 0 && dy % y == 0) {
      int64 d = dy / y;
      if (d >= 0 && d * x == dx) {
        cout << "Yes" << endl;
        exit(0);
      }
    }
  }
  
  cout << "No";
  
  return 0;
}
