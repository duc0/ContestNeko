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

double pr[2][MAXN][MAXN]; // pr[i][j] = prob that p[i] > p[j] after k operations, i < j

int main() {
  //testGen();
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
  int cur = 0, next = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      pr[cur][i][j] = p[i] > p[j] ? 1 : 0;
    }
  }
  repeat(k) {
    fill0(pr[next]);
    auto prn = pr[next];
    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        double prc = pr[cur][i][j];
        
        int dist = j - i;
        int right = n - j + 1;
        for (int i2 = 1; i2 <= i; ++i2) {
          prn[i2][j] += prc * min(i2, dist);
        }
        
        for (int i2 = i + 1; i2 < j; ++i2) {
          prn[i2][j] += prc * min(i, j - i2);
        }
        
        for (int j2 = i + 1; j2 <= j; ++j2) {
          prn[i][j2] += prc * min(j2 - i, right);
        }
        
        for (int j2 = j + 1; j2 <= n; ++j2) {
          prn[i][j2] += prc * min(dist, n - j2 + 1);
        }
        
        prn[i][j] += ((i-1) * i / 2 + (n - j) * (n - j + 1) / 2 + (j - i - 1) * (j - i) / 2) * prc;
        for (int j2 = 1; j2 < i; ++j2) {
          prn[j2][j2 + dist] += (1 - prc) * min(j2, right);
        }
        for (int j2 = i; j2 <= n + i - j; ++j2) {
          prn[j2][j2 + dist] += (1 - prc) * min(i, right - j2 + i);
        }
      }
    }
    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j <= n; ++j) {
        pr[next][i][j] *= probOp;
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