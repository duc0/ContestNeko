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
#include <stack>
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
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0)
    r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int nRow, nCol;
vector<string> board;

int getSide(int r, int c) {
  if (r == 0 && c == 0)
    return -1;
  if (r == 0 && c == nCol - 1)
    return -1;
  if (r == nRow - 1 && c == 0)
    return -1;
  if (r == nRow - 1 && c == nCol - 1)
    return -1;
  if (r > 0 && r < nRow && c > 0 && c < nCol)
    return -1;
  if (r == 0)
    return 0;
  if (c == nCol - 1)
    return 1;
  if (r == nRow - 1)
    return 2;
  // c == 0
  return 3;
}

#define DDOWN 0
#define DLEFT 1
#define DRIGHT 2

#define MAXN 2020
int64 f[3][3][MAXN][MAXN];
int side[MAXN][MAXN];

vector<string> boardRotate;

void rotateBoard() {
  int nRowNew = nCol;
  int nColNew = nRow;
  boardRotate.resize(nRowNew);
  for_inc(r, nRowNew) {
    boardRotate[r].resize(nColNew);
  }
  for_inc(r, nRow) {
    for_inc(c, nCol) {
      boardRotate[c][nColNew - 1 - r] = board[r][c];
    }
  }
  nRow = nRowNew;
  nCol = nColNew;
  board = boardRotate;
}

int main() {
  //freopen("input4.txt", "r", stdin);
  cin >> nRow >> nCol;
  board.resize(nRow);
  for_inc(r, nRow) cin >> board[r];

  int64 ret = 0, retDup = 0;
  for_inc(loop, 4) {
    //for_inc(r, nRow) cout << board[r] << endl;
    
    fill0(f);

    for_inc(r, nRow) for_inc(c, nCol) side[r][c] = getSide(r, c);

    for_inc_range(c, 1, nCol - 2) {
      if (board[0][c] == '.') {
        f[2][DDOWN][0][c] = 1;
      }
    }

    for_inc(r, nRow) {
      for_dec_range(k, 2, 0) {
        if (k > 0)
          for_inc(c, nCol) {
            if (board[r][c] != '.')
              continue;
            if (side[r][c] != -1)
              continue;
            if (c + 1 < nCol) {
              f[k - 1][DRIGHT][r][c + 1] += f[k][DDOWN][r][c];
            }
          }
        if (k > 0)
          for_dec(c, nCol) {
            if (board[r][c] != '.')
              continue;
            if (side[r][c] != -1)
              continue;
            if (c > 0) {
              f[k - 1][DLEFT][r][c - 1] += f[k][DDOWN][r][c];
            }
          }
        for_inc(c, nCol) {
          if (board[r][c] != '.')
            continue;
          if (side[r][c] != -1)
            continue;
          if (c + 1 < nCol) {
            f[k][DRIGHT][r][c + 1] += f[k][DRIGHT][r][c];
          }
        }
        for_dec(c, nCol) {
          if (board[r][c] != '.')
            continue;
          if (side[r][c] != -1)
            continue;
          if (c > 0) {
            f[k][DLEFT][r][c - 1] += f[k][DLEFT][r][c];
          }
        }
        for_inc(c, nCol) {
          if (board[r][c] != '.')
            continue;
          if (r + 1 < nRow) {
            f[k][DDOWN][r + 1][c] += f[k][DDOWN][r][c];
          }
          if (k > 0) {
            f[k - 1][DDOWN][r + 1][c] += f[k][DRIGHT][r][c];
            f[k - 1][DDOWN][r + 1][c] += f[k][DLEFT][r][c];
          }
        }
      }
    }

    int64 retTopBot = 0;

    for_inc_range(c, 1, nCol - 2) {
      if (board[nRow - 1][c] != '.')
        continue;
      for_inc_range(k, 0, 2) { retTopBot += f[k][DDOWN][nRow - 1][c]; }
    }

    //cout << "Top bot: " << retTopBot << endl;
    retDup += retTopBot;

    int64 retTopLeft = 0;
    for_inc_range(r, 1, nRow - 2) {
      if (board[r][0] != '.')
        continue;
      for_inc_range(k, 0, 2) { retTopLeft += f[k][DLEFT][r][0]; }
    }
    //cout << "Top left: " << retTopLeft << endl;
    retDup += retTopLeft;

    int64 retTopRight = 0;
    for_inc_range(r, 1, nRow - 2) {
      if (board[r][nCol - 1] != '.')
        continue;
      for_inc_range(k, 0, 2) { retTopRight += f[k][DRIGHT][r][nCol - 1]; }
    }
    //cout << "Top right: " << retTopRight << endl;
    retDup += retTopRight;

    int64 retTopTop = 0;
    for_inc_range(r, 1, nRow - 2) {
      for_inc_range(c, 1, nCol - 1) {
        if (board[r][c] != '.')
          continue;
        if (f[2][DDOWN][r][c] == 0)
          continue;
        if (board[r][c - 1] == '.') {
          retTopTop += f[1][DRIGHT][r][c - 1];
        }
      }
    }
    ret += retTopTop;
    //cout << "Top top: " << retTopTop << endl;
    
    rotateBoard();
  }

  cout << ret + retDup / 2 << endl;
  return 0;
}
