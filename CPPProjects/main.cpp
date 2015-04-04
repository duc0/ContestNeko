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

int n, q;
vector<int> a;

int getA(int i) {
  if (i > n) return a[i - n];
  return a[i];
}

int solve(int64 cap) {
  
  vector<int> maxR(n + 1);
  
  int64 sum = 0;
  int j = 0;
  while (j + 1 <= n && sum + a[j + 1] <= cap) {
    sum += a[j + 1];
    ++j;
  }
  maxR[1] = j;
  
  for_inc_range(i, 2, n) {
    sum -= a[i - 1];
    
    while (j + 1 < i + n - 1 && sum + getA(j + 1) <= cap) {
      sum += getA(j + 1);
      j++;
    }
    
    maxR[i] = j;
  }
  
  int minGroup = maxR[1], group = 1;
  for_inc_range(i, 1, n) {
    if (maxR[i] - i + 1 < minGroup) {
      minGroup = maxR[i] - i + 1;
      group = i;
    }
  }
  
  int ans = n;
  for_inc_range(s, group, maxR[group] + 1) {
    int start = s;
    if (start > n) start -= n;
    
    int cand = 0;
    int u = start;
    
    int total = 0;
    while (true) {
      cand++;
      total += (maxR[u] - u + 1);
      if (total >= n) {
        break;
      }
      u = maxR[u] + 1;
      if (u > n) {
        u -= n;
      }
    }
    ans = min(ans, cand);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n >> q;
  
  a.resize(n  + 1);
  for_inc_range(i, 1, n) cin >> a[i];
  
  repeat(q) {
    int64 cap;
    cin >> cap;
    cout << solve(cap) << endl;
  }
  
  
  return 0;
}
