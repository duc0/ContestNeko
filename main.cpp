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

#define LOG(l, x)                                                              \
  if (l <= LOGLEVEL)                                                           \
  cout << x << endl

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
  if (r < 0)
    r += MOD;
  return r;
}

template <class T> class BinaryIndexedTree {
  vector<T> val;
  int n;

public:
  BinaryIndexedTree(int n) {
    this->n = n;
    val.resize(n + 1);
  }
  void add(int i, int v) {
    for (; i <= n; i += i & -i)
      val[i] += v;
  }
  T sum(int i) {
    assert(i >= 0);
    if (i == 0)
      return 0;
    T s = 0;
    for (; i > 0; i -= i & -i)
      s += val[i];
    return s;
  }
  T sum(int i1, int i2) { return sum(i2) - sum(i1 - 1); }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif

  int n;
  cin >> n;
  vector<int> a(n);
  for_inc(i, n) { cin >> a[i]; }
  map<int, int> seen;
  vector<pair<int, int>> f(n), g(n);
  for_inc(i, n) { f[i] = make_pair(++seen[a[i]], i); }
  seen.clear();
  for_dec(i, n) { g[i] = make_pair(++seen[a[i]], i); }

  sort(f.begin(), f.end());
  sort(g.begin(), g.end());

  int j = 0;

  BinaryIndexedTree<int> tree(n);
  int64 ret = 0;
  for_inc(i, n) {
    while (j < n && g[j].first < f[i].first) {
      tree.add(g[j].second + 1, 1);
      ++j;
    }
    ret += tree.sum(f[i].second + 1 + 1, n);
  }
  cout << ret << endl;

  return 0;
}
