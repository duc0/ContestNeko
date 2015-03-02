#define SUBMIT

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
  friend std::ostream &operator<<(std::ostream &stream, const Point2D<T> &p) {
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

template <class T> class ClosestTwoPoints {
  void findClosest(const vector<Point2D<T>> &px, const vector<Point2D<T>> &py, const int n) {
    if (n <= 3)
      return bruteForce(px, n);
    
    int mid = n/2;
    Point2D<T> midPoint = px[mid];
    
    
    // Divide points in y sorted array around the vertical line.
    // Assumption: All x coordinates are distinct.
    Point Pyl[mid+1];   // y sorted points on left of vertical line
    Point Pyr[n-mid-1];  // y sorted points on right of vertical line
    int li = 0, ri = 0;  // indexes of left and right subarrays
    for (int i = 0; i < n; i++)
    {
      if (Py[i].x <= midPoint.x)
        Pyl[li++] = Py[i];
      else
        Pyr[ri++] = Py[i];
    }
    
    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = closestUtil(Px, Pyl, mid);
    float dr = closestUtil(Px + mid, Pyr, n-mid);
    
    // Find the smaller of two distances
    float d = min(dl, dr);
    
    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
      if (abs(Py[i].x - midPoint.x) < d)
        strip[j] = Py[i], j++;
    
    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d) );
    
  }
  
public:
  ClosestTwoPoints(const vector<Point2D<T>> &p) {
    assert(p.size() >= 2);
    
    int n = p.size();
    
    vector<Point2D<T>> px;
    vector<Point2D<T>> py;
    for (auto &a : p) {
      px.push_back(a);
      py.push_back(a);
    }
    sort(px.begin(), px.end());
    sort(py.begin(), py.end(), [](const Point2D<T> &a, const Point2D<T> &b){ return a.y < b.y || (a.y == b.y && a.x < b.x); });
    
    findClosest(px, py, n);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  return 0;
}
