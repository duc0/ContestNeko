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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 110
int p[MAXN], n, k, pos[MAXN];
int totalOps;

double pr[2][MAXN][MAXN]; // pr[i][j] = prob that p[i] = x and p[j] = y after k operations

int getPos(int i, int l, int r) { // get pos of p[i] after reverse(l, r)
  if (i < l || i > r) {
    return i;
  }
  return r - i + l;
}
int main() {
  //testGen();
  freopen("input2.txt", "r", stdin);
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    pos[p[i]] = i;
  }
  totalOps = n * (n + 1) / 2;
  double probOp = (double) 1 / totalOps;
  
  double ret = 0;
  
  for (int x = 1; x < n; ++x) {
    for (int y = x + 1; y <= n; ++y) {
      fill0(pr);
      int cur = 0, next = 1;
      pr[cur][pos[x]][pos[y]] = 1;
      repeat(k) {
        fill0(pr[next]);
        for (int i = 1; i <= n; ++i) {
          for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (pr[cur][i][j] == 0) continue;
            for (int l = 1; l <= n; ++l) {
              for (int r = l; r <= n; ++r) {
                int i2 = getPos(i, l, r);
                int j2 = getPos(j, l, r);
                pr[next][i2][j2] += pr[cur][i][j] * probOp;
              }
            }
          }
        }
        cur = 1 - cur;
        next = 1 -  next;
      }
      for (int py = 1; py < n; ++py) {
        for (int px = py + 1; px <= n; ++px) {
          ret += pr[cur][px][py];
        }
      }
    }
  }
  
  printf("%.10lf", ret);
  return 0;
}