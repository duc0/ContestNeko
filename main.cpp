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

class UndirectedGraph {
  vector<vector<int>> adj;
  vector<int> comp;
  vector<int> color;
  bool ccBuilt = false;
  int n, nComp;
  bool _hasOddCycle = false;
  
  void dfs(int u, int c) {
    comp[u] = nComp;
    color[u] = c;
    for (auto &v: adj[u]) {
      if (comp[v] == -1) {
        dfs(v, 1 - c);
      } else {
        if (color[v] != 1 - c) {
          _hasOddCycle = true;
        }
      }
    }
  }
  
public:
  void init(int n) {
    this->n = n;
    adj.resize(n + 1);
    for_inc_range(u, 1, n) {
      adj[u].clear();
    }
    ccBuilt = false;
  }
  
  void addEdge(int u, int v) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    adj[u].push_back(v);
    adj[v].push_back(u);
    ccBuilt = false;
  }
  
  // Find connected components and detect odd cycle
  void buildCC() {
    ccBuilt = true;
    comp.resize(n + 1);
    fill(comp.begin(), comp.end(), -1);
    color.resize(n + 1);
    nComp = 0;
    _hasOddCycle = false;
    for_inc_range(u, 1, n) {
      if (comp[u] == -1) {
        nComp++;
        dfs(u, 0);
      }
    }
  }
  
  bool hasOddCycle() {
    assert(ccBuilt);
    return _hasOddCycle;
  }
  
  int getComponent(int u) {
    assert(ccBuilt);
    return comp[u];
  }
  
  int getNumberOfComponents() {
    assert(ccBuilt);
    return nComp;
  }
};

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

UndirectedGraph sameGraph, compGraph;

vector<vector<int>> diffEdge;

int main() {
  //freopen("input2.txt", "r", stdin);
  
  cin >> n >> k;
  int a, b, c; string s;
  
  diffEdge.resize(n + 2);
  
  sameGraph.init(n + 1);
  
  repeat(k) {
    cin >> a >> b >> s;
    c = s[0] == 'x';
    Equation e = getEquation(a, b);
    int u = e.l == 0 ? n + 1 : e.l;
    int v = e.r == 0 ? n + 1 : e.r;
    if (c == 0) {
      diffEdge[u].push_back(v);
      diffEdge[v].push_back(u);
    } else {
      sameGraph.addEdge(u, v);
    }
  }
  
  sameGraph.buildCC();
  
  compGraph.init(sameGraph.getNumberOfComponents());
  for_inc_range(u, 1, n + 1) {
    for (auto &v: diffEdge[u]) {
      int cu = sameGraph.getComponent(u);
      int cv = sameGraph.getComponent(v);
      if (cu == cv) {
        cout << 0;
        return 0;
      } else {
        compGraph.addEdge(cu, cv);
      }
    }
  }
  
  compGraph.buildCC();
  if (compGraph.hasOddCycle()) {
    cout << 0;
    return 0;
  }
  
  int ret = 1;
  for_inc_range(i, 1, compGraph.getNumberOfComponents() - 1) {
    ret = (ret * 2) % MOD;
  }
  cout << ret << endl;
  
  return 0;
}
