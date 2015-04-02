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
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cfloat>
#include <random>
#include <bitset>

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

// 0-based
template<size_t NCOL> class GF2Matrix {
  vector<bitset<NCOL>> row;
  int nRow;
  vector<int> order;
  vector<size_t> length;
  bool isLock;
  
public:
  void init(int nRow) {
    this->nRow = nRow;
    row.resize(nRow);
    order.resize(nRow);
    for_inc(r, nRow) {
      order[r] = r;
    }
    length.resize(nRow);
    isLock = false;
  }
  
  void setRow(int r, const bitset<NCOL> &rV) {
    row[r] = rV;
  }
  
  void lock() {
    isLock = true;
    for_inc(r, nRow) {
      for_dec(c, NCOL) {
        if (row[r].test(c)) {
          length[r] = c;
          break;
        }
      }
    }
  }
  
  // O(NROW log NROW + NROW * NCOL)
  void gaussianElimination() {
    assert(isLock);
    sort(order.begin(), order.end(), [&](int r1, int r2) {return length[r1] > length[r2];});
    for (int c = NCOL - 1, r = 0; c >=0; c--) {
      int i = r;
      while (i < nRow && !getRow(i).test(c)) {
        ++i;
      }
      if (i >= nRow) {
        continue;
      }
      swap(order[r], order[i]);
      for_inc_range(j, r + 1, nRow - 1) {
        if (getRow(j).test(c)) {
          row[order[j]] ^= getRow(r);
        }
      }
      r++;
    }
  }
  
  inline const bitset<NCOL> & getRow(int r) const {
    return row[order[r]];
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int nTest;
  cin >> nTest;
  while (nTest --) {
  int n, k;
  cin >> n >> k;
  GF2Matrix<64> a;
  a.init(n);
  for_inc(r, n) {
    int64 x;
    cin >> x;
    a.setRow(r, x);
  }
  
  a.lock();
  a.gaussianElimination();
  
  int64 ret = k;
  for_inc(r, n) {
    int64 val = a.getRow(r).to_ullong();
    if ((val ^ ret) > ret) {
      ret ^= val;
    }
  }
  cout << ret << endl;
  }
  return 0;
}
