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

template <class T> struct Point3D {
  T x, y, z;
};
template <class T> Point3D<T> makePoint(T x, T y, T z) { return Point3D<T>{x, y, z}; }


inline int v1(const Point3D<int> &a) {
  return a.x + a.y - a.z;
}

inline int v2(const Point3D<int> &a) {
  return a.x + a.z - a.y;
}

inline int v3(const Point3D<int> &a) {
  return a.y + a.z - a.x;
}


void solve3() {
  vector<Point3D<int>> a;
  repeat(n) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    a.push_back(makePoint(x, y, z));
  }
  
  sort(a.begin(), a.end(), [](const Point3D<int> &p1, const Point3D<int> &p2){ return p1.x + p1.y + p1.z < p2.x + p2.y + p2.z; });
  
  BinaryIndexedTree3D<int> tree(2 - m, 2 * m - 1);
  
  int j = 0;
  int64 ret = 0;
  
  for_inc(i, n) {
    while (j < i && a[j].x + a[j].y + a[j].z + d < a[i].x + a[i].y + a[i].z) {
      tree.add(v1(a[j]), v2(a[j]), v3(a[j]), -1);
      ++j;
    }
    
    int s = tree.sum(v1(a[i]) - d, v2(a[i]) - d, v3(a[i]) - d, v1(a[i]) + d, v2(a[i]) + d, v3(a[i]) + d);
    ret += s;
    tree.add(v1(a[i]), v2(a[i]), v3(a[i]), 1);
  }
  
  cout << ret << endl;
}

// Sample: IOI 2007 PAIRS

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  scanf("%d%d%d%d", &b, &n, &d, &m);
  if (n <= 2000) {
    solveSmall();
  } else {
    if (b == 1) {
      solve1();
    } else if (b == 2) {
      solve2();
    } else if (b == 3) {
      solve3();
    }
  }
  
  return 0;
}
