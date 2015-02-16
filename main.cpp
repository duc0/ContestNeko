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

#define MBIT 80

struct binary {
  int digit[MBIT];
  
  int cBit;
  
  binary(int64 x) {
    fill0(digit);
    cBit = 0;
    while (x > 0) {
      digit[cBit] = x % 2;
      cBit++;
      x /= 2;
    }
  }
  
  int popCount() const {
    int c = 0;
    for_inc(i, MBIT) {
      c += (digit[i] == 1);
    }
    return c;
  }
  
  bool operator < (const binary &b) const {
    return isLess(b, MBIT - 1, 0);
  }
  
  bool isLess(const binary &b, int maxPos, int minPos) const {
    for_dec_range(t, maxPos, minPos) {
      if (digit[t] < b.digit[t]) return true;
      if (digit[t] > b.digit[t]) return false;
    }
    return false;
  }
  
  int64 toInt64() {
    int64 r = 0;
    for_dec(i, MBIT) {
      r = r * 2 + digit[i];
    }
    return r;
  }
};



binary bin_best(0);

void updateBest(const binary &b) {
  int p = b.popCount();
  
  int bestCount = bin_best.popCount();
  
  if (p > bestCount) {
    bin_best = b;
  } else if (p == bestCount && b < bin_best) {
    bin_best = b;
  }
}

int64 solve(int64 l, int64 r) {
  binary bin_l(l);
  binary bin_r(r);
  
  bin_best = bin_l;
  updateBest(bin_r);
  
  int c = max(bin_l.cBit, bin_r.cBit);
  
  binary bin(0);
  
  for_dec_range(i, c, 0) {
    if (bin_r.digit[i] == 1) {
      for_dec_range(j, c, i + 1) {
        bin.digit[j] = bin_r.digit[j];
      }
      bin.digit[i] = 0;
      if (bin_l.isLess(bin, c, i)) {
        for_dec_range(j, i - 1, 0) {
          bin.digit[j] = 1;
        }
        updateBest(bin);
      }
    }
    if (bin_l.digit[i] == 0) {
      for_dec_range(j, c, i + 1) {
        bin.digit[j] = bin_l.digit[j];
      }
      bin.digit[i] = 1;
      if (bin.isLess(bin_r, c, i)) {
        for_dec_range(j, i - 1, 0) {
          bin.digit[j] = 1;
        }
        updateBest(bin);
      }
    }
  }
  
  return bin_best.toInt64();
}

int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  int q;
  int64 l, r;
  cin >> q;
  repeat(q) {
    cin >> l >> r;
    cout << solve(l, r) << endl;
  }
  return 0;
}