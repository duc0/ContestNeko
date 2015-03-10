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
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  vector<deque<int>> pile(n);
  int total = 0;
  for_inc(i, n) {
    int s;
    cin >> s;
    total += s;
    repeat(s) {
      int x;
      cin >> x;
      pile[i].push_back(x);
    }
  }
  
  int sum1 = 0, sum2 = 0;
  bool turn1 = true;
  repeat(total) {
    if (turn1) {
      int best = 0, bestI = -1;
      for_inc(i, n) {
        if (!pile[i].empty()) {
          if (pile[i].front() > best) {
            best = pile[i].front();
            bestI = i;
          }
        }
      }
      sum1 += best;
      pile[bestI].pop_front();
    } else {
      int best = 0, bestI = -1;
      for_inc(i, n) {
        if (!pile[i].empty()) {
          if (pile[i].back() > best) {
            best = pile[i].back();
            bestI = i;
          }
        }
      }
      sum2 += best;
      pile[bestI].pop_back();
    }
    turn1 = !turn1;
  }
  
  cout << sum1 << " " << sum2 << endl;
  return 0;
}
