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
vector<pair<int, int>> adj[MAXN];

int cache[2*MAXN];

int solve(int u, int edgeId, int parent) {
  if (edgeId != -1 && cache[edgeId] != -1) {
    return cache[edgeId];
  }
  int ans = 1;
  for (auto &edge: adj[u]) if (edge.first != parent) {
    ans = ((int64) ans * (solve(edge.first, edge.second, u) + 1)) % MOD;
  }
  cache[edgeId] = ans;
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n;
  
  memset(cache, -1, sizeof(cache));
  int nDirectEdge = 0;
  for_inc_range(u, 2, n) {
    int x;
    cin >> x;
    nDirectEdge++;
    adj[u].push_back(make_pair(x, nDirectEdge));
    nDirectEdge++;
    adj[x].push_back(make_pair(u, nDirectEdge));
  }
  
  for_inc_range(u, 1, n) {
    cout << solve(u, -1, -1) << " ";
  }
  return 0;
}
