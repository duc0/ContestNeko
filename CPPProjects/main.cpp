#define SUBMIT

//#define C11

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
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, m, nQuery;
  cin >> n >> m >> nQuery;
  
  vector< vector<int> > adj(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  
  vector< vector< vector<short> > > ans(2);
  ans[0].resize(n + 1);
  ans[1].resize(n + 1);
  for (int u = 1; u <= n; ++u) {
    ans[0][u].resize(n + 1);
    ans[1][u].resize(n + 1);
  }
  
  for (int start = 1; start <= n; ++start) {
    if (adj[start].empty()) continue;
    queue< pair<int, int> > q;
    q.push(make_pair(start, 0));
    vector< vector<bool> > visit(2);
    visit[0].resize(n + 1);
    visit[1].resize(n + 1);
    visit[0][start] = true;
    ans[0][start][start] = 1;
    
    while (!q.empty()) {
      pair<int, int> cur = q.front();
      q.pop();
      int u = cur.first;
      for (int i = 0; i < (int) adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!visit[1 - cur.second][v]) {
          q.push(make_pair(v, 1 - cur.second));
          ans[1 - cur.second][start][v] = ans[cur.second][start][u] + 1;
          visit[1 - cur.second][v] = true;
        }
      }
    }
  }
  
  while (nQuery--) {
    int s, t, d;
    cin >> s >> t >> d;
    int a = ans[d % 2][s][t];
    if (a != 0 && a - 1 <= d) {
      cout << "TAK" << endl;
    } else {
      cout << "NIE" << endl;
    }
  }
  return 0;
}
