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
#include <sstream>

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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int nCol, nRow;
  cin >> nCol >> nRow;
  Board b;
  b.init(nRow);
  for_inc(r, nRow) {
    string s;
    cin >> s;
    b.setRow(r, s);
  }
  
  b.rotateRight();
  b.flipHorizontally();
  b.zoom(2);
  
  for_inc(r, b.numRow()) {
    cout << b[r] << endl;
  }
  
  return 0;
}
