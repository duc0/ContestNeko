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


// Note: 0-base index
template<class T> class ZFunction {
  int n;
  vector<int> z; // z[i] = max{l, s[i..i + l - 1] is a prefix of s, or 0 if s[i] != s[0]}
public:
  // O(n)
  template<class Iterator> ZFunction(Iterator begin, Iterator end) {
    n = (int) (end - begin);
    z.resize(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
      if (i <= r) {
        z[i] = min(r - i + 1, z[i - l]);
      }
      while (i + z[i] < n && *(begin + z[i]) == *(begin + i + z[i])) {
        ++z[i];
      }
      if (i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
      }
    }
  }
  
  int get(int i) const {
    assert(0 <= i && i < n);
    return z[i];
  }
};

// 0 based index
template<class T> class StringPeriod {
  int n;
  vector<int> period; // period[i] = min{l, s[0..(l - 1)] is a base string of s[0..i]}
public:
  // O(nlogn)
  template<class Iterator> StringPeriod(Iterator begin, Iterator end) {
    n = (int) (end - begin);
    period.resize(n);
    ZFunction<char> z(begin, end);
    
    for_dec_range(len, n, 1) {
      for (int end = len - 1; end < n; end += len) {
        int start = end - len + 1;
        if (z.get(start) < len) break;
        period[end] = len;
      }
    }
  }
  
  int get(int i) const {
    assert(0 <= i && i < n);
    return period[i];
  }
};


void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int nTest;
int n;
string s;

void solve() {
  StringPeriod<char> p(s.begin(), s.end());
  
  for_inc(i, n) {
    if (p.get(i) != (i + 1)) {
      cout << i + 1 << " " << (i + 1) / p.get(i) << endl;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> nTest;
  for_inc_range(test, 1, nTest) {
    cin >> n;
    cin >> s;
    cout << "Test case #" << test << endl;
    solve();
    cout << endl;
  }
  return 0;
}
