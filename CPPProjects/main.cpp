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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input2.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  
  string p;
  cin >> p;
  int l = (int) p.length();
  
  ZFunction<char> z(p.begin(), p.end());
  
  RangeUpdateArrayOffline<int> a(n);
  
  int last = -1;
  
  repeat(m) {
    int y;
    cin >> y;
    
    a.add(y, y + l - 1, 1);
    
    if (last != -1) {
      int diff = y - last;
      if (diff <= l - 1 && z.get(diff) < l - diff) {
        cout << 0 << endl;
        exit(0);
      }
    }
    
    last = y;
  }
  
  for_inc_range(d, 0, n - l) {

  }
  
  
  
  vector<int> final = a.getArray();
  
  int cnt = 0;
  int64 ans = 1;
  for_inc_range(i, 1, n) {
    if (final[i] == 0) {
      cnt++;
      ans = (ans * 26) % MOD;
    }
  }
  
  cout << ans << endl;
  
  return 0;
}
