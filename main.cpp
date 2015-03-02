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

template <class T> struct Point2D {
  T x, y;
  bool operator<(const Point2D &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  bool operator==(const Point2D &p) const { return x == p.x && y == p.y; }
  Point2D operator+(const Point2D &p) const {
    return Point2D{x + p.x, y + p.y};
  }
  Point2D operator-(const Point2D &p) const {
    return Point2D{x - p.x, y - p.y};
  }
  T dotProduct(const Point2D &p) const { return x * p.x + y * p.y; }
  T crossProduct(const Point2D &p) const { return x * p.y - y * p.x; }
  T distance(const Point2D &p) const {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  }
  friend std::ostream& operator<< (std::ostream& stream, const Point2D<T>& p) {
    stream << "Point (" << p.x << ", " << p.y << ")";
    return stream;
  }

};
template <class T>
T cross(const Point2D<T> &o, const Point2D<T> &a, const Point2D<T> &b) {
  return (a - o).crossProduct(b - o);
}
template <class T> Point2D<T> makePoint(T x, T y) { return Point2D<T>{x, y}; }
namespace std {
template <class T> struct hash<Point2D<T>> {
  size_t operator()(const Point2D<T> &k) const {
    return (hash<T>()(k.x) ^ hash<T>()(k.y));
  }
};
}

template <class T> class ConvexHull {
  vector<Point2D<T>> upper;
  vector<Point2D<T>> lower;

public:
  ConvexHull(const vector<Point2D<T>> &points) {
    vector<Point2D<T>> p = points;
    int j = 0, k = 0, n = (int) p.size();
    sort(p.begin(), p.end());
    upper.resize(2 * n);
    lower.resize(2 * n);
    for_inc(i, n) {
      while (j >= 2 && cross(lower[j - 2], lower[j - 1], p[i]) <= 0)
        j--;
      while (k >= 2 && cross(upper[k - 2], upper[k - 1], p[i]) >= 0)
        k--;
      lower[j++] = p[i];
      upper[k++] = p[i];
    }
    upper.resize(k);
    lower.resize(j);
  }

  const vector<Point2D<T>> &getUpperHull() const { return upper; }

  const vector<Point2D<T>> &getLowerHull() const { return lower; }
};

template <class T> class FarthestTwoPoints {
  T dist;

public:
  FarthestTwoPoints(const vector<Point2D<T>> &p) {
    ConvexHull<T> ch(p);
    const vector<Point2D<T>> u = ch.getUpperHull();
    const vector<Point2D<T>> &l = ch.getLowerHull();
    int i = 0, j, m;
    j = (int)u.size() - 1;
    m = (int)l.size() - 1;
    dist = numeric_limits<T>::min();
    while (i < m || j > 0) {
      T d =  u[i].distance(l[j]);
      if (d > dist) {
        dist = d;
        LOG(1, "Point1: " << u[i]);
        LOG(1, "Point2: " << l[j]);
      }
      if (i == m)
        j--;
      else if (j == 0)
        i++;
      else {
        if ((l[j] - l[j - 1]).crossProduct(u[i + 1] - u[i]) > 0)
          i++;
        else
          j--;
      }
    }
  }

  T getFarthestDistance() { return dist; }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  int x;
  int64 s = 0;
  
  vector<Point2D<int64>> p;
  for_inc_range(i, 1, n) {
    cin >> x;
    s += x;
    p.push_back(makePoint((int64)i, s));
  }
  
  FarthestTwoPoints<int64> ftp(p);
  cout << ftp.getFarthestDistance() << endl;
  return 0;
}
