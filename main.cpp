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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  map<string, int> vertexMap;
  vector<pair<int, int>> edge;
  
  int m;
  cin >> m;
  repeat(m) {
    string su, tmp, sv;
    cin >> su >> tmp >> sv;
    transform(su.begin(), su.end(), su.begin(), ::tolower);
    transform(sv.begin(), sv.end(), sv.begin(), ::tolower);
    
    int u, v;
    if (vertexMap.count(su)) {
      u = vertexMap[su];
    } else {
      u = (int) vertexMap.size() + 1;
      vertexMap[su] = u;
    }
    
    if (vertexMap.count(sv)) {
      v = vertexMap[sv];
    } else {
      v = (int) vertexMap.size() + 1;
      vertexMap[sv] = v;
    }
    
    edge.push_back(make_pair(u, v));
  }
  
  
  int n = (int) vertexMap.size();
  DirectedGraph g;
  g.init(false, n);
  
  for (auto &e: edge) {
    g.addEdge(e.first, e.second);
  }
  
  LongestPath lp(g);
  cout << lp.getLongestPath() + 1<< endl;
  
  return 0;
}
