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
#define for_dec(i,x) for(auto i=(int)x-1; i >= 0; --i)
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

string s;
int a[MAXN];
int ret[MAXN];
int n, cntSharp;
int sum=0;

int main() {
  //testGen();
  //freopen("input4.txt", "r", stdin);
  
  cin >> s;
  n = (int)s.length();
  cntSharp = 0;
  for_inc(i, n) {
    if (s[i] == '(') {
      a[i] = 1;
    } else if (s[i] == ')') {
      a[i] = -1;
    } else {
      ++cntSharp;
      a[i] = 0;
    }
    sum+=a[i];
  }
  
  bool foundFirst = true;
  for_dec(i, n) {
    if (a[i] == 0) {
      if (foundFirst) {
        ret[i] = sum - (cntSharp - 1);
        foundFirst = false;
      } else {
        ret[i] = 1;
      }
      if (ret[i] <= 0) {
        cout << -1 << endl;
        return 0;
      }
    }
  }
  
  sum = 0;
  for_inc(i, n) {
    if (a[i] == 0) {
      sum -= ret[i];
    } else {
      sum += a[i];
    }
    if (sum < 0) {
      cout << -1 << endl;
      return 0;
    }
  }
  for_inc(i, n) {
    if (a[i] == 0) {
      cout << ret[i] << endl;
    }
  }
  return 0;
}