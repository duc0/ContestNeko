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

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, q;
  cin >> n >> q;
  
  vector<int> a( n + 1);
  int64 sum = 0;
  
  set<pair<int, int>> s;
  
  for_inc_range(i, 1, n) {
    cin >> a[i];
    
    sum += a[i];
    s.insert(make_pair(a[i], i));
  }
  
  repeat(q) {
    int t;
    cin >> t;
    if (t == 1) {
      int i, x;
      cin >> i >> x;
      if (a[i] != x) {
        sum -= a[i];
        
        s.erase(make_pair(a[i], i));
        
        a[i] = x;
        
        s.insert(make_pair(a[i], i));
        
        sum += x;
      }
      cout << sum << endl;
    } else {
      int p;
      cin >> p;
      
      while (s.rbegin()->first >= p) {
        auto e = *s.rbegin();
        
        sum -= a[e.second];
        a[e.second] = a[e.second] % p;
        sum += a[e.second];
        
        s.erase(e);
        
        s.insert(make_pair(a[e.second], e.second));
      }
      
      cout << sum << endl;
    }
  }
  
  return 0;
}
