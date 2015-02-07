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

#define MAXN 500
#define MAXK 60

int n, k;
int a[MAXN];
int f[MAXN][MAXN][MAXK];
int sumPart[MAXN];

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  cout << 400 << " " << 50 << endl;
  for (int i = 1; i <= 400; ++i) {
    cout << 10000 << " ";
  }
  fclose(stdout);
}

int getSum(int l, int r) {
  return sumPart[r] - sumPart[l - 1];
}

int main() {
  //testGen();
  //freopen("biginput1.txt", "r", stdin);
  
  cin >> n >> k;
  sumPart[0] = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sumPart[i] = a[i] + sumPart[i - 1];
  }
  
  fill0(f);
  for (int last = 1; last <= n; ++last) {
    for (int prev = 1; prev <= last; ++prev) {
      for (int numSeq = 1; numSeq <= k; ++numSeq) {
        if (numSeq > last) {
          continue;
        }
        if (numSeq - 1 > prev - 1) {
          continue;
        }
        int sumCur = getSum(prev, last);
        if (numSeq == 1) {
          f[last][prev][numSeq] = 0;
          continue;
        }
        int best = 0;
        for (int before = 1; before < prev; ++before) {
          int sumPrev = getSum(before, prev - 1);
          if (numSeq - 2 > before - 1) {
            continue;
          }
          int cand = abs(sumCur - sumPrev) + f[prev - 1][before][numSeq - 1];
          if (cand > best) {
            best = cand;
          }
        }
        f[last][prev][numSeq] = best;
      }
    }
  }
  
  int best = 0;
  for (int i = 1; i <= n; ++i) {
    for (int prev = 1; prev <= n; ++prev) {
      if (k <= i && f[i][prev][k] > best) {
        best = f[i][prev][k];
      }
    }
  }
  cout << best << endl;
  return 0;
}