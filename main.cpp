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

#define MOD 1000000007
int MODP(int a) {
  int r = a % MOD;
  if (r < 0) r += MOD;
  return r;
}

#define MAXN 5100

int n, a, b, k;
int f[MAXN][MAXN];
int s[MAXN][MAXN];

int getSum(int d, int i, int j) {
  return MODP(s[d][j] - s[d][i - 1]);
}

int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  cin >> n >> a >> b >> k;
  fill0(f);
  fill0(s);
  
  f[0][a] = 1;

  s[0][0] = 0;
  for_inc_range(i, 1, n) {
    s[0][i] = MODP(s[0][i - 1] + f[0][i]);
  }
  
  for_inc_range(d, 1, k) {
    s[d][0] = 0;
    for_inc_range(i, 1, n) {
      if (i == b) continue;
      if (i > b) {
        f[d][i] = MODP(getSum(d - 1, (i + b) / 2 + 1, n) - f[d - 1][i]);
      } else {
        int r = (i + b) / 2;
        if ((i + b) % 2 == 0) r--;
        f[d][i] = MODP(getSum(d - 1, 1, r) - f[d - 1][i]);
      }
      
      s[d][i] = MODP(s[d][i - 1] + f[d][i]);
    }
  }
  
  int ret = 0;
  for_inc_range(i, 1, n) {
    ret = MODP(ret + f[k][i]);
  }
  cout << ret << endl;
  return 0;
}