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
#define MOD 1000000009
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

class DirectedGraph {
  vector<vector<int>> nodeFrom;
  vector<vector<int>> nodeTo;
  vector<int> degIn, degOut;
  vector<bool> erase;
  int _minNode, _maxNode;
public:
  void init(bool zeroBased, int n) {
    if (zeroBased) {
      _minNode = 0;
      _maxNode = n - 1;
    } else {
      _minNode = 1;
      _maxNode = n;
    }
    nodeFrom.resize(_maxNode + 1);
    nodeTo.resize(_maxNode + 1);
    degIn.resize(_maxNode + 1);
    degOut.resize(_maxNode + 1);
    erase.resize(_maxNode + 1);
    for_inc_range(u, _minNode, _maxNode) {
      degIn[u] = 0;
      degOut[u] = 0;
      nodeFrom[u].clear();
      nodeTo[u].clear();
      erase[u] = false;
    }
  }
  
  int getSize() const {
    return _maxNode - _minNode + 1;
  }
  
  void addEdge(int u, int v) {
    nodeFrom[u].push_back(v);
    degOut[u]++;
    
    nodeTo[v].push_back(u);
    degIn[v]++;
  }
  
  const vector<int> getNodeFrom(int u) const {
    vector<int> r;
    for (auto &v: nodeFrom[u]) {
      if (!erase[v]) {
        r.push_back(v);
      }
    }
    return r;
  }
  
  const vector<int> getNodeTo(int u) const {
    vector<int> r;
    for (auto &v: nodeTo[u]) {
      if (!erase[v]) {
        r.push_back(v);
      }
    }
    return r;
    
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

vector<pair<int, int>> points;
map<pair<int, int>, int> idx;

bool isFreeNode(const DirectedGraph &g, int u) {
  for (auto &v: g.getNodeFrom(u)) {
    if (g.getDegIn(v) == 1) {
      return false;
    }
  }
  return true;
}

// Sample: CF295_B
int main() {
#ifndef SUBMIT
  freopen("input5.txt", "r", stdin);
#endif
  int n;
  cin >> n;
  int x, y;
  for_inc(i, n) {
    cin >> x >> y;
    auto p = make_pair(x, y);
    points.push_back(p);
    idx[p] = i;
  }
  
  DirectedGraph g;
  g.init(true, n);
  
  for_inc(i, n) {
    x = points[i].first;
    y = points[i].second;
    for_inc_range(d, -1, 1) {
      pair<int, int> p = make_pair(x + d, y + 1);
      if (idx.count(p)) {
        g.addEdge(i, idx[p]);
      }
    }
  }
  
  set<int> freeNode;
  for_inc(u, n) {
    if (isFreeNode(g, u)) {
      freeNode.insert(u);
    }
  }
  
  int64 ret = 0;
  bool turn = true;
  
  while (!freeNode.empty()) {
    int u;
    if (turn) {
      u = *freeNode.rbegin();
    } else {
      u = *freeNode.begin();
    }
    turn = !turn;
    
    LOG(1, u);
    ret = MODP(ret * n + u);
    
    freeNode.erase(u);
    g.removeNode(u);
    
    for (auto &v: g.getNodeFrom(u)) {
      if (g.getDegIn(v) == 1) {
        for (auto &w : g.getNodeTo(v)) {
          freeNode.erase(w);
        }
      }
    }
    for (auto &v: g.getNodeTo(u)) {
      if (isFreeNode(g, v)) {
        freeNode.insert(v);
      }
    }
  }
  
  cout << ret << endl;
  return 0;
}
