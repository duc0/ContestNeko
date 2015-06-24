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

class UndirectedGraph {
  friend class UndirectedGraphEdgeMarker;
  
  vector<vector<int>> adj;
  // indexMap[u][i] = the index of the same edge in adj[v]
  vector<vector<int>> indexMap;
  vector<int> comp;
  vector<int> color;
  vector<int> deg;
  bool ccBuilt = false;
  int nEdge = 0;
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
    indexMap.resize(n + 1);
    deg.resize(n + 1);
    for_inc_range(u, 1, n) {
      adj[u].clear();
      indexMap[u].clear();
    }
    nEdge = 0;
    ccBuilt = false;
  }
  
  const vector<int> &getAdjacent(int u) const {
    return adj[u];
  }
  
  void addEdge(int u, int v) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    adj[u].push_back(v);
    adj[v].push_back(u);
    indexMap[u].push_back((int)adj[v].size() - 1);
    indexMap[v].push_back((int)adj[u].size() - 1);
    nEdge++;
    deg[u]++;
    deg[v]++;
    ccBuilt = false;
  }
  
  int getDeg(int u) const {
    return deg[u];
  }
  
  int getSize() const {
    return n;
  }
  
  int getNumEdges() const {
    return nEdge;
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

class UndirectedGraphEdgeMarker {
  UndirectedGraph g;
  vector<vector<bool>> flag;
  int n;
  
  void set(int u, int i, bool b) {
    assert(i >= 0 && i < g.getAdjacent(u).size());
    flag[u][i] = b;
    int v = g.getAdjacent(u)[i];
    flag[v][g.indexMap[u][i]] = b;
  }
public:
  UndirectedGraphEdgeMarker(const UndirectedGraph &g): g(g) {
    n = g.getSize();
    flag.resize(n + 1);
    for_inc_range(u, 1, n) {
      flag[u].resize(g.getAdjacent(u).size());
    }
  }
  
  void mark(int u, int i) {
    set(u, i, true);
  }
  
  void unmark(int u, int i) {
    set(u, i, false);
  }
  
  bool test(int u, int i) const {
    assert(i >= 0 && i < g.getAdjacent(u).size());
    return flag[u][i];
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 100100

int n, m;
vector<int> eq[MAXN];
vector<int> diff[MAXN];
vector<pair<int, int>> diffEdge;
int val[MAXN];

void noSol() {
  cout << 0 << endl;
  exit(0);
}

void dfsVal(int u) {
  assert(val[u] != -1);
  for (int v: eq[u]) {
    if (val[v] != -1 && val[v] != val[u]) {
      noSol();
    }
    if (val[v] == -1) {
      val[v] = val[u];
      dfsVal(v);
    }
  }
  
  for (int v: diff[u]) {
    if (val[v] != -1 && val[v] == val[u]) {
      noSol();
    }
    if (val[v] == -1) {
      val[v] = 1 - val[u];
      dfsVal(v);
    }
  }
}

int nComp;
int comp[MAXN];

void dfsEq(int u) {
  assert(val[u] == -1);
  assert(comp[u] == -1);
  
  comp[u] = nComp;
  for (int v: eq[u]) {
    assert(val[v] == -1);
    if (comp[v] == -1) {
      dfsEq(v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input3.txt", "r", stdin);
#endif
  
  scanf("%d%d", &n, &m);
  
  memset(val, -1, sizeof(val));
  
  repeat(m) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    if (u > v) {
      swap(u, v);
    }
    if (u == 1) {
      val[v] = c;
    } else {
      if (c == 1) {
        eq[u].push_back(v);
        eq[v].push_back(u);
      } else {
        diff[u].push_back(v);
        diff[v].push_back(u);
        diffEdge.push_back(make_pair(u, v));
      }
    }
  }
  
  for_inc_range(u, 2, n) {
    if (val[u] != -1) {
      dfsVal(u);
    }
  }
  
  memset(comp, -1, sizeof(comp));
  nComp = 0;
  for_inc_range(u, 2, n) {
    if (val[u] == -1 && comp[u] == -1) {
      nComp++;
      dfsEq(u);
    }
  }
  
  UndirectedGraph graph;
  graph.init(nComp);
  
  for (auto &e: diffEdge) {
    int u = e.first, v = e.second;
    if (comp[u] != -1 && comp[v] != -1) {
      graph.addEdge(comp[u], comp[v]);
    }
  }
  
  graph.buildCC();
  if (graph.hasOddCycle()) {
    noSol();
  }
  
  int nComp = graph.getNumberOfComponents();
  
  int ret = 1;
  repeat(nComp) {
    ret = ((int64) ret * 2) % MOD;
  }
  cout << ret << endl;
  
  return 0;
}
