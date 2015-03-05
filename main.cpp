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

int n;
vector<pair<int, int>> a;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  cin >> n;
  int maxH = 0;
  repeat(n) {
    int h, k;
    cin >> h >> k;
    a.push_back(make_pair(h, k));
    maxH = max(maxH, h);
  }
  
  sort(a.begin(), a.end());
  
  int curH = 0;
  vector<int> s(maxH);
  for (auto &p: a) {
    int h = p.first, k = p.second;
    if (h > curH) {
      curH = h;
    }
    int need = k;
    int i = curH - 1;
    while (need > 0) {
      int skip = 0;
      while (i > 0 && s[i - 1] == s[i]) {
        --i;
        ++skip;
      }
      int j = i + min(need - 1, skip);
      for_dec_range(k, j, i) {
        --need;
        ++s[k];
      }
      --i;
    }
  }
  
  int64 ret = 0;
  for (auto &x: s) {
    ret += (int64) x * (x - 1) / 2;
  }
  
  cout << ret << endl;
  return 0;
}
