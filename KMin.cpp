#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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
#include <deque>
#include <functional>

using namespace std;

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 2020
#define MAXK 2020

int nRow, nCol, nCar;
char board[MAXN][MAXN];
pair<int, int> carPos[MAXK];
int f[MAXN][MAXN];

int posLeft[MAXN][MAXN];
int posRight[MAXN][MAXN];

int ret[MAXK];

// Compute all min(ai, ..., ai + k - 1) for each i in O(n)
// Usage: KMin(k): initialize KMin algorithm with the given k
// absorb(x): absorb the next element
// getMin() return the minimum among the last absorbed k elements

template <class T> class KMin {
  deque<pair<int, T>> a;
  int k;
  int last = 0;
  function<bool(T, T)> comp;
  
public:
  KMin(int k) : KMin(k, [](T a, T b) { return a < b; }) {}
  KMin(int k, function<bool(T, T)> comp) : k(k), comp(comp) {}
  
  void absorb(T x) {
    last++;
    if (a.empty()) {
      a.push_back(make_pair(last, x));
    } else {
      while (!a.empty() && !comp(a.back().second, x)) {
        a.pop_back();
      }
      a.push_back(make_pair(last, x));
      while (!a.empty() && a.front().first <= last - k) {
        a.pop_front();
      }
    }
  }
  
  T getMin() { return a.front().second; }
};

bool ok(int side, int r, int c) {
  if (side == 1) {
    return true;
  }
  
  int top = max(1, r - side + 1), bottom = top + side - 1;
  if (bottom > nRow || top > r) {
    return false;
  }
  
  KMin<int> maxLeft(side, [](int a, int b) { return a > b; });
  KMin<int> minRight(side);
  
  for_inc_range(row, top, bottom) {
    maxLeft.absorb(posLeft[row][c] + 1);
    minRight.absorb(posRight[row][c] - 1);
  }
  
  while (1) {
    auto ml = maxLeft.getMin();
    auto mr = minRight.getMin();
    if (ml <= mr && mr - ml + 1 >= side) {
      return true;
    }
    
    top++;
    bottom++;
    if (bottom > nRow || top > r) {
      break;
    }
    maxLeft.absorb(posLeft[bottom][c] + 1);
    minRight.absorb(posRight[bottom][c] - 1);
  }
  return false;
}

void recalcRow(int r) {
  for_inc_range(c, 1, nCol) {
    char ch = board[r - 1][c - 1];
    if (ch == 'X') {
      posLeft[r][c] = c;
      posRight[r][c] = c;
    }
  }
  posLeft[r][0] = 0;
  posRight[r][nCol + 1] = nCol + 1;
  for_inc_range(c, 1, nCol) {
    char ch = board[r - 1][c - 1];
    if (ch == '.') {
      posLeft[r][c] = posLeft[r][c - 1];
    }
  }
  for_dec_range(c, nCol, 1) {
    char ch = board[r - 1][c - 1];
    if (ch == '.') {
      posRight[r][c] = posRight[r][c + 1];
    }
  }
}

// Sample: CF274 - E

int main() {
  // testGen();
  freopen("input1.txt", "r", stdin);
  
  scanf("%d%d%d", &nRow, &nCol, &nCar);
  for_inc(row, nRow) { scanf("%s", board[row]); }
  
  for_inc_range(i, 1, nCar) {
    int r, c;
    scanf("%d%d", &r, &c);
    carPos[i] = make_pair(r, c);
    board[r - 1][c - 1] = 'X';
  }
  
  ret[nCar] = 0;
  fill0(f);
  for_inc_range(r, 1, nRow) {
    for_inc_range(c, 1, nCol) {
      char ch = board[r - 1][c - 1];
      if (ch == '.') {
        f[r][c] = min(f[r - 1][c], min(f[r][c - 1], f[r - 1][c - 1])) + 1;
        ret[nCar] = max(ret[nCar], f[r][c]);
      }
    }
  }
  
  for_inc_range(r, 1, nRow) { recalcRow(r); }
  
  for_dec_range(car, nCar - 1, 1) {
    pair<int, int> pos = carPos[car + 1];
    board[pos.first - 1][pos.second - 1] = '.';
    
    recalcRow(pos.first);
    
    int l = 1, r = min(nRow, nCol), mid = 0, best = 0;
    while (l <= r) {
      mid = (l + r) / 2;
      if (ok(mid, pos.first, pos.second)) {
        best = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    
    ret[car] = max(ret[car + 1], best);
  }
  
  for_inc_range(car, 1, nCar) { cout << ret[car] << endl; }
  
  return 0;
}