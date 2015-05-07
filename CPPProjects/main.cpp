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

#define MAXN 3030
int n, m;

vector<int> adj[MAXN];

int dist[MAXN][MAXN];

int s1, t1, l1, s2, t2, l2;

void bfs(int start) {
  queue<int> q;
  
  q.push(start);
  
  dist[start][start] = 0;
  
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    int curDist = dist[start][cur];
    
    for (auto &next: adj[cur]) {
      if (dist[start][next] == -1) {
        dist[start][next] = curDist + 1;
        q.push(next);
      }
    }
  }
}

int solve() {
  int ans = dist[s1][t1] + dist[s2][t2];
  for_inc_range(mid1, 1, n) {
    for_inc_range(mid2, 1, n) {
      int time1 = dist[s1][mid1] + dist[mid1][mid2] + dist[mid2][t1];
      int time2 = dist[s2][mid1] + dist[mid1][mid2] + dist[mid2][t2];
      if (time1 <= l1 && time2 <= l2) {
        int totalEdge = time1 + time2 - dist[mid1][mid2];
        ans = min(ans, totalEdge);
      }
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n >> m;
  
  repeat(m) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  memset(dist, -1, sizeof(dist));  
  for_inc_range(u, 1, n) {
    bfs(u);
  }
  
  cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
  
  if (dist[s1][t1] > l1 || dist[s2][t2] > l2) {
    cout << -1 << endl;
    return 0;
  }
  
  int ans1 = solve();
  swap(s2, t2);
  int ans2 = solve();
  int ans = min(ans1, ans2);
  
  cout << m - ans << endl;
  return 0;
}
