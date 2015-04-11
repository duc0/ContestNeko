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

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
  //freopen("output1.txt", "w", stdout);
#endif
  
  int nTest;
  cin >> nTest;
  for_inc_range(test, 1, nTest) {
    int n;
    cin >> n;
    int ans = 0;
    
    map<int, int> cnt;
    repeat(n) {
      int x;
      cin >> x;
      LOG(1, "Plate " << x);
      cnt[x]++;
    }
    
    ans = cnt.rbegin()->first;
    
    int totalMin = 0;
    while (!cnt.empty()) {
      int most = cnt.rbegin()->first;
      int mostCount = cnt.rbegin()->second;
      
      if (most == 1) {
        break;
      }
      
      totalMin += mostCount;
      int a = most/2;
      int b = (most % 2 == 1) ? (a + 1) : a;
      cnt.erase(most);
      cnt[a] += mostCount;
      cnt[b] += mostCount;
      
      ans = min(ans, totalMin + cnt.rbegin()->first);
    }
    
    cout << "Case #" << test << ": " << ans << endl;
  }
  return 0;
}
