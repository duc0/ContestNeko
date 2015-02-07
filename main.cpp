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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(a, 0, sizeof(a))



void testGen() {
  freopen("biginput1.txt", "w", stdout);
  cout << 51 << " " << ((1LL << 50)) << endl;
}

#define MAXN 70

int n;
int a[MAXN];
int ret[MAXN];

int64 need;

bool used[MAXN];

bool used2[MAXN];

int64 solve(int k) {
  if (!used[n]) {
    int64 d = n - ret[k] - 1;
    return (1LL << d);
  }
  int pn = 0;
  fill0(used2);
  for (int i = 1; i <= k; ++i) {
    used2[ret[i]] = true;
    if (ret[i] == n) {
      pn = i;
      break;
    }
  }
  vector<int> notUsed;
  for (int i = n; i >= 1; i--) {
    if (!used2[i]) {
      notUsed.push_back(i);
    }
  }
  assert(notUsed.size() == (n - pn));
  for (int j = pn + 1; j <= k; ++j) {
    if (ret[j] != notUsed[j - (pn + 1)]) {
      return 0;
    }
  }
  return 1;
}

int main() {
  //testGen();
  //freopen("biginput1.txt", "r", stdin);
  
  cin >> n >> need;
  
  fill0(used);
  for (int i = 1; i <= n; ++i) {
    for (int x = 1; x <= n; ++x) {
      if (!used[x]) {
        if (!used[n]) {
          if (i > 1 && x < ret[i - 1]) {
            continue;
          }
        } else {
          if (i > 1 && x > ret[i - 1]) {
            continue;
          }
        }
        used[x] = true;
        
        ret[i] = x;
        
        int64 cnt = solve(i);
        
        if (need <= cnt) {
          break;
        }
        
        need -= cnt;
        used[x] = false;
      }
    }
  }
  
  for (int i = 1; i <= n; ++i) {
    cout << ret[i] << " ";
  }
  return 0;
}