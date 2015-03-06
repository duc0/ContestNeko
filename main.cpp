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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template <class T> class BinaryIndexedTree {
  vector<T> val;
  int n, minIndex, maxIndex;
  
public:
  BinaryIndexedTree(int n): BinaryIndexedTree(1, n) {}
  
  BinaryIndexedTree(int minIndex, int maxIndex) {
    init(minIndex, maxIndex);
  }
  
  BinaryIndexedTree() {}
  
  void init(int minIndex, int maxIndex) {
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

template <class T> class RangeUpdateArray {
  BinaryIndexedTree<T> tree;
  int minIndex, maxIndex;
  
public:
  RangeUpdateArray(int n): RangeUpdateArray(1, n) {}

  RangeUpdateArray(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    tree.init(minIndex, maxIndex);
  }

  void add(int i, int j, T v) {
    assert(minIndex <= i && i <= j && j <= maxIndex);
    if (j < maxIndex) {
      tree.add(j + 1, -v);
    }
    tree.add(i, v);
  }

  T get(int i) {
    assert (minIndex <= i && i <= maxIndex);
    return tree.sum(i);
  }
  
  const T operator[](int i) {
    return get(i);
  }
};

int n;
vector<pair<int, int>> a;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n;
  int maxH = 0;
  repeat(n) {
    int h, k;
    cin >> h >> k;
    a.push_back(make_pair(h, k));
    maxH = max(maxH, h);
  }
  
  sort(a.begin(), a.end());
  
  int curH = 0;
  RangeUpdateArray<int> s(0, maxH - 1);
  for (auto &p: a) {
    int h = p.first, k = p.second;
    if (h > curH) {
      curH = h;
    }
    int need = k;
    int i = curH - 1;
    while (need > 0) {
      int skip = 0;
      while (i > 0 && s[i - 1] == s[i]) {
        --i;
        ++skip;
      }
      int j = i + min(need - 1, skip);
      need -= (j - i + 1);
      if (i >= 0 && i <= j) {
        s.add(i, j, 1);
      }
      --i;
    }
  }
  
  int64 ret = 0;
  for (int i = 0; i < maxH; ++i) {
    int x = s[i];
    ret += (int64) x * (x - 1) / 2;
  }
  
  cout << ret << endl;
  return 0;
}
