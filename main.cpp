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
  RangeUpdateArray() {}
  
  RangeUpdateArray(int n) {
    init(1, n);
  }
  
  RangeUpdateArray(int minIndex, int maxIndex) {
    init(minIndex, maxIndex);
  }
  
  void init(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    tree.init(minIndex, maxIndex);
  }
  
  // Do a[k] = a[k] + v for i <= k <= j
  // O(logn)
  void add(int i, int j, T v) {
    assert(minIndex <= i && i <= j && j <= maxIndex);
    if (j < maxIndex) {
      tree.add(j + 1, -v);
    }
    tree.add(i, v);
  }
  
  // Return a[i] in O(logn)
  T get(int i) {
    assert (minIndex <= i && i <= maxIndex);
    return tree.sum(i);
  }
  
  const T operator[](int i) {
    return get(i);
  }
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
  
  int nTest;
  
  cin >> nTest;
  repeat(nTest) {
    int n, k;
    cin >> n >> k;
    
    string s;
    cin >> s;
    
    RangeUpdateArray<int> a(1, n);
    for_inc(i, n) {
      if (s[i] == 'R') {
        a.add(i + 1, i + 1, 1);
      }
    }
    
    int ret = 0;
    for_inc_range(i, 1, n) {
      if (a[i] % 2 == 1) {
        a.add(i, min(n, i + k - 1), 1);
        ret ++;
      }
    }
    
    cout << ret << endl;
  }
  return 0;
}
