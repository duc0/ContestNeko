//#define SUBMIT

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
#include <array>
#include <type_traits>
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

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

class EulerTour {
  UndirectedGraph g;
  vector<int> euler;
public:
  EulerTour(const UndirectedGraph &g): g(g) {
    int n = g.getSize();
    stack<int> s;
    s.push(1);
    UndirectedGraphEdgeMarker used(g);
    vector<int> curPos(n + 1);
    while (!s.empty()) {
      int u = s.top();
      if (curPos[u] < g.getAdjacent(u).size()) {
        int v = g.getAdjacent(u)[curPos[u]];
        if (used.test(u, curPos[u])) {
          curPos[u]++;
          continue;
        }
        s.push(v);
        used.mark(u, curPos[u]);
      } else {
        s.pop();
        euler.push_back(u);
      }
    }
  }
  
  const vector<int> &getEulerTour() {
    return euler;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// CF296 - Div1 - Cg

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  UndirectedGraph g;
  g.init(n);
  
  repeat(m) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  
  vector<int> oddV;
  for_inc_range(u, 1, n) {
    if (g.getDeg(u) % 2 == 1) {
      oddV.push_back(u);
    }
  }
  
  while (oddV.size() >= 2) {
    int u = oddV.back();
    oddV.pop_back();
    int v = oddV.back();
    oddV.pop_back();
    g.addEdge(u, v);
  }
  
  if (oddV.size() == 1) {
    int u = oddV.back();
    g.addEdge(u, u);
  }
  
  if (g.getNumEdges() % 2 == 1) {
    g.addEdge(1, 1);
  }
  
  EulerTour e(g);
  vector<int> t = e.getEulerTour();
  for (auto u: t) {
    LOG(1, "Euler: " << u);
  }
  
  m = g.getNumEdges();
  cout << m << endl;
  bool first = true;
  for (int i = 0; i < m; ++i) {
    if (first) {
      cout << t[i] << " " << t[(i + 1) % m] << endl;
    } else {
      cout << t[(i + 1) % m] << " " << t[i] << endl;
    }
    first = !first;
  }
  
  return 0;
}
