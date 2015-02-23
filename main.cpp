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
#include <queue>
#include <stack>
#include <functional>

using namespace std;

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  //freopen("input2.txt", "r", stdin);
  
  int n;
  cin >> n;
  vector<int> a(n + 1);
  int64 sum = 0;
  for_inc_range(i, 1, n) {
    cin >> a[i];
    sum += a[i];
  }
  sort(a.begin() + 1, a.end());
  
  int64 ans = sum;
  for_inc_range(i, 1, n - 1) {
    ans += sum;
    sum -= a[i];
  }
  
  cout << ans << endl;
  
  return 0;
}
