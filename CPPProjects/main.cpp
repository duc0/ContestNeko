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
  cout << 100 << endl;
  repeat(100) {
    int n = 200;
    cout << n << endl;
    vector<int> a(n + 1);
    for_inc_range(i, 1, n) {
      a[i] = i;
    }
    random_shuffle(a.begin() + 1, a.end());
    for_inc_range(i, 1, n) {
      cout << a[i] << " ";
    }
    cout << endl;
  }
  fclose(stdout);
}

vector<int> f;
int n;
void apply(vector<int> &a) {
  for_inc_range(i, 1, n) {
    a[i] = f[a[i]];
  }
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("biginput1.txt", "r", stdin);
#endif
  
  int nTest;
  cin >> nTest;
  while (nTest--) {
  cin >> n;
  
  f.resize(n + 1);
  for_inc_range(i, 1, n) {
    cin >> f[i];
  }
  
  vector<int> p1(n + 1), p2(n + 1);
  for_inc_range(i, 1, n) {
    p1[i] = i;
    p2[i] = i;
  }
  
  apply(p1);
  apply(p2); apply(p2);
  
  int cnt = 0;
  while (p1 != p2) {
    cnt++;
    apply(p1);
    apply(p2); apply(p2);
  }
  
  int start = 0;
  for_inc_range(i, 1, n) {
    p1[i] = i;
  }
  
  while (p1 != p2) {
    apply(p1);
    apply(p2);
    start++;
  }
  
  int period = 1;
  p2 = p1;
  apply(p2);
  while (p2 != p1) {
    apply(p2);
    period++;
  }
  
  if ((start % period) != 0) {
    start += (period - (start % period));
  } else if (start == 0) {
    start = period;
  }
  
  cout << start << endl;
  }
  return 0;
}
