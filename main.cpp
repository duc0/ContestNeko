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

template <class T> class BinaryIndexedTree3D {
  vector<vector<vector<T>>> val;
  int n, minIndex, maxIndex;
  
public:
  BinaryIndexedTree3D(int n): BinaryIndexedTree3D(1, n) {}
  
  BinaryIndexedTree3D(int minIndex, int maxIndex) {
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
    this->n = maxIndex - minIndex + 1;
    val.resize(n + 1);
    for_inc_range(i, 1, n) {
      val[i].resize(n + 1);
      for_inc_range(j, 1, n) {
        val[i][j].resize(n + 1);
      }
    }
  }
  
  void add(int x0, int y0, int z0, int v) {
    x0 = x0 - minIndex + 1;
    y0 = y0 - minIndex + 1;
    z0 = z0 - minIndex + 1;
    for (int x = x0; x <= n; x += x & -x) for (int y = y0; y <= n; y += y & - y) for (int z = z0; z <= n; z += z & -z) {
      val[x][y][z] += v;
    }
  }
  
  T sum(int x0, int y0, int z0) {
    x0 = x0 - minIndex + 1;
    y0 = y0 - minIndex + 1;
    z0 = z0 - minIndex + 1;
    if (x0 <= 0 || y0 <= 0 || z0 <= 0) return 0;
    if (x0 > n) x0 = n;
    if (y0 > n) y0 = n;
    if (z0 > n) z0 = n;
    T s = 0;
    for (int x = x0; x > 0; x -= x & -x) for (int y = y0; y > 0; y -= y & -y) for (int z = z0; z > 0; z -= z & -z)
      s += val[x][y][z];
    return s;
  }
  
  T sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) - sum(x2, y2, z1 - 1)
    + sum(x1 - 1, y1 - 1, z2) + sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y2, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
  }
};


void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int solveSlow(vector<pair<int ,int>> a) {
  int ans = 0;
  int n = (int) a.size() - 1;
  for_inc_range(i, 1, n) {
    for_inc_range(j, 1, n) {
      ans += min(a[i].first, a[j].first) * abs(i - j);
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  vector<pair<int, int>> a(n + 1);
  
  for_inc_range(i, 1, n) {
    int x;
    cin >> x;
    a[i] = make_pair(x, i);
  }
  
  //LOG(1, solveSlow(a));
  
  sort(a.begin() + 1, a.end());
  
  BinaryIndexedTree<int64> sumPos(1, n);
  BinaryIndexedTree<int> present(1, n);
  
  int64 ans = 0 ;
  for_dec_range(i, n, 1) {
    int64 val = a[i].first;
    int pos = a[i].second;
    
    int64 localAns = 0;
    localAns += sumPos.sum(pos + 1, n) - pos * (int64)present.sum(pos + 1, n);
    localAns += pos * (int64)present.sum(1, pos - 1) - sumPos.sum(1, pos - 1);
    localAns = MODP(localAns);
    localAns = MODP(localAns * val);
    ans = MODP(ans + localAns);
  
    sumPos.add(a[i].second, a[i].second);
    present.add(a[i].second, 1);
  }
  
  ans = MODP(ans * 2);
  
  cout << ans << endl;
  return 0;
}
