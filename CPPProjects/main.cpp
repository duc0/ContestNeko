//#define SUBMIT

#define C11

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
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11
#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>
#endif

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

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

#define MAXN 200100
int n;
vector<int> adj[MAXN];
vector<int> children[MAXN];

int f[MAXN];
int fPar[MAXN];
vector<int> prefix[MAXN];
vector<int> suffix[MAXN];

int ans[MAXN];

void calcChildren(int cur, int parent) {
  for (int child: adj[cur]) {
    if (child != parent) {
      children[cur].push_back(child);
      calcChildren(child, cur);
    }
  }
}

void calcF(int cur, int parent) {
  f[cur] = 1;
  int nChild = (int) children[cur].size();
  prefix[cur].resize(nChild);
  suffix[cur].resize(nChild);
  for_inc(i, nChild) {
    calcF(children[cur][i], cur);
    f[cur] = ((int64) f[cur] * (f[children[cur][i]] + 1)) % MOD;
  }
  for_inc(i, nChild) {
    if (i == 0) {
      prefix[cur][i] = 1;
    } else {
      prefix[cur][i] = ((int64)prefix[cur][i - 1] * (f[children[cur][i - 1]] + 1)) % MOD;
    }
  }
  
  for_dec(i, nChild) {
    if (i == nChild - 1) {
      suffix[cur][i] = 1;
    } else {
      suffix[cur][i] = ((int64) suffix[cur][i + 1] * (f[children[cur][i + 1]] + 1)) % MOD;
    }
  }
}

void calcAns(int cur, int childId, int parent) {
  if (parent == -1) {
    ans[cur] = f[cur];
    fPar[cur] = 0;
  } else {
    fPar[cur] = ((int64)suffix[parent][childId] * prefix[parent][childId]) % MOD;
    fPar[cur] = ((int64)fPar[cur] * (fPar[parent] + 1)) % MOD;
    ans[cur] = ((int64)f[cur] * (fPar[cur] + 1)) % MOD;
  }
  int nChild = (int) children[cur].size();
  for_inc(i, nChild) {
    calcAns(children[cur][i], i, cur);
  }
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n;
  
  for_inc_range(u, 2, n) {
    int x;
    cin >> x;
    adj[u].push_back(x);
    adj[x].push_back(u);
  }
  
  int root = 1;
  calcChildren(root, -1);
  calcF(root, -1);
  calcAns(root, -1, -1);
  
  for_inc_range(u, 1, n) {
    cout << ans[u] << " ";
  }
  return 0;
}
