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

class DirectedGraph {
  vector<vector<int>> nodeFrom;
  vector<vector<int>> nodeTo;
  vector<int> degIn, degOut;
  vector<bool> erase;
  int n;
public:
  void init(int n) {
    this->n = n;
    nodeFrom.resize(n + 1);
    nodeTo.resize(n + 1);
    degIn.resize(n + 1);
    degOut.resize(n + 1);
    erase.resize(n + 1);
    for_inc_range(u, 1, n) {
      degIn[u] = 0;
      degOut[u] = 0;
      nodeFrom[u].clear();
      nodeTo[u].clear();
      erase[u] = false;
    }
  }
  
  int getSize() const {
    return n;
  }
  
  void addEdge(int u, int v) {
    nodeFrom[u].push_back(v);
    degOut[u]++;
    
    nodeTo[v].push_back(u);
    degIn[v]++;
  }
  
  const vector<int>& getNodeFrom(int u) const {
    return nodeFrom[u];
  }
  
  const vector<int>& getNodeTo(int u) const {
    return nodeTo[u];
  }
  
  int getDegIn(int u) const {
    assert(!erase[u]);
    return degIn[u];
  }
  
  int getDegOut(int u) const {
    assert(!erase[u]);
    return degOut[u];
  }
  
  void removeNode(int u) {
    assert(!erase[u]);
    for (auto &v: getNodeFrom(u)) {
      degIn[v]--;
    }
    for (auto &v: getNodeTo(u)) {
      degOut[v]--;
    }
    erase[u] = true;
  }
};

class TopologicalSort {
  const DirectedGraph &dag;
  
  vector<int> ans;
public:
  TopologicalSort (const DirectedGraph &dag): dag(dag) {
    int n = dag.getSize();
    vector<int> degIn(n + 1);
    
    vector<int> cand;
    
    for_inc_range(u, 1, n) {
      degIn[u] = dag.getDegIn(u);
      if (degIn[u] == 0) {
        cand.push_back(u);
      }
    }

    while (!cand.empty()) {
      int u = cand.back();
      cand.pop_back();
      ans.push_back(u);
      for (auto &v: dag.getNodeFrom(u)) {
        degIn[v]--;
        if (degIn[v] == 0) {
          cand.push_back(v);
        }
      }
    }
  }
  
  const vector<int>& getResult() const {
    return ans;
  }
};

class LongestPath {
  const DirectedGraph &dag;
  
  int longestPath;
  
public:
  LongestPath (const DirectedGraph &dag): dag(dag) {
    TopologicalSort topoSort(dag);
    vector<int> order = topoSort.getResult();
    
    int n = dag.getSize();
    vector<int> f(n + 1);
    longestPath = 0;
    for_inc(i, n) {
      int v = order[i];
      f[v] = 0;
      for (auto &u: dag.getNodeTo(v)) {
        f[v] = max(f[v], f[u] + 1);
      }
      longestPath = max(longestPath, f[v]);
    }
  }
  
  int getLongestPath() {
    return longestPath;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input2.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<pair<pair<int, int>, int>> edge(m + 1);
  for_inc(i, m) {
    int u, v, w;
    cin >> u >> v >> w;
    edge[i] = make_pair(make_pair(u, v), w);
    adj[u].push_back(i);
  }
  
  
  DirectedGraph g;
  g.init(m);
  
  for_inc(i, m) {
    int u, v, w;
    u = edge[i].first.first;
    v = edge[i].first.second;
    w = edge[i].second;
    
    for (auto &e: adj[v]) {
      if (w < edge[e].second) {
        g.addEdge(i + 1, e + 1);
        LOG(1, "Add edge " << i + 1 << " " << e + 1);
      }
    }
  }
  
  LongestPath lp(g);
  cout << lp.getLongestPath() + 1 << endl;
  
  return 0;
}
