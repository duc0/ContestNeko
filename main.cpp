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

int nRow, nCol;
char board[MAXN][MAXN];

int getAt(int r, int c) {
  if (r < 0 || r >= nRow || c < 0 || c >= nCol) return 0;
  return board[r][c] == '.';
}

int getDeg(int r, int c) {
  return getAt(r - 1, c) + getAt(r, c - 1) + getAt(r + 1, c) + getAt(r, c + 1);
}

set<pair<int, pair<int, int>>> node;

int main() {
  //testGen();
  freopen("input1.txt", "r", stdin);
  
  scanf("%d%d", &nRow, &nCol);
  for_inc(r, nRow) {
    scanf("%s", board[r]);
  }
  
  for_inc(r, nRow) for_inc(c, nCol) {
    if (board[r][c] == '.') {
      int deg = getDeg(r, c);
      if (deg == 0) {
        // No sol
        cout << "Not unique";
        return 0;
      }
      node.insert(make_pair(deg, make_pair(r, c)));
    }
  }
  
  while (node.size() > 0) {
    auto p = node.begin();
    if (p->first > 1) {
      cout << "Not unique";
      return 0;
    }
    int r = p->second.first;
    int c = p->second.second;
    if (getAt(r - 1, c) == 1) {
      board[r-1][c] = '^';
      board[r][c] = 'v';
      update(r - 1, c);
      update(r, c);
    }
  }
  
  return 0;
}