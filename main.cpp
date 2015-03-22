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

// Greedy
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n, m, t;
  scanf("%d%d%d", &n, &m, &t);
  
  vector<int> color( n  + 1);
  
  vector<int> a(n + 1);
  
  int nColor = 0;
  
  int curL = 1;
  
  bool good = false;
  map<int, int> dColor;
  
  for_inc_range(i, 1, n) {
    int hour, min, sec;
    scanf("%d:%d:%d", &hour, &min, &sec);
    
    //LOG(1, hour << " " << min << " " << sec);
    
    a[i] = hour * 3600 + min * 60 + sec;

    LOG(1, "Time: " << a[i]);
    
    while (curL < i && a[curL] + t <= a[i]) {
      dColor[color[curL]]--;
      if (dColor[color[curL]] == 0) {
        dColor.erase(color[curL]);
      }
      ++curL;
    }
    
    if (dColor.size() >= m) {
      color[i] = color[i - 1];
      dColor[color[i]]++;
      good = true;
    } else {
      if (i - curL + 1 == m) {
        good = true;
      }
      nColor++;
      color[i] = nColor;
      dColor[color[i]]++;
    }
  }
  
  
  if (good) {
    cout << nColor << endl;
    for_inc_range(i, 1, n) {
      cout << color[i] << endl;
    }
  } else {
    cout << "No solution" << endl;
  }
  return 0;
}
