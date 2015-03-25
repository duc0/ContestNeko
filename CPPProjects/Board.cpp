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
#define INT_INF 2E9L
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

class Board {
  int nRow, nCol;
  vector<string> a;
public:
  void init(int nRow) {
    this->nRow = nRow;
    a.resize(nRow);
  }
  void setRow(int r, string s) {
    a[r] = s;
    nCol = (int)s.length();
  }
  
  int numRow() const {return nRow;}
  int numCol() const {return nCol;}
  bool isCorner(int r, int c) const {
    return (r == 0 && c == 0) || (r == 0 && c == lastCol()) || (r == lastRow() && c == 0) || (r == lastRow() && c == lastCol());
  }
  bool isOnSide(int r, int c) const {
    return (r == 0 || c == 0 || r == lastRow() || c == lastCol());
  }
  int lastCol() const {return nCol - 1;}
  int lastRow() const {return nRow - 1;}
  
  void rotateRight() {
    vector<string> boardRotate;
    boardRotate.resize(nCol);
    for_inc(c, nCol) boardRotate[c].resize(nRow);
    for_inc(r, nRow) {
      for_inc(c, nCol) {
        boardRotate[c][nRow - 1 - r] = a[r][c];
      }
    }
    swap(nRow, nCol);
    a = boardRotate;
  }
  
  void flipHorizontally() {
    vector<string> boardFlip;
    boardFlip.resize(nRow);
    for_inc(r, nRow) boardFlip[r].resize(nCol);
    for_inc(r, nRow) {
      for_inc(c, nCol) {
        boardFlip[r][c] = a[r][nCol - c - 1];
      }
    }
    a = boardFlip;
  }
  
  void zoom(int scale) {
    assert(scale > 0);
    if (scale == 1) return;
    vector<string> boardZoom;
    boardZoom.resize(nRow * scale);
    for_inc(r, nRow * scale) boardZoom[r].resize(nCol * scale);
    for_inc(r, nRow * scale) {
      for_inc(c, nCol * scale) {
        boardZoom[r][c] = a[r / scale][c / scale];
      }
    }
    a = boardZoom;
    nRow *= scale;
    nCol *= scale;
  }
  
  const string& operator[](int r) const {
    return a[r];
  }
};

Board board;

bool isSide(const Board &board, int r, int c) {
  return board.isOnSide(r, c) && !board.isCorner(r, c);
}

// Sample: CF 293, div 2, problem F

#define DDOWN 0
#define DLEFT 1
#define DRIGHT 2
#define MAXN 2020
int64 f[3][3][MAXN][MAXN];
bool good[MAXN][MAXN];

int main() {
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  int nRow, nCol;
  cin >> nRow >> nCol;
  board.init(nRow);
  for_inc(r, nRow) {
    string s;
    cin >> s;
    board.setRow(r, s);
  }
  
  int64 ret = 0, retDup = 0;
  for_inc(loop, 4) {
    for_inc(r, nRow) LOG(1, board[r]);
    
    fill0(f);
    
    for_inc(r, nRow) for_inc(c, nCol) good[r][c] = !isSide(board, r, c) && board[r][c] == '.';
    
    for_inc_range(c, 1, nCol - 2) {
      if (board[0][c] == '.') {
        f[2][DDOWN][0][c] = 1;
      }
    }
    
    for_inc(r, nRow) {
      for_dec_range(k, 2, 0) {
        if (k > 0)
          for_inc(c, nCol) {
            if (!good[r][c])
              continue;
            if (c + 1 < nCol) {
              f[k - 1][DRIGHT][r][c + 1] += f[k][DDOWN][r][c];
            }
          }
        if (k > 0)
          for_dec(c, nCol) {
            if (!good[r][c])
              continue;
            if (c > 0) {
              f[k - 1][DLEFT][r][c - 1] += f[k][DDOWN][r][c];
            }
          }
        for_inc(c, nCol) {
          if (!good[r][c])
            continue;
          if (c + 1 < nCol) {
            f[k][DRIGHT][r][c + 1] += f[k][DRIGHT][r][c];
          }
        }
        for_dec(c, nCol) {
          if (!good[r][c])
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
    
    LOG(1, "Top bot: " << retTopBot);
    retDup += retTopBot;
    
    int64 retTopLeft = 0;
    for_inc_range(r, 1, nRow - 2) {
      if (board[r][0] != '.')
        continue;
      for_inc_range(k, 0, 2) { retTopLeft += f[k][DLEFT][r][0]; }
    }
    LOG(1, "Top left: " << retTopLeft);
    retDup += retTopLeft;
    
    int64 retTopRight = 0;
    for_inc_range(r, 1, nRow - 2) {
      if (board[r][nCol - 1] != '.')
        continue;
      for_inc_range(k, 0, 2) { retTopRight += f[k][DRIGHT][r][nCol - 1]; }
    }
    LOG(1, "Top right: " << retTopRight);
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
    LOG(1, "Top top: " << retTopTop);
    
    board.rotateRight();
    nRow = board.numRow();
    nCol = board.numCol();
  }
  
  cout << ret + retDup / 2 << endl;
  return 0;
}