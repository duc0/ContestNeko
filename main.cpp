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
#include <queue>

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)

#define for_inc(i,x) for(auto i=0; i < x;++i)
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
#define for_inc_range(i,x,y) for (auto i=x; i<=y; ++i)
#define for_dec_range(i,x,y) for (auto i=x; i>=y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n;

#define MAXN 100100

#define MOD 1000000007



vector<vector<pair<int, int>>> adj;
bool visit[MAXN];

int parent[MAXN];
int cntNode[MAXN];
int sumDist[MAXN];
int sumSqrDist[MAXN]; // sum sqr dist from u to all nodes in subtree root u

int sumAllSqrDist[MAXN]; // sum sqr dist from u to all other nodes
int sumAllDist[MAXN]; // sum dist from u to all other nodes

int getDistInc(int w, int v) {
  return ((int64)cntNode[v] * w + sumDist[v]) % MOD;
}

int getSqrDistInc(int w, int v) {
  int sqrDistInc = ((int64)w * w) % MOD;
  sqrDistInc = ((int64)sqrDistInc * cntNode[v]) % MOD;
  sqrDistInc = (sqrDistInc + (int64) 2 * w * sumDist[v]) % MOD;
  sqrDistInc = (sqrDistInc + sumSqrDist[v]) % MOD;
  return sqrDistInc;
}

void dfs(int u) {
  visit[u] = true;
  cntNode[u] = 1;
  sumDist[u] = 0;
  sumSqrDist[u] = 0;
  
  for (auto &e : adj[u]) {
    int v = e.first, w = e.second;
    if (v != parent[u] && !visit[v]) {
      parent[v] = u;
      dfs(v);
      cntNode[u] += cntNode[v];
      sumDist[u] = (sumDist[u] + getDistInc(w, v)) % MOD;
      sumSqrDist[u] = (sumSqrDist[u] + getSqrDistInc(w, v)) % MOD;
    }
  }
}

void dfsSumAllDist(int u) {
  visit[u] = true;
  for (auto &e : adj[u]) {
    int v = e.first, w = e.second;
    if (v != parent[u] && !visit[v]) {
      int nOutside = n - cntNode[v];
      int retSumDist = sumAllDist[u];
      retSumDist = (retSumDist - getDistInc(w, v)) % MOD;
      if (retSumDist < 0) retSumDist += MOD;
      
      int retSumSqrDist = sumAllSqrDist[u];
      retSumSqrDist = (retSumSqrDist - getSqrDistInc(w, v)) % MOD;
      if (retSumSqrDist < 0) retSumSqrDist += MOD;
      int inc = ((int64)w*w) % MOD;
      inc = ((int64)inc * nOutside) % MOD;
      inc = (inc + (int64) 2 * w * retSumDist) % MOD;
      retSumSqrDist = (retSumSqrDist + inc) % MOD;
      
      retSumDist = (retSumDist + (int64)w * nOutside) % MOD;
      retSumDist = (retSumDist + sumDist[v]) % MOD;
      sumAllDist[v] = retSumDist;
      
      retSumSqrDist = (retSumSqrDist + sumSqrDist[v]) % MOD;
      sumAllSqrDist[v] = retSumSqrDist;
      
      dfsSumAllDist(v);
    }
  }
}

int main() {
  //testGen();
  freopen("input1.txt", "r", stdin);
  
  scanf("%d", &n);
  adj.resize(n + 1);
  int a, b, c;
  repeat(n - 1) {
    scanf("%d%d%d", &a, &b, &c);
    adj[a].push_back(make_pair(b, c));
    adj[b].push_back(make_pair(a, c));
  }
  fill0(visit);
  parent[1] = 0;
  dfs(1);
  
  fill0(visit);
  sumAllSqrDist[1] = sumSqrDist[1];
  sumAllDist[1] = sumDist[1];
  dfsSumAllDist(1);
  
  cout << cntNode[1] << endl;
  cout << sumDist[1] << endl;
  cout << sumDist[3] << endl;
  cout << sumSqrDist[1] << endl;
  cout << sumSqrDist[4] << endl;
  cout << sumAllDist[3] << endl;
  cout << sumAllSqrDist[5] << endl;
  
  return 0;
}