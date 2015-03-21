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

string op(int a, int b, int c, char op) {
  ostringstream ss;
  ss << a << " " << op << " " << b << " = " << c;
  return ss.str();
}

void solve4() {
  cout << op(1, 2, 2 , '*') << endl;
  cout << op(2, 3, 6 , '*') << endl;
  cout << op(6, 4, 24 , '*') << endl;
}

void solve5() {
  cout << op(3, 4, 7 , '+') << endl;
  cout << op(7, 5, 12 , '+') << endl;
  cout << op(12, 2, 24 , '*') << endl;
  cout << op(24, 1, 24 , '*') << endl;
}


int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;

  if (n < 4) {
    cout << "NO";
  } else {
    cout << "YES" << endl;
    if (n == 4) {
      solve4();
    } else if (n == 5) {
      solve5();
    } else {
      if (n % 2 == 0) {
        solve4();
        for (int i = 5; i <= n; i += 2) {
          cout << op(i + 1, i, 1, '-') << endl;
          cout << op(24, 1, 24, '*') << endl;
        }
      } else {
        solve5();
        for (int i = 6; i <= n; i += 2) {
          cout << op(i + 1, i, 1, '-') << endl;
          cout << op(24, 1, 24, '*') << endl;
        }
      }
    }
  }
  
  return 0;
}
