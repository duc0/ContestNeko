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

double pr[2][MAXN][MAXN]; // pr[i][j] = prob that p[i] > p[j] after k operations, i < j

int getPos(int i, int l, int r) { // get pos of p[i] after reverse(l, r)
  if (i < l || i > r) {
    return i;
  }
  return r - i + l;
}

int main() {
  //testGen();
  //freopen("input2.txt", "r", stdin);
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    pos[p[i]] = i;
  }
  totalOps = n * (n + 1) / 2;
  double probOp = (double) 1 / totalOps;
  
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
        for (int l = 1; l <= n; ++l) {
          for (int r = l; r <= n; ++r) {
            int i2 = getPos(i, l, r);
            int j2 = getPos(j, l, r);
            if (i2 < j2) {
              pr[next][i2][j2] += pr[cur][i][j] * probOp;
            } else {
              pr[next][j2][i2] += (1 - pr[cur][i][j]) * probOp;
            }
          }
        }
      }
    }
    cur = 1 - cur;
    next = 1 - next;
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