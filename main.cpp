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
#define fill0(x) memset(x, 0, sizeof(x))
#define INF_INT 2E9L

#define MAXN 30100
#define MAXK 210

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  cout << 400 << " " << 50 << endl;
  for (int i = 1; i <= 400; ++i) {
    cout << 10000 << " ";
  }
  fclose(stdout);
}

int n, k;
int a[MAXN];
int f[2][2][MAXN][MAXK];

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  
  // Let s1, s2, ..., sk be the sum of k subarrays
  // Relax the problem to optimize
  // g(s) = (qi + pi) * si, such that pi, qi are -1 or 1, and:
  // q1 = 0
  // pk = 0
  // pi = - q(i + 1), for i < k
  // We can easily shown that g(s) is also equal to max |s1 - s2| + ... + |s(k -1) - sk|
  fill0(f);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      for (int p = 0; p < 2; ++p) {
        for (int q = 0; q < 2; ++q) {
          f[p][q][i][j] = -INF_INT;
          if (i < j) continue;
          int qq = j == 1 ? 0 : (2 * q - 1);
          int pp = j == k ? 0 : (2 * p  - 1);
          f[p][q][i][j] = (pp + qq) * a[i] + max(f[p][q][i - 1][j], j > 1 ? max(f[1 - q][0][i - 1][j - 1], f[1 - q][1][i - 1][j - 1]) : 0);
        }
      }
    }
  }
  
  int ret = 0;
  for (int i = 1; i <= n; ++i) {
    for (int p = 0; p < 2; ++p) {
      for (int q = 0; q < 2; ++q) {
        ret = max(ret, f[p][q][i][k]);
      }
    }
  }
  cout << ret << endl;
  
  return 0;
}