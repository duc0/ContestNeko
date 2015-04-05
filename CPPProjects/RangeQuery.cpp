#include <cstdio>
#include <algorithm>
#include <cstring>

#define NDEBUG
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
#import <functional>
#import <stack>

using namespace std;

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
#define INT64_INF 1E18L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template <class T> class RangeQuery {
  size_t n, k;
  vector<vector<T>> a;
  function<T(T, T)> combine;
  
public:
  RangeQuery() {}
  
  template <class Iterator>
  RangeQuery(Iterator begin, Iterator end) {
    init(begin, end);
  }
  
  template <class Iterator>
  RangeQuery(Iterator begin, Iterator end, const function<T(T, T)> &combine) {
    init(begin, end, combine);
  }
  
  // The default combine function is min (Range Minimum Query).
  template <class Iterator>
  void init(Iterator begin, Iterator end) {
    init(begin, end, [](const T &a, const T &b) { return min(a, b); });
  }
  
  template <class Iterator>
  void init(Iterator begin, Iterator end, const function<T(T, T)> &combine) {
    this->combine = combine;
    n = end - begin;
    k = -1;
    size_t s = n;
    while (s > 0) {
      s >>= 1;
      ++k;
    }
    a.resize(k + 1);
    for (int i = 0; i <= k; ++i) {
      a[i].resize(n + 1 - (1 << i));
    }
    auto it = begin;
    for (int i = 0; i < n; ++i) {
      a[0][i] = *it;
      ++it;
    }
    for (int t = 1; t <= k; ++t) {
      for (int i = 0; i <= n - (1 << t); ++i) {
        a[t][i] = combine(a[t - 1][i], a[t - 1][i + (1 << (t - 1))]);
      }
    }
  }
  
  T query(int i, int j) {
    int t = 31 - __builtin_clz(j - i + 1);
    int m = j + 1 - (1 << t);
    return combine(a[t][i], a[t][m]);
  }
};

#define MAXN 200100

// Sample problem: CF292_C

struct Node {
  int64 best;
  int bestId1, bestId2;
};

int n, q;

int64 h[MAXN];
int64 d[MAXN];
int64 dst[MAXN];

Node hplusd[MAXN];
Node hminusd[MAXN];

int main() {
  // testGen();
  //freopen("input1.txt", "r", stdin);
  
  cin >> n >> q;
  for_inc_range(i, 1, n) { cin >> dst[i]; }
  for_inc_range(i, 1, n) { cin >> h[i]; }
  
  for_inc_range(i, n + 1, 2 * n) {
    dst[i] = dst[i - n];
    h[i] = h[i - n];
  }
  
  n = n * 2;
  d[1] = 0;
  for_inc_range(i, 2, n) { d[i] = d[i - 1] + dst[i - 1]; }
  
  for_inc_range(i, 1, n) {
    hplusd[i - 1] = Node{2 * h[i] + d[i], i - 1, -1};
    hminusd[i - 1] = Node{2 * h[i] - d[i], i - 1, -1};
  }
  
  auto good = [](int x, initializer_list<int> ys) {
    for (auto y : ys)
      if (y != -1 && y != x)
        return y;
    return *ys.begin();
  };
  auto combineNode = [&good](Node a, Node b) {
    if (a.best < b.best)
      return b;
    if (a.best > b.best)
      return a;
    return Node{a.best, a.bestId1,
      good(a.bestId1, {a.bestId2, b.bestId1, b.bestId2})};
  };
  
  RangeQuery<Node> rmqplus(hplusd, hplusd + n, combineNode);
  RangeQuery<Node> rmqminus(hminusd, hminusd + n, combineNode);
  
  int a, b;
  int leftBound, rightBound;
  repeat(q) {
    cin >> a >> b;
    if (a <= b) {
      leftBound = b + 1;
      rightBound = a - 1 + n / 2;
    } else {
      leftBound = b + 1;
      rightBound = a - 1;
    }
    
    leftBound--;
    rightBound--;
    
    Node mplus;
    Node mminus;
    
    int64 best = -INT64_INF, bt;
    
    int id;
    
    mplus = rmqplus.query(leftBound, rightBound);
    for_inc(loop, 2) {
      if (loop == 0) {
        id = mplus.bestId1;
      } else {
        id = mplus.bestId2;
      }
      if (id == -1)
        continue;
      bt = -INT64_INF;
      if (leftBound <= id - 1) {
        bt = max(bt, rmqminus.query(leftBound, id - 1).best);
      }
      if (id + 1 <= rightBound) {
        bt = max(bt, rmqminus.query(id + 1, rightBound).best);
      }
      best = max(best, mplus.best + bt);
    }
    
    mminus = rmqminus.query(leftBound, rightBound);
    for_inc(loop, 2) {
      if (loop == 0) {
        id = mminus.bestId1;
      } else {
        id = mminus.bestId2;
      }
      if (id == -1)
        continue;
      bt = -INT64_INF;
      if (leftBound <= id - 1) {
        bt = max(bt, rmqplus.query(leftBound, id - 1).best);
      }
      if (id + 1 <= rightBound) {
        bt = max(bt, rmqplus.query(id + 1, rightBound).best);
      }
      best = max(best, mminus.best + bt);
    }
    
    cout << best << endl;
  }
  
  return 0;
}