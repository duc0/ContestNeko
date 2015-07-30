//#define SUBMIT

#define C11

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
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11
#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>
#endif

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

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

#define prev prev_
#define next next_

vector<pair<string, int>> a;

vector<int> prev, next;

int n;

int getType(int id) {
  if (id <= n) return 1;
  return 2;
}

int getLcp(string s1, string s2) {
  int i = 0, l1 = (int) s1.length(), l2 = (int) s2.length();
  while (i < l1 && i < l2 && s1[i] == s2[i]) ++i;
  return i;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n;
  
  prev.resize(2 * n + 1);
  next.resize(2 * n + 1);
  a.resize(2 * n + 1);
  for_inc_range(i, 1, n) {
    string s;
    cin >> s;
    a[i] = make_pair(s, i);
  }
  
  for_inc_range(i, n + 1, 2 * n) {
    string s;
    cin >> s;
    a[i] = make_pair(s, i);
  }
  
  sort(a.begin() + 1, a.end());
  
  prev[1] = -1;
  for_inc_range(i, 2, 2 * n) {
    prev[i] = i - 1;
  }

  for_inc_range(i, 1, 2 * n - 1) {
    next[i] = i + 1;
  }
  next[2 * n] = -1;
  
  set<pair<int, int>> best;
  for_inc_range(i, 2, 2 * n) {
    if (getType(a[i - 1].second) != getType(a[i].second)) {
      int lcp = getLcp(a[i - 1].first, a[i].first);
      best.insert(make_pair(lcp, i));
    }
  }
  
  vector<bool> used(2 * n + 1);
  vector<pair<int, int>> res;
  int ret = 0;
  while (!best.empty()) {
    pair<int, int> curBest = *best.rbegin();
    best.erase(curBest);
    int i = curBest.second;
    int prevI = prev[i];
    if (used[i] || used[prevI]) {
      continue;
    }
    used[i] = true;
    used[prevI] = true;
    ret += curBest.first;
    //LOG(1, a[prevI].first << " " << a[i].first << " " << curBest.first);
    if (getType(a[prevI].second) == 1) {
      res.push_back(make_pair(a[prevI].second, a[i].second));
    } else {
      res.push_back(make_pair(a[i].second, a[prevI].second));
    }
    int theNext = next[i];
    int thePrev = prev[prevI];
    if (theNext != -1) {
      prev[theNext] = thePrev;
    }
    if (thePrev != -1) {
      next[thePrev] = theNext;
    }
    if (theNext != -1 && thePrev != -1 && getType(a[thePrev].second) != getType(a[theNext].second)) {
      int lcp = getLcp(a[thePrev].first, a[theNext].first);
      best.insert(make_pair(lcp, theNext));
    }
  }
  
  cout << ret << endl;
  for (auto &p: res) {
    cout << p.first << " " << p.second - n << endl;
  }
  
  return 0;
}
