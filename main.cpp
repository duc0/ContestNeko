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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 23
#define MAXS MAXN*MAXN

#define MALE 0
#define FEMALE 1

char board[MAXN][MAXN];

int row[MAXS], col[MAXS], speed[MAXS], type[MAXS];

int nRow, nCol, nMale, nFemale;

int dist[MAXN][MAXN][MAXN][MAXN];

#define REPROW(x) for (int x = 0; x < nRow; ++x)
#define REPCOL(x) for (int x = 0; x < nCol; ++x)

int main() {
  //testGen();
  freopen("input1.txt", "r", stdin);
  
  cin >> nRow >> nCol >> nMale >> nFemale;
  if ((nMale + nFemale) % 2 == 0) {
    cout << -1;
    return 0;
  }
  if (abs(nMale - nFemale) >= 2) {
    cout << -1;
    return 0;
  }
  REPROW(i) {
    cin >> board[i];
    assert(strlen(board[i]) == nCol);
  }
  cin >> row[0] >> col[0] >> speed[0];
  if (nMale == nFemale + 1) {
    type[0] = FEMALE;
  }
  for (int i = 0; i < nMale; ++i) {
    cin >> row[i + 1] >> col[i + 1] >> speed[i + 1];
    type[i + 1] = MALE;
  }
  for (int i = 0; i < nFemale; ++i) {
    cin >> row[i + 1 + nMale] >> col[i + 1 + nMale] >> speed[i + 1 + nMale];
    type[i + 1 + nMale] = FEMALE;
  }
  
  REPROW(r) REPCOL(c) REPROW(r2) REPCOL(c2) {
    dist[r][c][r2][c2] = INT_INF;
    if (r2 == r && c2 == c) {
      dist[r][c][r2][c2] = 0;
    } else if (abs(r2 - r) + abs(c2 - c) == 1) {
      if (board[r][c] != '#' && board[r2][c2] != '#') {
        dist[r][c][r2][c2] = 1;
      }
    }
  }
  
  REPROW(rk) REPCOL(ck) REPROW(r) REPCOL(c) REPROW(r2) REPCOL(c2) {
    dist[r][c][r2][c2] = min (dist[r][c][r2][c2], dist[r][c][rk][ck] + dist[rk][ck][r2][c2]);
  }
  
  
    
  return 0;
}