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
int a[MAXN];

set<int> s;

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  int n, l, x, y;
  cin >> n >> l >> x >> y;
  for_inc_range(i, 1, n) {
    cin >> a[i];
    s.insert(a[i]);
  }
  
  bool covx = false, covy = false;
  for_inc_range(i, 1, n) {
    if (!covx) covx = s.count(a[i] - x) || s.count(a[i] + x);
    if (!covy) covy = s.count(a[i] - y) || s.count(a[i] + y);
  }
  
  if (covx && covy) {
    cout << 0 << endl;
    return 0;
  }
  if (covx) {
    cout << 1 << endl;
    cout << y << endl;
    return 0;
  }
  if (covy) {
    cout << 1 << endl;
    cout << x << endl;
    return 0;
  }
  
  for_inc_range(i, 1, n) {
    int c;
    for (int kind = 0; kind < 2; ++kind) {
      c = kind == 0 ? (a[i] - x) : (x + a[i]);
      if (0 <= c && c <= l) {
        if (s.count(y + c) || s.count(c - y)) {
          cout << 1 << endl;
          cout << c << endl;
          return 0;
        }
      }
    }
  }
  
  cout << 2 << endl;
  cout << x << " " << y << endl;
  
  return 0;
}