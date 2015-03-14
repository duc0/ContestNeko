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
  int n, minIndex, maxIndex;

public:
  BinaryIndexedTree(int n) : BinaryIndexedTree(1, n) {}

  BinaryIndexedTree(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    this->n = maxIndex - minIndex + 1;
    val.resize(n + 1);
  }

  void add(int i, int v) {
    i = i - minIndex + 1;
    for (; i <= n; i += i & -i) {
      val[i] += v;
    }
  }
  T sum(int i) {
    i = i - minIndex + 1;
    if (i <= 0)
      return 0;
    if (i > n)
      i = n;
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
  freopen("input1.txt", "r", stdin);
#endif

  int n, q;
  scanf("%d%d", &n, &q);
  vector<pair<int, int>> a(n + 1);

  for_inc_range(i, 1, n) {
    int x;
    scanf("%d", &x);
    a[i] = make_pair(x, i);
  }

  vector<pair<int, int>> query(q + 1);

  for_inc_range(i, 1, q) {
    int l, r;
    scanf("%d%d", &l, &r);
    query[i] = make_pair(l, r);
  }

  sort(a.begin() + 1, a.end());

  vector<int64> qResult(q + 1);

  vector<int> inQ(q + 1);

  for_inc_range(i, 1, n) {
    int v = a[i].first;
    int pos = a[i].second;

    for_inc_range(j, 1, q) {
      int l = query[j].first, r = query[j].second;
      if (l <= pos && pos <= r) {
        qResult[j] += (int64)v * (inQ[j] + 1);
      inQ[j]++;
      }
    }
  }

  for_inc_range(i, 1, q) { cout << qResult[i] << endl; }

  return 0;
}
