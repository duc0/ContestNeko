#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>

using namespace std;

#define MAXN 400

#define MOD 1000000007
#define MAXT 101000

int n, q, t;
int a[MAXN];
int more[MAXN];
int mless[MAXN];

int f[MAXT];

int main() {
  freopen("input2.txt", "r", stdin);
  
  cin >> n;
  cin >> q;
  cin >> t;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int b, c;
  memset(more, 0, sizeof(more));
  memset(mless, 0, sizeof(mless));
  for (int i = 0; i < q; ++i) {
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