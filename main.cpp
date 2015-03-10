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
  freopen("input3.txt", "r", stdin);
#endif
  
  int n, k;
  cin >> n >> k;
  int maxV = 0, minV = INT_INF;
  vector<int> a(n + 1);
  for_inc_range(i, 1, n) {
    cin >> a[i];
    maxV = max(maxV, a[i]);
    minV = min(minV, a[i]);
  }
  
  int maxDiff = maxV - minV;
  vector<vector<pair<int, int>>> pairDiff(maxDiff + 1);
  vector<bool> cannotDelete(maxDiff + 1);
  fill(cannotDelete.begin(), cannotDelete.end(), false);
  
  for_inc_range(i, 1, n) {
    for_inc_range(j, 1, i - 1) {
      int x = abs(a[i] - a[j]);
      if (pairDiff[x].size() == k) {
        cannotDelete[x] = true;
      } else {
        pairDiff[x].push_back(make_pair(a[i], a[j]));
      }
    }
  }
  
  for (int m = 1; ;++m) {
    bool ok = true;
    map<int, set<int>> group;
    for (int x = 0; x <= maxDiff; x += m) {
      if (cannotDelete[x]) {
        ok = false;
        break;
      }
      
      for (auto &p : pairDiff[x]) {
        int r = p.first % m;
        assert(r == (p.second % m));
        group[r].insert(p.first);
        group[r].insert(p.second);
      }
      
      if (group.size() > k) {
        ok = false;
        break;
      }
      
      int totalDelete = 0;
      for (auto &g: group) {
        totalDelete += g.second.size();
      }
      totalDelete -= group.size();
      if (totalDelete > k) {
        ok = false;
        break;
      }
    }
    if (!ok) continue;
    cout << m;
    return 0;
  }
  
  return 0;
}
