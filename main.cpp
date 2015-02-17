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

#define MAXN 100100

int n, q;

int64 h[MAXN];
int64 d[MAXN];

int main() {
  //testGen();
  freopen("input1.txt", "r", stdin);
  
  cin >> n >> q;
  for_inc_range(i, 1, n) {
    cin >> d[i];
  }
  for_inc_range(i, 1, n) {
    cin >> h[i];
  }
  
  for_inc_range(i, n + 1, 2 * n) {
    d[i] = d[i - n];
    h[i] = h[i - n];
  }
  
  n = n * 2;
  d[0] = 0;
  for_inc_range(i, 1, n) {
    d[i] = d[i - 1] + d[i];
  }
  
  
  return 0;
}