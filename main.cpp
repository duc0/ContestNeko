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
#define fill0(x) memset(a, 0, sizeof(a))




#define MAXN 400

#define MOD 1000000007
#define MAXT 101000

int n, q, t;
int a[MAXN];
int more[MAXN];
int mless[MAXN];

int f[MAXT];

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  n = 300;
  q = 299;
  t = 100000;
  cout << n << " " << q << " " << t << endl;
  for (int i = 0; i < n; ++i) {
    cout << 1 << " ";
  }
  cout << endl;
  for (int i = 0; i < q; ++i) {
    cout << i + 1 << " " << i + 2 << endl;
  }
  fclose(stdout);
}

int main() {
  //testGen();
  freopen("input1.txt", "r", stdin);
  
  cin >> n;
  cin >> q;
  cin >> t;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int b, c;
  fill0(more);
  fill0(mless);
  repeat(q) {
    cin >> b >> c;
    more[b] = c;
    mless[c] = b;
  }
  for (int i = 1; i <= n; ++i) {
    int j = i;
    while (more[j] != 0) {
      j = more[j];
      if (j == i) {
        // Cycle!
        cout << 0 << endl;
        return 0;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (mless[i] != 0) {
      continue;
    }
    int j = i;
    while (more[j] != 0) {
      // j, more[j]
      a[more[j]] += a[j]; // reduce x[j] > x[more[j]] => x[j] > 0
      t -= a[j]; // reduce x[j] > 0 => x[j] >= 0
      // Overflow can happen, so we should check here!
      if (t < 0) {
        cout << 0 << endl;
        return 0;
      }
      j = more[j];
    }
  }
  
  if (t == 0) {
    cout << 1 << endl;
    return 0;
  }
  
  assert(t > 0);
  
  memset(f, 0, sizeof(f));
  for (int i = 1; i <= n; ++i) {
    f[0] = 1;
    for (int iterT = 1; iterT <= t; ++iterT) {
      if (iterT >= a[i]) {
        f[iterT] = (f[iterT] + f[iterT - a[i]]) % MOD;
      }
    }
  }
  
  cout << f[t] << endl;
  
  return 0;
}