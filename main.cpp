//#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
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
#include <stack>
#include <functional>
#include <sstream>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 200200


set<int> xcut, ycut;
map<int, int> ycutsize, xcutsize;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  
  int w, h, n;
  scanf("%d%d%d", &w, &h, &n);

  ycutsize[h] = 1;
  xcutsize[w] = 1;
  
  xcut.insert(0);
  xcut.insert(w);
  ycut.insert(0);
  ycut.insert(h);
  
  char typ[5];
  
  for_inc(i, n) {
    int v;
    scanf("%s %d", typ, &v);
    
    if (typ[0] == 'H') {
      auto it = ycut.lower_bound(v);
      
      int cR = *it;
      int cL = *(--it);
      
      ycutsize[cR - cL]--;
      if (ycutsize[cR - cL] == 0) {
        ycutsize.erase(cR - cL);
      }
      ycutsize[v - cL]++;
      ycutsize[cR - v]++;
      
      ycut.insert(v);
    } else {
      auto it = xcut.lower_bound(v);
      
      int cR = *it;
      int cL = *(--it);
      
      xcutsize[cR - cL]--;
      if (xcutsize[cR - cL] == 0) {
        xcutsize.erase(cR - cL);
      }
      xcutsize[v - cL]++;
      xcutsize[cR - v]++;
      
      xcut.insert(v);
    }
    
    //LOG(1, ycutsize.rbegin()->first << " " << xcutsize.rbegin()->first);
    int64 ret = ((int64)ycutsize.rbegin()->first) * (xcutsize.rbegin()->first);
    cout << ret << endl;
  }
  
  return 0;
}
