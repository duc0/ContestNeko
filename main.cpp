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
#define fillneg(x) memset(x, -1, sizeof(x))

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  cout << 100 << " " << 100000 << endl;
  for (int i = 1; i <= 100; ++i) {
    cout << i << " ";
  }
  fclose(stdout);
}

#define MAXN 102
int p[MAXN], n, k, pos[MAXN];
int totalOps;

double pr[MAXN][MAXN], npr[MAXN][MAXN]; // pr[i][j] = prob that p[i] > p[j] after k operations, i < j

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

int countOpNotAffect[MAXN][MAXN];

int nextState[MAXN][MAXN][3*MAXN*3][3];
int countState[MAXN][MAXN];

void addNextState(int i, int j, int i2, int j2, int cnt) {
  nextState[i][j][countState[i][j]][0] = i2;
  nextState[i][j][countState[i][j]][1] = j2;
  nextState[i][j][countState[i][j]][2] = cnt;
  countState[i][j]++;
}
int main() {
  //testGen()
  freopen("biginput1.txt", "r", stdin);
  
  cin >> n >> k;
  if (k > 1000) {
    k = 1000;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
    pos[p[i]] = i;
  }
  totalOps = n * (n + 1) / 2;
  
  double probOp = (double)1 / totalOps;
  
  fill0(pr);
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      pr[i][j] = p[i] > p[j] ? 1 : 0;
      
      countOpNotAffect[i][j] = (i-1) * i / 2 + (n - j) * (n - j + 1) / 2 + (j - i - 1) * (j - i) / 2;
    }
  }
  
  fill0(countState);
  
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      for (int i2 = 1; i2 < j; ++i2) {
        int cnt = countOpSwap1(i, j, i2);
        if (cnt > 0) {
          addNextState(i, j, i2, j, cnt);
        }
      }
      for (int j2 = i + 1; j2 <= n; ++j2) {
        int cnt = countOpSwap2(i, j, j2);
        if (cnt > 0) {
          addNextState(i, j, i, j2, cnt);
        }
      }
      if (countOpNotAffect[i][j] > 0) {
        addNextState(i, j, i, j, countOpNotAffect[i][j]);
      }
      for (int j2 = 1, i2 = j2 + j - i; j2 <= n && i2 <= n; ++j2, ++i2) {
        int sum_r_l = j2 + j;
        int cnt = countOp(sum_r_l, i, j);
        if (cnt > 0) {
          addNextState(i, j, j2, i2, -cnt);
        }
      }

    }
  }
  repeat(k) {
    fill0(npr);
    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        double curp = pr[i][j];
        double curp1 = 1 - curp;
        double ret;
        auto ns = nextState[i][j];
        int cs = countState[i][j];
        int i2, j2, cnt;
        for (int id = 0; id < cs; ++id) {
          i2 = ns[id][0];
          j2 = ns[id][1];
          cnt = ns[id][2];
          if (cnt > 0) {
            ret = curp * cnt;
          } else {
            ret = -curp1 * cnt;
          }
          npr[i2][j2] += ret;
        }
      }
    }
    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        npr[i][j] *= probOp;
        pr[i][j] = npr[i][j];
      }
    }
  }
  
  double ret = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      ret += pr[i][j];
    }
  }
  printf("%.10lf", ret);
  return 0;
}