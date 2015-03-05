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

template <class T> class BinaryIndexedTree {
  vector<T> val;
  int n, minIndex, maxIndex;
  
public:
  BinaryIndexedTree(int n): BinaryIndexedTree(1, n) {}
  
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
    if (i <= 0) return 0;
    if (i > n) i = n;
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

int b, n, d, m;

void solveSmall() {
  vector<vector<int>> p;
  repeat(n) {
    vector<int> point;
    repeat(b) {
      int x;
      scanf("%d", &x);
      point.push_back(x);
    }
    p.push_back(point);
  }
  int ret = 0;
  for_inc(i, n) {
    for_inc(j, i) {
      int dist = 0;
      for_inc(k, b) {
        dist += abs(p[i][k] - p[j][k]);
      }
      if (dist <= d) {
        ++ret;
      }
    }
  }
  cout << ret << endl;
}

void solve1() {
  vector<int> a;
  repeat(n) {
    int x;
    scanf("%d", &x);
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  int j = 0;
  int64 ret = 0;
  for_inc(i, n) {
    while (j < i && a[i] - a[j] > d) ++j;
    ret += i - j;
  }
  cout << ret << endl;
}

void solve2() {
  vector<pair<int, int>> a;
  repeat(n) {
    int x, y;
    scanf("%d%d", &x, &y);
    a.push_back(make_pair(x, y));
  }
  
  sort(a.begin(), a.end(), [](const pair<int, int> &p1, const pair<int, int> &p2){ return p1.first + p1.second < p2.first + p2.second; });
  
  BinaryIndexedTree<int> tree(1 - m, m - 1);
  
  int j = 0;
  int64 ret = 0;
  
  for_inc(i, n) {
    while (j < i && a[j].first + a[j].second + d < a[i].first + a[i].second) {
      tree.add(a[j].first - a[j].second, - 1);
      ++j;
    }
    ret += tree.sum(a[i].first - a[i].second - d, a[i].first - a[i].second + d);
    tree.add(a[i].first - a[i].second, 1);
  }
  
  cout << ret << endl;
  
}
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("biginput1.txt", "r", stdin);
#endif
  
  scanf("%d%d%d%d", &b, &n, &d, &m);
  if (n <= 2000) {
    solveSmall();
  } else {
    if (b == 1) {
      solve1();
    } else if (b == 2) {
      solve2();
    }
  }
  
  return 0;
}
