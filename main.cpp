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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)

#define for_inc(i,x) for(auto i=0; i < x;++i)
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
#define for_inc_range(i,x,y) for (auto i=x; i<=y; ++i)
#define for_dec_range(i,x,y) for (auto i=x; i>=y; --i)

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

int ret[MAXK];

set<int> carAt[MAXN];

set<pair<int, int>> carIn;

bool isGood(int side, int c) {
  int minLeft = 1, maxRight = nCol;
  auto nextCar = carIn.lower_bound(make_pair(c, 0));
  if (nextCar != carIn.end()) {
    if (nextCar->first != c) {
      maxRight = nextCar->first - 1;
    } else {
      return false;
    }
  }
  if (nextCar != carIn.begin()) {
    nextCar--;
    minLeft = nextCar->first + 1;
  }
  return minLeft <= maxRight && maxRight - minLeft + 1 >= side;
}

void doRelevant(int row, int c, bool del) {
  auto p = carAt[row].lower_bound(c);
  if (p != carAt[row].end()) {
    auto q = make_pair(*p, row);
    if (del) {
      carIn.erase(q);
    } else {
      carIn.insert(q);
    }
  }
  if (p != carAt[row].begin()) {
    p--;
    auto q = make_pair(*p, row);
    if (del) {
      carIn.erase(q);
    } else {
      carIn.insert(q);
    }
  }
}

bool ok(int side, int r, int c) {
  if (side == 1) {
    return true;
  }
  
  int top = max(1, r - side + 1), bottom = top + side - 1;
  if (bottom > nRow || top > r) {
    return false;
  }
  carIn.clear();
  for_inc_range(row, top, bottom) {
    doRelevant(row, c, false);
  }
  
  while (1) {
    if (isGood(side, c)) {
      return true;
    }
    
    doRelevant(top, c, true);
    top++;
    bottom++;
    if (bottom > nRow || top > r) {
      break;
    }
    doRelevant(bottom, c, false);
    
  }
  return false;
}

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  scanf("%d%d%d", &nRow, &nCol, &nCar);
  for_inc(row, nRow) {
    scanf("%s", board[row]);
  }
  
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
  
  for_inc_range(r, 1, nRow) {
    for_inc_range(c, 1, nCol) {
      char ch = board[r - 1][c - 1];
      if (ch == 'X') {
        carAt[r].insert(c);
      }
    }
  }

  for_dec_range(car, nCar - 1, 1) {
    pair<int, int> pos = carPos[car + 1];
    board[pos.first - 1][pos.second - 1] = '.';
    
    assert(carAt[pos.first].count(pos.second));
    carAt[pos.first].erase(pos.second);
    
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
  
  for_inc_range(car, 1, nCar) {
    cout << ret[car] << endl;
  }
  
  return 0;
}