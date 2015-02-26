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

#define LOG(l, x)                                                              \
if (l <= LOGLEVEL)                                                           \
cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0)
    r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template <class FlowType, class CostType> class CostNetwork {
  template <class FT, class CT> friend class SSPath;
  size_t n;
  vector<vector<int>> a;
  int s, t;
  
  vector<vector<FlowType>> c, f;
  FlowType totalFlow;
  
  vector<vector<CostType>> cost;
  CostType totalCost;
  
public:
  void reset(int n) {
    this->n = n;
    c.resize(n);
    for (int i = 0; i < n; ++i) {
      c[i].resize(n);
      for (int j = 0; j < n; ++j) {
        c[i][j] = 0;
      }
    }
    cost.resize(n);
    for (int i = 0; i < n; ++i) {
      cost[i].resize(n);
      for (int j = 0; j < n; ++j) {
        cost[i][j] = 0;
      }
    }
    f.resize(n);
    for (int i = 0; i < n; ++i) {
      f[i].resize(n);
      for (int j = 0; j < n; ++j) {
        f[i][j] = 0;
      }
    }
    a.resize(n);
    for (int i = 0; i < n; ++i) {
      a[i].clear();
    }
    totalFlow = 0;
    totalCost = 0;
  }
  
  CostNetwork() {}
  CostNetwork(int n) { reset(n); }
  
  void addEdge(int u, int v, int c, CostType cost) {
    this->c[u][v] = c;
    this->cost[u][v] = cost;
    a[u].push_back(v);
    a[v].push_back(u);
  }
  
  const vector<int> &getAdjacent(int u) const { return a[u]; }
  
  int getSource() const { return s; }
  int getSink() const { return t; }
  
  void setSource(int s) { this->s = s; }
  void setSink(int t) { this->t = t; }
  
  FlowType getFlow() const { return totalFlow; }
  
  CostType getCost() const { return totalCost; }
  
  size_t getSize() const { return n; }
  
  FlowType getFlow(int u, int v) const { return f[u][v]; }
  
  CostType getCost(int u, int v) const { return cost[u][v]; }
};

// Successive shortest path algorithm
template <class FlowType, class CostType> class SSPath {
  vector<int> pre;
  vector<CostType> pi; // potential
  vector<bool> fixed;
  vector<CostType> d;
  bool _hasNegativeCycle;
  const CostType INF = numeric_limits<CostType>::max() / 2;
  
  bool findAugmentingPath(const CostNetwork<FlowType, CostType> &g) {
    for (int u = 0; u < g.n; ++u) {
      fixed[u] = false;
      d[u] = INF;
    }
    d[g.s] = 0;
    
    while (1) {
      int u = -1;
      for (int v = 0; v < g.n; ++v) {
        if (!fixed[v] && (u == -1 || d[v] < d[u])) {
          u = v;
        }
      }
      if (u == -1)
        break;
      fixed[u] = true;
      for (int i = 0; i < g.a[u].size(); ++i) {
        int v = g.a[u][i];
        if (!fixed[v]) {
          CostType w = INF;
          if (g.f[v][u] > 0) {
            w = -g.cost[v][u] + pi[u] - pi[v];
          } else if (g.f[u][v] < g.c[u][v]) {
            w = g.cost[u][v] + pi[u] - pi[v];
          }
          if (d[u] + w < d[v]) {
            d[v] = d[u] + w;
            pre[v] = u;
          }
        }
      }
    }
    for (int u = 0; u < g.n; ++u) {
      pi[u] += d[u];
    }
    return d[g.t] != INF;
  }
  
  void incFlow(CostNetwork<FlowType, CostType> &g, const FlowType &targetFlow) {
    FlowType delta = targetFlow - g.totalFlow;
    for (int v = g.t; v != g.s; v = pre[v]) {
      int u = pre[v];
      if (g.f[v][u] > 0) {
        delta = min(delta, g.f[v][u]);
      } else {
        delta = min(delta, g.c[u][v] - g.f[u][v]);
      }
    }
    for (int v = g.t; v != g.s; v = pre[v]) {
      int u = pre[v];
      if (g.f[v][u] > 0) {
        g.f[v][u] -= delta;
      } else {
        g.f[u][v] += delta;
      }
    }
    g.totalFlow += delta;
    g.totalCost += delta * pi[g.t];
  }
  
  void initPi(const CostNetwork<FlowType, CostType> &g) {
    _hasNegativeCycle = false;
    queue<int> q;
    vector<bool> in_q(g.n);
    vector<int> cnt(g.n);
    q.push(g.s);
    in_q[g.s] = true;
    cnt[g.s] = 1;
    for (int u = 0; u < g.n; ++u) {
      pi[u] = INF;
    }
    pi[g.s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      in_q[u] = false;
      for (int i = 0; i < g.a[u].size(); ++i) {
        int v = g.a[u][i];
        if (g.c[u][v] > 0 && pi[u] + g.cost[u][v] < pi[v]) {
          pi[v] = pi[u] + g.cost[u][v];
          if (!in_q[v]) {
            q.push(v);
            in_q[v] = true;
            ++cnt[v];
            if (cnt[v] > g.n) {
              _hasNegativeCycle = true; // negative cycle detected
              return;
            }
          }
        }
      }
    }
  }
  
public:
  // set target_f = INF for max flow
  SSPath(CostNetwork<FlowType, CostType> &g, const FlowType &targetFlow) {
    pre.resize(g.n);
    pi.resize(g.n);
    fixed.resize(g.n);
    d.resize(g.n);
    initPi(g);
    if (_hasNegativeCycle) {
      return; // cannot work with negative cycles
    }
    while (g.totalFlow < targetFlow && findAugmentingPath(g)) {
      incFlow(g, targetFlow);
    }
  }
  
  bool hasNegativeCycle() const { return _hasNegativeCycle; }
};

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, m, k, s, f;
  scanf("%d%d%d%d%d", &n, &m, &k, &s, &f);
  CostNetwork<int64, int64> g(n);
  g.setSource(s - 1);
  g.setSink(f - 1);
  while (m--) {
    int u, v, c, d;
    scanf("%d%d%d%d", &u, &v, &c, &d);
    g.addEdge(u - 1, v - 1, d, c);
    g.addEdge(v - 1, u - 1, d, c);
  }
  SSPath<int64, int64> ssp(g, k);
  if (g.getFlow() < k) {
    cout << -1 << endl;
  } else {
    cout << g.getCost() << endl;
    for (int u = 0; u < g.getSize(); ++u) {
      for (int v = 0; v < g.getSize(); ++v) {
        if (g.getFlow(u, v) > 0) {
          cout << u + 1 << " " << v + 1 << " " << g.getFlow(u, v) << endl;
        }
      }
    }
    cout << "0 0 0" << endl;
  }
  return 0;
}
