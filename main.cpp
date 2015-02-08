#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 110
int p[MAXN], n, k, pos[MAXN];
int totalOps;

double pr[2][MAXN][MAXN]; // pr[i][j] = prob that p[i] > p[j] after k operations, i < j

int getPos(int i, int l, int r) { // get pos of p[i] after reverse(l, r)
  if (i < l || i > r) {
    return i;
  }
  return r - i + l;
}

int countOp(int s, int i, int j) {
  // count number of reverse ops (l, r) such that l + r = s , l <= i, r >= j
  int l = i, r = s-l;
  if (!(r >= j && r <= n)) {
    r = j;
    l = s - r;
    if (!(l <= i && l >= 1)) {
      return 0;
    }
  }
  return min(l, n - r + 1);;
}

int countOpSwap1(int i, int j, int i2) {
  // count number of reverse ops (l, r) such that i and i2 are swapped, but j stay the same
  if (i > i2) {
    return countOpSwap1(i2, j, i);
  }
  return min(i, j - i2);
}

int countOpSwap2(int i, int j, int j2) {
  if (j2 > j) {
    return countOpSwap2(i, j2, j);
  }
  return min(j2 - i, n - j + 1);
}

int main() {
  //testGen();
  freopen("input3.txt", "r", stdin);
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    pos[p[i]] = i;
  }
  totalOps = n * (n + 1) / 2;
  
  fill0(pr);
  int cur = 0, next = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      pr[cur][i][j] = p[i] > p[j] ? 1 : 0;
    }
  }
  
  repeat(k) {
    fill0(pr[next]);
    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        for (int i2 = 1; i2 < j; ++i2) {
          int cnt = countOpSwap1(i, j, i2);
          //cout << i << " " << j << " " << i2 << " " << cnt << endl;
          pr[next][i2][j] += pr[cur][i][j] * ((double) cnt / totalOps);
        }
        for (int j2 = i + 1; j2 <= n; ++j2) {
          int cnt = countOpSwap2(i, j, j2);
          //cout << i << " " << j << " " << j2 << " " << cnt << endl;
          pr[next][i][j2] += pr[cur][i][j] * ((double) cnt / totalOps);
        }
        pr[next][i][j] += ((double)(i-1) * i / 2 + (n - j) * (n - j + 1) / 2 + (j - i - 1) * (j - i) / 2)  * pr[cur][i][j] / totalOps;
        for (int j2 = 1; j2 <= n; ++j2) {
          int i2 = j2 + (j - i);
          if (i2 > n) break;
          int sum_r_l = j2 + j;
          int cnt = countOp(sum_r_l, i, j);
          assert(j2 < i2);
          //cout << i << " " << j << " " << i2 << " " << j2 << endl;
          //cout << sum_r_l << " " << i << " " << j << " " << cnt << endl;
          pr[next][j2][i2] += (1 - pr[cur][i][j]) * ((double) cnt/ totalOps);
        }
      }
    }
    cur = 1 - cur;
    next = 1 - next;
    //cout << pr[cur][1][2] <<  " " << pr[cur][2][3] << " " << pr[cur][1][3] << endl;
  }
  
  double ret = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      ret += pr[cur][i][j];
    }
  }
  printf("%.10lf", ret);
  return 0;
}