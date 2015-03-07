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

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input5.txt", "r", stdin);
#endif
  
  int numMeal;
  cin >> numMeal;
  vector<int> price(numMeal + 1);
  for_inc_range(i, 1, numMeal) {
    cin >> price[i];
  }
  
  int menuPrice;
  cin >> menuPrice;
  vector<int> menu(5);
  for_inc_range(i, 1, 4) {
    cin >> menu[i];
  }
  
  int traySize;
  cin >> traySize;
  vector<int> tray(numMeal + 1);
  
  int curPrice = 0;
  
  for_inc_range(i, 1, traySize) {
    int x;
    cin >> x;
    tray[x]++;
    curPrice += price[x];
  }
  
  int best = curPrice;
  
  int numMenu = 1;
  while (1) {
    bool found = false;
    for_inc_range(i, 1, 4) {
      if (tray[menu[i]] > 0) {
        found = true;
        tray[menu[i]]--;
        curPrice -= price[menu[i]];
      }
    }
    if (!found) break;
    curPrice += menuPrice;
    best = min(best, curPrice);
    numMenu++;
  }
  
  cout << best << endl;
  return 0;
}
