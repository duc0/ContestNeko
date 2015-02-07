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
int p[MAXN], n, k;

int countInv[MAXN*(MAXN - 1) / 2], countAll;

int countInversion() {
  int cnt = 0;
  for (int i = 1; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (p[i] > p[j]) {
        cnt++;
      }
    }
  }
  return cnt;
}

void reverse(int l, int r) {
  int mid = (l + r) / 2;
  
  int ii = l, jj = r;
  for (int i = l; i <= mid; ++i) {
    swap(p[ii], p[jj]);
    ii++;
    jj--;
  }
}

void bruteforce(int numOp) {
  if (numOp == 0) {
    int ret = countInversion();
    countInv[ret]++;
    countAll++;
    return;
  }
  for (int l = 1; l <= n; ++l) {
    for (int r = l; r <= n; ++r) {
      reverse(l, r);
      bruteforce(numOp - 1);
      reverse(l, r);
    }
  }
}
int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    cin >> p[i];
  }
  
  countAll = 0;
  fill0(countInv);
  bruteforce(k);
  
  double ret = 0;
  for (int i = 0; i <= n * (n - 1) / 2; ++i) {
    ret += i * ((double)countInv[i] / countAll);
  }
  printf("%.10lf", ret);
  return 0;
}