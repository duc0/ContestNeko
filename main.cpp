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

#define MAXN 100100

#define MOD 1000000007
int MODP(int64 a) {
  int r = a % MOD;
  if (r < 0) r += MOD;
  return r;
}

int n;
int parent[MAXN];
vector<int> child[MAXN];

#define EVEN 0
#define ODD 1

int f[2][MAXN]; // f[0][u], f[1][u]: color even/odd number of vertices in subtree rooted at u

int g[2][MAXN];

int h[2][2][MAXN]; // dup

void dfs(int u) {
  f[EVEN][u] = 0;
  f[ODD][u] = 1; // only color u

  if (child[u].empty()) {
    return;
  }

  for (auto &v: child[u]) {
    dfs(v);
  }
  int nChild = (int)child[u].size();

  g[EVEN][1] = MODP(1 + f[EVEN][child[u][0]]); // no color + f-child even
  g[ODD][1] = f[ODD][child[u][0]];
  
  for_inc_range(i, 2, nChild) {
    int v = child[u][i - 1];
    g[EVEN][i] = MODP(MODP((int64)g[EVEN][i-1] * (1 + f[EVEN][v])) + MODP((int64)g[ODD][i - 1] * f[ODD][v]));
    g[ODD][i] = MODP(MODP((int64)g[ODD][i-1] * (1 + f[EVEN][v])) + MODP((int64)g[EVEN][i - 1] * f[ODD][v]));
  }
  
  
  // Count for two-way traversal
  f[EVEN][u] = MODP(g[ODD][nChild] * 2);
  f[ODD][u] = MODP(g[EVEN][nChild] * 2);
  
  // Now subtract the duplicates
  
  h[EVEN][EVEN][1] = MODP(1 + f[EVEN][child[u][0]]);
  h[EVEN][ODD][1] = 1; // no color
  h[ODD][ODD][1] = 0;
  h[ODD][EVEN][1] = f[ODD][child[u][0]];
  
  
  for_inc_range(i, 2, nChild) {
    int v = child[u][i - 1];
    for_inc_range(curPar, 0, 1) {
      for_inc_range(remainPar, 0, 1) {
        int r = h[curPar][remainPar][i - 1]; //Not color i
        
        if (curPar == remainPar) {
          // color i even
          r = MODP(r + (int64)h[curPar][remainPar][i - 1] * f[EVEN][v]);
        } else {
          // color i odd
          r = MODP(r + (int64)h[1 - curPar][1 - remainPar][i - 1] * f[ODD][v]);
        }
        h[curPar][remainPar][i] = r;
      }
    }
  }
  
  f[EVEN][u] = MODP(f[EVEN][u] - h[ODD][EVEN][nChild]);
  f[ODD][u] = MODP(f[ODD][u] - h[EVEN][EVEN][nChild]);
  
}
int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  scanf("%d", &n);
  
  parent[1] = -1;
  for_inc_range(u, 2, n) {
    scanf("%d", &parent[u]);
    child[parent[u]].push_back(u);
  }
  
  dfs(1);
  
  cout << MODP(f[0][1] + f[1][1]) << endl;
  return 0;
}