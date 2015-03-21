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
  freopen("input2.txt", "r", stdin);
#endif
  
  vector<pair<pair<int, int>, int>> rect;
  
  int n;
  
  int sumw = 0;
  cin >> n;
  for_inc(i, n) {
    int ww, hh;
    cin >> ww >> hh;
    rect.push_back(make_pair(make_pair(hh, ww), i));
    sumw += ww;
  }
  sort(rect.begin(), rect.end());
  int maxH = rect[n - 1].first.first;
  int maxH2 = rect[n - 2].first.first;
  
  vector<int> ans(n);
  for_inc(i, n) {
    int ww = sumw - rect[i].first.second;
    int hh = maxH;
    if (i == n - 1) {
      hh = maxH2;
    }
    ans[rect[i].second] = ww * hh;
  }
  
  for_inc(i, n) {
    cout << ans[i] << " ";
  }
  
  
  return 0;
}
