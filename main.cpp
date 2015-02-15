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
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
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

int a[MAXN], n;

int maxEdge;
int maxMid;

// Let [left, right] be the current interval in question
// Let [symLeft, symRight] be the reflected interval of [left, right]
// We define cntDiff to be the count profile of [left, right] minus
// the count profile of [symLeft, symRight] plus the count profile of
// their intersection.
// cntDiff can be used to quickly test if [left, right] is good:
// if cntDiff has a negative count, we know for sure that [left, right]
// is bad.
int cntDiff[MAXN];

#define left _left
#define right _right
int left, right, symLeft, symRight;
int countNeg = 0;

bool bad() {
  if (left > right) {
    return true;
  }
  if (countNeg > 0) {
    return true;
  }
  if (left > maxEdge && right < n - maxEdge + 1) {
    return true;
  }
  if (right < symLeft) {
    if (right < maxMid) {
      return true;
    }
  }
  if (symRight < left) {
    if (symRight < maxMid) {
      return true;
    }
  }
  return false;
}

void incDiff(int x) {
  cntDiff[x]++;
  if (cntDiff[x] == 0) {
    countNeg--;
  }
}

void decDiff(int x) {
  cntDiff[x]--;
  if (cntDiff[x] == -1) {
    countNeg++;
  }
}

void incLeft() {
  decDiff(a[left]);
  incDiff(a[symRight]);
  if (symLeft <= left && left <= symRight) {
    decDiff(a[left]);
  }
  if (left != symRight && left <= symRight && symRight <= right) {
    decDiff(a[symRight]);
  }
  left++;
  symRight--;
}

void decLeft() {
  left--;
  symRight++;
  incDiff(a[left]);
  decDiff(a[symRight]);
  if (symLeft <= left && left <= symRight) {
    incDiff(a[left]);
  }
  if (left != symRight && left <= symRight && symRight <= right) {
    incDiff(a[symRight]);
  }
}

void decRight() {
  decDiff(a[right]);
  incDiff(a[symLeft]);
  if (symLeft <= right && right <= symRight) {
    decDiff(a[right]);
  }
  if (right != symLeft && left <= symLeft && symLeft <= right) {
    decDiff(a[symLeft]);
  }
  right--;
  symLeft++;
}

int main() {
  //testGen();
  //freopen("input5.txt", "r", stdin);
  
  fill0(cntDiff);
  
  scanf("%d", &n);
  for_inc_range(i, 1, n) {
    scanf("%d", &a[i]);
    cntDiff[a[i]]++;
  }
  
  for (maxEdge = 1; maxEdge <= n && a[maxEdge] == a[n - maxEdge + 1]; maxEdge++);
  
  for (maxMid = n / 2; maxMid >= 1 && a[maxMid] == a[n - maxMid + 1]; maxMid--);
  
  int cntOdd = 0;
  for_inc_range(x, 1, n) cntOdd += cntDiff[x] % 2;
  if (cntOdd > 1) {
    cout << 0 << endl;
    return 0;
  }
  
  left = 1;
  right = n;
  symLeft = 1;
  symRight = n;
  while (1) {
    incLeft();
    if (bad()) {
      decLeft();
      break;
    }
  }
  
  int64 ret = left;
  // O(N)
  while (1) {
    decRight();
    if (right == 0) break;
    
    while (bad() && left > 1) {
      decLeft();
    }
    if (bad()) break;
    ret += left;
  }
  
  cout << ret << endl;
  
  return 0;
}