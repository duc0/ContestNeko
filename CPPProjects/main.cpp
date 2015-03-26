#define LOGLEVEL 0
#define NDEBUG
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
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cfloat>
#include <random>

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

class SuccessiveSubtraction2 {
public:
  vector <int> calc( vector <int> ar, vector <int> p, vector <int> v ) {
    int n = (int) ar.size();
    
    int nChange = (int) p.size();
    vector<int> ret;
    
    for (int t = 0; t < nChange; ++t) {
      ar[p[t]] = v[t];
      
      vector<int> a(n);
      a[0] = ar[0];
      for (int i = 1; i < n; ++i) {
        a[i] = -ar[i];
      }
      
      int sum = 0;
      for (int i = 0; i < n; ++i) {
        sum = sum + a[i];
      }
      
      if (n <= 2) {
        ret.push_back(sum);
        continue;
      }
      
      //LOG(1, sum);
      
      vector<vector<int>> f(3, vector<int>(n));
      vector<vector<int>> g(3, vector<int>(n));
      
      for (int k = 1; k <= 2; ++k) {
        f[k][1] = 0;
        g[k][1] = 0;
        for (int i = 2; i < n; ++i) {
          f[k][i] = a[i] + f[k][i - 1];
          if (k == 2) {
            f[k][i] = min(f[k][i], a[i] + g[k - 1][i - 1]);
          }
          g[k][i] = min(g[k][i - 1], f[k][i]);
          //LOG(1, i << " " << k << " " << f[k][i]);
        }
      }
      
      int ans = 0;
      ans = min(ans, g[1][n - 1]);
      ans = min(ans, g[2][n - 1]);
      
      ret.push_back(sum - 2 * ans);
    }
              
    return ret;
  }
};
