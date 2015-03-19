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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAX 1000100

char a[MAX];
int f[MAX], g[MAX];
int ff[2][MAX];
int f2[MAX], g2[MAX], ff2[2][MAX], gg2[2][MAX];
int prevB[MAX], prevW[MAX];
int total;

inline char getA(int i) {
  if (i == 0) return 'X';
  return a[i - 1];
}

inline int getG(int i) {
  if (i <= 0) return 1;
  return g[i];
}

inline int getG2(int i) {
  if (i <= 0) return 0;
  return g2[i];
}


int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  int n, k;
  scanf("%d%d", &n, &k);
  scanf("%s", a);
  
  total = 1;
  
  prevB[0] = 0;
  prevW[0] = 0;
  for_inc_range(i, 1, n) {
    if (getA(i) == 'B') {
      prevB[i] = i;
    } else {
      prevB[i] = prevB[i - 1];
    }
    
    if (getA(i) == 'W') {
      prevW[i] = i;
    } else {
      prevW[i] = prevW[i - 1];
    }
  }
  
  f[0] = 0;
  g[0] = 1;
  
  for_inc_range(i, 1, n) {
    char c = getA(i);
    
    if (c == 'X') {
      total = (total * 2) % MOD;
    }
    
    if (c != 'X') {
      f[i] = f[i - 1];
      
      if (c == 'B' && prevW[i] < i - k + 1 && i - k + 1>= 1 && getA(i - k) != 'B') {
        f[i] = (f[i] + getG(i - k - 1)) % MOD;
      }
      
      if (c == 'W') {
        ff[0][i] = f[i];
        ff[1][i] = 0;
      } else {
        ff[0][i] = 0;
        ff[1][i] = f[i];
      }
    } else {
      if (prevW[i] < i - k + 1 && i - k + 1 >= 1 && getA(i - k) != 'B') {
        f[i] = getG(i - k - 1);
      }
      ff[0][i] = f[i - 1];
      ff[1][i] = (f[i] + f[i - 1]) % MOD;
      f[i] = (f[i] + MODP(f[i - 1] * 2)) % MOD;
    }
    
    g[i] = MODP(total - f[i]);
  }
  
  LOG(1, f[n]);
  LOG(1, ff[0][n]);
  LOG(1, ff[1][n]);
  
  f2[0] = 0;
  g2[0] = 0;
  
  
  for_inc_range(i, 1, n) {
    char c = getA(i);
    
    if (c != 'X') {
      f2[i] = f2[i - 1];
      if (c == 'W' && prevB[i] < i - k + 1 && i - k + 1 >= 1 && getA(i - k) != 'W') {
        f2[i] = (f2[i] + gg2[1][i - k]) % MOD;
      }
      
      if (c == 'W') {
        ff2[0][i] = f2[i];
        ff2[1][i] = 0;
      } else {
        ff2[0][i] = 0;
        ff2[1][i] = f2[i];
      }
    } else {
      if (prevB[i] < i - k + 1 && i - k + 1 >= 1 && getA(i - k) != 'W') {
        f2[i] = gg2[1][i - k];
      }
      
      ff2[1][i] = f2[i - 1];
      ff2[0][i] = MODP(f2[i] + f2[i - 1]);
      f2[i] = MODP(f2[i] + MODP(f2[i - 1] * 2));
    }
    
    g2[i] = MODP(f[i] - f2[i]);
    gg2[0][i] = MODP(ff[0][i] - ff2[0][i]);
    gg2[1][i] = MODP(ff[1][i] - ff2[1][i]);
    LOG(1, "F " << i << " " << f[i]);
    LOG(1, "F2 " << i << " " << f2[i]);
    LOG(1, "G2 " << i << " " << g2[i]);
  }
  
  cout << f2[n] << endl;
  return 0;
}
