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
  freopen("biginput2.txt", "w", stdout);
  int n = 10000;
  cout << n << endl;
  repeat(n) {
    cout << rand() % 1000003 - 590000 << " ";
  }
  fclose(stdout);
}

#define MAXN 1000010

int n, a[MAXN];

int64 f[MAXN];

void solve1() {
  f[0] = 0;
  for_inc_range(i, 1, n) {
    int minx = a[i], maxx = a[i];
    for_dec_range(j, i, 1) {
      minx = min(minx, a[j]);
      maxx = max(maxx, a[j]);
      f[i] = max(f[i], f[j - 1] + maxx - minx);
    }
  }
  cout << f[n] << endl;
}

void solve2() {
  f[0] = 0;
  for_inc_range(i, 1, n) {
    f[i] = f[i - 1];
    for_inc_range(j, 1, i) {
      f[i] = max(f[i], f[j - 1] + a[i] - a[j]);
      f[i] = max(f[i], f[j - 1] + a[j] - a[i]);
    }
  }
  
  cout << f[n] << endl;
}

set<int64> max1, max2;

void solve3() {
  f[0] = 0;
  max1.insert(-a[1]);
  max2.insert(a[1]);
  for_inc_range(i, 1, n) {
    f[i] = f[i - 1];
    f[i] = max(f[i], a[i] + *(--max1.end()));
    f[i] = max(f[i], -a[i] + *(--max2.end()));
    if (i < n) {
      max1.insert(f[i] - a[i + 1]);
      max2.insert(f[i] + a[i + 1]);
    }
  }
  
  cout << f[n] << endl;
}


int main() {
  //testGen();
  //freopen("biginput2.txt", "r", stdin);
  
  scanf("%d", &n);
  for_inc_range(i, 1, n) {
    scanf("%d", &a[i]);
  }
  
  //solve1();
  //solve2();
  solve3();
  
  return 0;
}