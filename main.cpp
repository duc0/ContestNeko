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


void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  DirectedGraph g;
  g.init(false, n);
  
  repeat(m) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  
  for_inc_range(u, 1, n) {
    if (g.getDegIn(u) % 2 == 1 && g.getDegOut(u) % 2 == 1) {
      g.addEdge(u, u);
    }
  }
  
  vector<int> inOdd;
  vector<int> outOdd;
  for_inc_range(u, 1, n) {
    if (g.getDegIn(u) % 2 == 1) {
      inOdd.push_back(u);
    } else if (g.getDegOut(u) % 2 == 1) {
      outOdd.push_back(u);
    }
  }
  
  while (!inOdd.empty() && !outOdd.empty()) {
    int u = inOdd.back();
    int v = outOdd.back();
    inOdd.pop_back();
    outOdd.pop_back();
    g.addEdge(v, u);
  }
  
  while (!inOdd.empty()) {
    int u = inOdd.back();
    inOdd.pop_back();
    int v = inOdd.back();
    inOdd.pop_back();
    g.addEdge(u, u);
    g.addEdge(u, v);
  }
  
  while (!outOdd.empty()) {
    int u = outOdd.back();
    outOdd.pop_back();
    int v = outOdd.back();
    outOdd.pop_back();
    g.addEdge(u, u);
    g.addEdge(v, u);
  }
  
  m = 0;
  for_inc_range(u, 1, n) {
    m += (int) g.getNodeFrom(u).size();
  }
  
  cout << m << endl;
  for_inc_range(u, 1, n) {
    for (auto &v: g.getNodeFrom(u)) {
      cout << u << " " << v << endl;
    }
  }
  return 0;
}
