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
#include <queue>
#include <stack>
#include <functional>

using namespace std;

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define MOD 1000000007

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

struct Equation {
  int l, r;
};

int n, k;

Equation getEquation(int r, int c) {
  if (r + c > n + 1) {
    return getEquation(n - c + 1, n - r + 1);
  }
  if (r > c) {
    return getEquation(c, r);
  }
  int diag = c - r + 1;
  Equation e;
  e.l = diag;
  e.r = diag + 2 * (r - 1);
  if (e.l <= 2) {
    e.l = 0;
  } else e.l -= 2;
  
  return e;
}

vector<vector<int>> diffEdge, sameEdge;

vector<int> compSame;
int nComp = 0;

void dfsComp(int u) {
  compSame[u] = nComp;
  for (auto &v: sameEdge[u]) {
    if (compSame[v] == -1) {
      dfsComp(v);
    }
  }
}

vector<vector<int>> compEdge;
vector<int> comp;
vector<int> color;

int nRegion = 0;

bool dfs(int u, int c) {
  comp[u] = nRegion;
  color[u] = c;
  for (auto &v: compEdge[u]) {
    if (comp[v] == -1) {
      if (!dfs(v, 1 - c)) {
        return false;
      }
    } else {
      if (color[v] != 1 - c) {
        // odd cycle
        return false;
      }
    }
  }
  return true;
}

int main() {
  freopen("input2.txt", "r", stdin);
  
  cin >> n >> k;
  int a, b, c; string s;
  
  diffEdge.resize(n + 1);
  sameEdge.resize(n + 1);
  
  repeat(k) {
    cin >> a >> b >> s;
    c = s[0] == 'x';
    Equation e = getEquation(a, b);
    //cout << e.l << " " << e.r << " " << c << endl;
    if (c == 0) {
      diffEdge[e.l].push_back(e.r);
      diffEdge[e.r].push_back(e.l);
    } else {
      sameEdge[e.l].push_back(e.r);
      sameEdge[e.r].push_back(e.l);
    }
  }
  
  compSame.resize(n + 1);
  fill(compSame.begin(), compSame.end(), - 1);
  for_inc_range(u, 0, n) {
    if (compSame[u] == -1) {
      nComp++;
      dfsComp(u);
    }
  }
  
  compEdge.resize(nComp + 1);
  for_inc_range(u, 0, n) {
    for (auto &v: diffEdge[u]) {
      if (compSame[u] == compSame[v]) {
        cout << 0;
        return 0;
      } else {
        compEdge[compSame[u]].push_back(compSame[v]);
        compEdge[compSame[v]].push_back(compSame[u]);
      }
    }
  }
  
  comp.resize(nComp + 1);
  fill(comp.begin(), comp.end(), -1);
  color.resize(nComp + 1);
  for_inc_range(u, 1, nComp) {
    if (comp[u] == -1) {
      nRegion++;
      if (!dfs(u, 0)) {
        cout << 0;
        return 0;
      }
    }
  }
  
  int ret = 1;
  for_inc_range(i, 1, nRegion - 1) {
    ret = (ret * 2) % MOD;
  }
  cout << ret << endl;
  
  return 0;
}
