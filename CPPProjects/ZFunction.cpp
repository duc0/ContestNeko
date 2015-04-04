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

template <class T> class RangeUpdateArrayOffline {
  vector<T> diff;
  int n;
  
public:
  RangeUpdateArrayOffline() {}
  
  RangeUpdateArrayOffline(int n) {
    init(n);
  }
  
  void init(int n) {
    this->n = n;
    diff.resize(n + 1);
  }
  
  // Do a[k] = a[k] + v for i <= k <= j
  // O(1)
  void add(int i, int j, T v) {
    assert(1 <= i && i <= j && j <= n);
    diff[i] += v;
    if (j + 1 <= n) {
      diff[j + 1] -= v;
    }
  }
  
  vector<T> getArray() {
    vector<T> ret(n + 1);
    ret[0] = 0;
    for_inc_range(i, 1, n) {
      ret[i] = ret[i - 1] + diff[i];
    }
    return ret;
  }
  
};

// Note: 0-base index
template<class T> class ZFunction {
  vector<T> s;
  int n;
  
  vector<int> z; // z[i] = max{l, s[i..i + l - 1] is a prefix of s, or 0 if s[i] != s[0]}
public:
  template<class Iterator> ZFunction(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; it++) {
      s.push_back(*it);
    }
    n = (int) s.size();
    z.resize(n + 1);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
      if (i <= r) {
        z[i] = min(r - i + 1, z[i - l]);
      }
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Zepto 2015 - D

int n, k;
string s;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  cin >> n >> k;
  cin >> s;
  ZFunction<char> z(s.begin(), s.end());
  
  RangeUpdateArrayOffline<int> good(n);
  
  for (int ablen = 1; ablen * k <= n; ++ablen) {
    if (z.get(ablen) >= ablen * (k - 1)) {
      int l = ablen * k - 1;
      int r = l+ min(ablen, z.get(ablen * k));
      good.add(l + 1, r + 1, 1);
    }
  }
  
  vector<int> ret = good.getArray();
  string ans = s;
  for_inc_range(i, 1, n) {
    if (ret[i] > 0) {
      ans[i - 1] = '1';
    } else {
      ans[i - 1] = '0';
    }
  }
  cout << ans << endl;
  return 0;
}
