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
#include <unordered_set>
#include <unordered_map>
#include <random>

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

template<class T> struct Point2D {
  T x, y;
  bool operator < (const Point2D &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
  bool operator == (const Point2D &p) const {
    return x == p.x && y == p.y;
  }
};
template<class T> Point2D<T> makePoint(T x, T y) {
  return Point2D<T>{x, y};
}
namespace std {
  template <class T>
  struct hash<Point2D<T>>
  {
    size_t operator()(const Point2D<T>& k) const
    {
      return (hash<T>()(k.x) ^ hash<T>()(k.y));
    }
  };
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  int n = 100000;
  cout << n << endl;
  unordered_set<Point2D<int64>> p;
  
  random_device rd;
  mt19937_64 gen(rd());
  uniform_int_distribution<int64> dis;
  const int64 MAX = 1000;
  
  repeat(n) {
    while(1) {
      int64 x = dis(gen) % MAX;
      int64 y = dis(gen) % MAX;
      if (p.find(makePoint(x, y)) == p.end()) {
        p.insert(makePoint(x, y));
        cout << x << " " << y << endl;
        break;
      }
    }
  }
  fclose(stdout);
}

int n;
unordered_map<int64, unordered_set<int64>> byX;
unordered_map<int64, unordered_set<int64>> byY;

vector<Point2D<int64>> points;

// Sample: CF243 D

int main() {
#ifndef SUBMIT
  //testGen();
  freopen("biginput1.txt", "r", stdin);
#endif
  
  cin >> n;
  int64 x, y;
  int64 cnt = 0;
  repeat(n) {
    cin >> x >> y;
    auto p = makePoint(x, y);
    points.push_back(p);
    byX[x].insert(y);
    byY[y].insert(x);
  }
  
  int ret = 0;
  for (auto &p: points) {
    auto &xPoints = byX[p.x];
    auto &yPoints = byY[p.y];
    
    if (xPoints.size() < yPoints.size()) {
      cnt += xPoints.size();
      for (auto &y2 : xPoints) if (y2 > p.y) {
        int64 side = y2 - p.y;
        if (yPoints.find(p.x + side) != yPoints.end()) {
          auto x2Points = byX.find(p.x + side);
          if (x2Points != byX.end() && (x2Points->second).find(p.y + side) != (x2Points->second).end()) {
            ++ret;
          }
        }
      }
    } else {
      cnt += yPoints.size();
      for (auto &x2 : yPoints) if (x2 > p.x) {
        int64 side = x2 - p.x;
        if (xPoints.find(p.y + side) != xPoints.end()) {
          auto x2Points = byX.find(x2);
          if (x2Points != byX.end() && (x2Points->second).find(p.y + side) != (x2Points->second).end()) {
            ++ret;
          }
        }
      }
    }
  }
  
  //cout << cnt << endl;
  cout << ret << endl;
  return 0;
}
