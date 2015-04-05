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

template <class T> class RangeQuery {
  size_t n, k;
  vector<vector<T>> a;
public:
  virtual inline const T& combine(const T &a, const T &b) const = 0;
  
  template <class Iterator>
  void init(Iterator begin, Iterator end) {
    n = end - begin;
    k = -1;
    size_t s = n;
    while (s > 0) {
      s >>= 1;
      ++k;
    }
    a.resize(k + 1);
    for (int i = 0; i <= k; ++i) {
      a[i].resize(n + 1 - (1 << i));
    }
    auto it = begin;
    for (int i = 0; i < n; ++i) {
      a[0][i] = *it;
      ++it;
    }
    for (int t = 1; t <= k; ++t) {
      for (int i = 0; i <= n - (1 << t); ++i) {
        a[t][i] = combine(a[t - 1][i], a[t - 1][i + (1 << (t - 1))]);
      }
    }
  }
  
  T query(int i, int j) {
    int t = 31 - __builtin_clz(j - i + 1);
    int m = j + 1 - (1 << t);
    return combine(a[t][i], a[t][m]);
  }
};

template <class T> class RangeMinimumQuery: public RangeQuery<T> {
public:
  virtual inline const T& combine(const T &a, const T &b) const {
    return min(a, b);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  int n = 100000;
  cout << n << endl;
  repeat(n) {
    cout << rand() % 1000000000 + 1 << " ";
  }
  cout << endl;
  int m = (int) 1E8;
  cout << m << endl;
  cout << 0 << " " << 1 << endl;
  fclose(stdout);
}

int n, m;
vector<int> a;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("biginput1.txt", "r", stdin);
#endif
  
  scanf("%d", &n);
  a.resize(n + 1);
  for_inc_range(i, 1, n) {
    scanf("%d", &a[i]);
    a[i] = -a[i];
  }
  
  RangeMinimumQuery<int> rmq;
  rmq.init(a.begin(), a.end());
  
  int64 ret = 0;
  int x, y;
  scanf("%d", &m);
  scanf("%d%d", &x, &y);
  repeat(m) {
    ret += -rmq.query(min(x, y) + 1, max(x, y) + 1);
    
    x += 7;
    while (x >= (n - 1)) x -= (n - 1);
    y += 11;
    while (y >= n) y -= n;
  }
  
  cout << ret << endl;
  return 0;
}
