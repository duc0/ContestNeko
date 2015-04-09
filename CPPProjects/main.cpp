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

int intersect_cnt(const set<int> &a, const set<int> &b) {
  int cnt = 0;
  for (int s: b) {
    if (a.count(s)) ++cnt;
  }
  return cnt;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int nFile;
  cin >> nFile;
  
  vector<set<int>> file(nFile);
  
  for_inc(i, nFile) {
    int c;
    cin >> c;
    repeat(c) {
      int x;
      cin >> x;
      file[i].insert(x);
    }
  }
  
  int nQuery;
  cin >> nQuery;
  repeat(nQuery) {
    int qType;
    cin >> qType;
    int c;
    cin >> c;
    set<int> a;
    repeat(c) {
      int x;
      cin >> x;
      a.insert(x);
    }

    int ans = 0;
    if (qType == 1) {
      for_inc(i, nFile) {
        if (intersect_cnt(file[i], a) == a.size()) {
          ans++;
        }
      }
    } else if (qType == 2) {
      for_inc(i, nFile) {
        if (intersect_cnt(file[i], a) > 0) {
          ans++;
        }
      }
    } else if (qType == 3) {
      for_inc(i, nFile) {
        int sz = intersect_cnt(file[i], a);
        if (sz > 0 && sz < a.size()) {
          ans++;
        }
      }
    }
    
    cout << ans << endl;
  }
  return 0;
}
