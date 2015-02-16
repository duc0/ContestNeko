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
#define INT_INF 1E9L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

bool win(int h1, int a1, int d1, int h2, int a2, int d2) {
  int f1 = max(0, a1 - d2);
  int f2 = max(a2 - d1, 0);
  if (f1 == 0) {
    return false;
  }
  if (f2 == 0) {
    return true;
  }
  int t1 = h1 / f2;
  if (h1 % f2 > 0) t1++;
  int t2 = h2 / f1;
  if (h2 % f1 > 0) t2++;
  return t1 > t2;
}

int h1, a1, d1, h2, a2, d2, ph, pa, pd;

void tryBuy(int money, int &x, int &y, int &z, int &px, int &py, int &pz) {
  x += money / px;
  money %= px;
  y += money / py;
  money %= py;
  z += money / pz;
  money %= pz;
}

#define buy(x,y,z) tryBuy(money, x, y, z, p##x, p##y, p##z)

bool ok(int oMoney) {
  int money;
  int h, a, d;
  
  money = oMoney; h = h1; a = a1; d = d1;
  buy(h,a,d);
  if (win(h, a, d, h2, a2, d2)) return true;
  
  money = oMoney; h = h1; a = a1; d = d1;
  buy(h, d, a);
  if (win(h, a, d, h2, a2, d2)) return true;

  money = oMoney; h = h1; a = a1; d = d1;
  buy(a, h, d);
  if (win(h, a, d, h2, a2, d2)) return true;

  money = oMoney; h = h1; a = a1; d = d1;
  buy(a, d, h);
  if (win(h, a, d, h2, a2, d2)) return true;

  money = oMoney; h = h1; a = a1; d = d1;
  buy(d, a, h);
  if (win(h, a, d, h2, a2, d2)) return true;

  money = oMoney; h = h1; a = a1; d = d1;
  buy(d, h, a);
  if (win(h, a, d, h2, a2, d2)) return true;
  
  return false;
}

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  
  cin >> h1 >> a1 >> d1;
  cin >> h2 >> a2 >> d2;
  cin >> ph >> pa >> pd;
  
  int left = 0, right = INT_INF, mid, ret = 0;
  
  while (left <= right) {
    mid = (left + right) / 2;
    if (ok(mid)) {
      ret = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  
  cout << ret << endl;
  
  return 0;
}