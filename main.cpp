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

#define count _count
#define MAXN 100100

int n, s, l;
int x;
map<int, int> count;

int f[MAXN], a[MAXN];
set<int> goodPos;

int main() {
  //testGen();
  //freopen("input2.txt", "r", stdin);
  
  scanf("%d%d%d", &n, &s, &l);
  for_inc_range(i, 1, n) {
    scanf("%d", &a[i]);
  }
  
  int leftBound = 1;
  
  goodPos.insert(0);
  f[0] = 0;
  
  fill0(f);
  for_inc_range(i, 1, n) {
    count[a[i]]++;
    
    while (leftBound < i) {
      int smallest = count.begin()->first;
      int largest = count.rbegin()->first;
      if (largest - smallest <= s) {
        break;
      }
      count[a[leftBound]]--;
      if (count[a[leftBound]] == 0) {
        count.erase(a[leftBound]);
      }
      leftBound++;
    }
   
    if (i - leftBound + 1 >= l) {
      auto minPos = goodPos.lower_bound(leftBound - 1);
      if (minPos != goodPos.end()) {
        auto x = *minPos;
        if (i - x >= l) {
          f[i] = f[x] + 1;
          goodPos.insert(i);
        }
      }
    }
  }

  if (f[n] == 0) {
    cout << -1 << endl;
  } else {
    cout << f[n] << endl;
  }
  return 0;
}