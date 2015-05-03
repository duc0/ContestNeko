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

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, totalTime;
  vector<int> score(n + 1), timeTake(n + 1);
  
  cin >> n >> totalTime;
  
  for_inc_range(i, 1, n) {
    cin >> timeTake[i] >> score[i];
  }
  
  vector<int> sortByScore(n + 1);
  for_inc_range(i, 1, n) {
    sortByScore[i] = i;
  }
  sort(sortByScore.begin() + 1, sortByScore.end(), [&](int i, int j) {
    return score[i] > score[j];
  });
  
  for_inc_range(availTime, 1, totalTime) {
    int best = 0;
    
    // One task
    for_inc_range(i, 1, n) {
      int j = sortByScore[i];
      if (timeTake[j] <= availTime) {
        best = score[j];
        break;
      }
    }
    
    // A question and two tasks
    int cnt = 0;
    int two = 0;
    for_inc_range(i, 1, n) {
      int j = sortByScore[i];
      if (timeTake[j] <= availTime - 1) {
        cnt++;
        two += score[j];
        if (cnt == 2) {
          break;
        }
      }
    }
    
    best = max(best, two);
    
    
    
    
  }
  return 0;
}
