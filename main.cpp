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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(a, 0, sizeof(a))



void testGen() {
}

#define MAXN 70
int n, need;
int a[MAXN];
int ret[MAXN];

int main() {
  //testGen();
  freopen("input4.txt", "r", stdin);
  
  cin >> n >> need;
  for (int i = 1; i <= n; ++i) {
    a[i] = i;
  }
  int bestS = (n*(n+1)*(n+2)) / 6 ;
  int cnt = 0;
  do {
    int s = 0;
    for (int i = 1; i <= n; ++i) {
      int m = a[i];
      for (int j = i; j <= n; ++j) {
        if (a[j] < m) {
          m = a[j];
        }
        s += m;
      }
    }
    if (s == bestS) {
      cnt++;
      for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
      }
      cout << endl;
    }
  } while (next_permutation(a + 1, a + n + 1));
  
  for (int i = 1; i <= n; ++i) {
    cout << ret[i] << " ";
  }
  cout << cnt << endl;
  return 0;
  
}