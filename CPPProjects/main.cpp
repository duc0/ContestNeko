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

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template<int BASE, int64 MODULO> class StringHash {
  template<int B, int64 M> friend class StringHasher;
  vector<int64> hash;
public:
  size_t getSize() const {
    return hash.size();
  }
};

template<int BASE, int64 MODULO> class StringHasher {
  static int64 getBasePower(int n) {
    static vector<int64> power; // cache
    if (n > (int)power.size() - 1) {
      int cur = (int) power.size() - 1;
      power.resize(n + 1);
      for_inc_range(i, cur + 1, n) {
        if (i == 0) {
          power[i] = 1;
        } else {
          power[i] = (power[i - 1] * BASE) % MODULO;
        }
      }
    }
    return power[n];
  }
  
public:
  template<class Iterator> static StringHash<BASE, MODULO> getHash(Iterator begin, Iterator end) {
    StringHash<BASE, MODULO> h;
    int n = (int)(end - begin);
    h.hash.resize(n);
    int idx = 0;
    int64 last = 0;
    for (auto it = begin; it != end; ++it) {
      h.hash[idx] = (last * BASE + *it) % MODULO;
      last = h.hash[idx];
      idx++;
    }
    return h;
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh) {
    return sh.hash[sh.getSize() - 1];
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh, int first, int len) {
    assert(0 <= first && first < sh.getSize());
    assert(len >= 1);
    assert(first + len - 1 < sh.getSize());
    
    int last = first + len - 1;
    
    if (first == 0) return sh.hash[last];
    
    int64 ret = (sh.hash[last] - sh.hash[first - 1] * getBasePower(len)) % MODULO;
    if (ret < MODULO) ret += MODULO;
    return ret;
  }
  
  static int64 getHashValueConcat(const StringHash<BASE, MODULO> &sh1, const StringHash<BASE, MODULO> &sh2) {
    
    return (getHashValue(sh1) * getBasePower((int)sh2.getSize()) + getHashValue(sh2)) % MODULO;
  }
  
};

template <class T> class Network {
  struct Edge {
    int u, v;
    T f, c;
  };
  vector<Edge> edgeList;
  vector<vector<int>> adj;
  
public:
  vector<int> &getAdjacent(int u) { return adj[u]; }
  
  Edge &getEdge(int i) { return edgeList[i]; }
  
  void addEdge(int u, int v, T c) {
    Edge e = {u, v, 0, c};
    adj[u].push_back((int)edgeList.size());
    adj[v].push_back((int)edgeList.size());
    edgeList.push_back(e);
  }
  size_t getSize() { return adj.size(); }
  void resetFlow() {
    for (auto &pe : edgeList)
      pe.f = 0;
  }
  void init(int n) {
    edgeList.clear();
    adj.resize(n);
    for (auto &au : adj)
      au.clear();
  }
  Network(int n) { init(n); }
};

template <class T> class Dinic {
  Network<T> &g;
  int s, t;
  vector<T> dist;
  vector<bool> block;
  const T INF = numeric_limits<T>::max() / 2;
  
  bool computeDist() {
    queue<int> q;
    q.push(t);
    fill(dist.begin(), dist.end(), -1);
    dist[t] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto pi : g.getAdjacent(u)) {
        auto &e = g.getEdge(pi);
        int v = -1;
        if (e.v == u && e.f < e.c)
          v = e.u;
        else if (e.u == u && e.f > 0)
          v = e.v;
        if (v != -1 && dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
          if (v == s)
            return true;
        }
      }
    }
    return dist[s] != -1;
  }
  T findAugmentingPath(int u, T delta) {
    if (u == t)
      return delta;
    T inc;
    for (auto pi : g.getAdjacent(u)) {
      auto &e = g.getEdge(pi);
      int v = -1, i = 0, d = 0;
      if (e.u == u && e.f < e.c) {
        v = e.v;
        i = 1;
        d = e.c - e.f;
      } else if (e.v == u && e.f > 0) {
        v = e.u;
        i = -1;
        d = e.f;
      }
      if (v != -1 && !block[v] && dist[u] == dist[v] + 1 &&
          (inc = findAugmentingPath(v, min(delta, d)))) {
        e.f += i * inc;
        return inc;
      }
    }
    block[u] = true;
    return 0;
  }
  
public:
  T totalFlow;
  Dinic(Network<T> &g, int s, int t) : g(g), s(s), t(t) {
    g.resetFlow();
    totalFlow = 0;
    dist.resize(g.getSize());
    block.resize(g.getSize());
  }
  T run() {
    while (computeDist()) {
      fill(block.begin(), block.end(), false);
      while (T inc = findAugmentingPath(s, INF))
        totalFlow += inc;
    }
    return totalFlow;
  }
};

#define BASE 300
#define HMOD 100000000000000007LL

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  while (1) {
    int n;
    if (!(cin >> n)) break;
    vector<StringHash<BASE, HMOD>> sh;
    vector<StringHash<BASE, HMOD>> rsh;
    for_inc(i, n) {
      string s;
      cin >> s;
      sh.push_back(StringHasher<BASE, HMOD>::getHash(s.begin(), s.end()));
      rsh.push_back(StringHasher<BASE, HMOD>::getHash(s.rbegin(), s.rend()));
    }
    
    Network<int> g(2 * n + 2);
    int s = n + 1;
    int t = n + 2;
    for_inc_range(i, 1, n) {
      g.addEdge(s, i, 1);
      g.addEdge(n + i, t, 1);
      
    }
    for_inc(i, n) for_inc(j, i) {
      bool good = false;
      if (StringHasher<BASE, HMOD>::getHashValueConcat(rsh[j], rsh[i]) == StringHasher<BASE, HMOD>::getHashValueConcat(sh[i], sh[j])) {
        good = true;
      }
      
      if (!good) {
        good = StringHasher<BASE, HMOD>::getHashValueConcat(rsh[i], rsh[j]) == StringHasher<BASE, HMOD>::getHashValueConcat(sh[j], sh[i]);
      }
      
      if (good) {
        //LOG(1, i + 1 << " " << j + 1);
        g.addEdge(j + 1, n + i + 1, 1);
        g.addEdge(i + 1, n + j + 1, 1);
      }
    }
    Dinic<int> dinic(g, s, t);
    int maxFlow = dinic.run();
    cout << n - maxFlow / 2 << endl;
  }
  return 0;
}
