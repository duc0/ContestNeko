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
  
  vector<pair<int, int>> rect( n+1);
  
  set<int> allS;
  
  for_inc_range(i, 1, n) {
    int w, h;
    cin >> w >> h;
    rect[i] = make_pair(w, h);
    
    allS.insert(w);
    allS.insert(h);
  }
  
  vector<int> all(allS.begin(), allS.end());
  
  int best = INT_INF;
  
  for (auto &finalH: all) {
    bool bad = false;
    for_inc_range(i, 1, n) {
      if (min(rect[i].first, rect[i].second) > finalH) {
        bad = true;
        break;
      }
    }
    if (bad) {
      continue;
    }
    
    vector<bool> turn(n + 1);
    int have = n / 2;
    
    vector<pair<int, int>> diff;
    
    for_inc_range(i, 1, n) {
      if (rect[i].second > finalH) {
        if (have == 0) {
          bad = true;
          break;
        } else {
          have--;
          turn[i] = true;
        }
      } else if (rect[i].first <= finalH) {
        diff.push_back(make_pair(rect[i].second - rect[i].first, i));
      }
      
    }
    
    if (bad) {
      continue;
    }
    
    sort(diff.begin(), diff.end());
    
    for (auto &d: diff) {
      if (have == 0) break;
      if (d.first >= 0) break;
      turn[d.second] = true;
      have--;
    }
    
    int sumw = 0;
    for_inc_range(i, 1, n) {
      if (turn[i]) sumw += rect[i].second; else sumw += rect[i].first;
    }
    
    int ans = sumw * finalH;
    best = min(best, ans);
    
    LOG(1, "FinalH: " << finalH << " " << sumw << " " << ans);
  }
  
  cout << best << endl;
  
  return 0;
}
