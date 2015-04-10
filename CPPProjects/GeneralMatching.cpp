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
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0)
    r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  int n = 1000;
  cout << n << endl;
  repeat(n) {
    repeat(1000) {
      cout << (char)(rand() % 1 + 'a');
    }
    cout << endl;
  }
  fclose(stdout);
}

template <int BASE, int64 MODULO> class StringHash {
  template <int B, int64 M> friend class StringHasher;
  vector<int64> hash;
  
public:
  size_t getSize() const { return hash.size(); }
};

template <int BASE, int64 MODULO> class StringHasher {
  static int64 getBasePower(int n) {
    static vector<int64> power; // cache
    if (n > (int)power.size() - 1) {
      int cur = (int)power.size() - 1;
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
  template <class Iterator>
  static StringHash<BASE, MODULO> getHash(Iterator begin, Iterator end) {
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
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh, int first,
                            int len) {
    if (len == 0) return 0;
    assert(0 <= first && first < sh.getSize());
    assert(len >= 1);
    assert(first + len - 1 < sh.getSize());
    
    int last = first + len - 1;
    
    if (first == 0)
      return sh.hash[last];
    
    int64 ret =
    (sh.hash[last] - sh.hash[first - 1] * getBasePower(len)) % MODULO;
    if (ret < 0)
      ret += MODULO;
    return ret;
  }
  
  static int64 getHashValueConcat(const StringHash<BASE, MODULO> &sh1,
                                  const StringHash<BASE, MODULO> &sh2) {
    
    return (getHashValue(sh1) * getBasePower((int)sh2.getSize()) +
            getHashValue(sh2)) %
    MODULO;
  }
};

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

// Edmonds O(V(V+E))
class MaximumMatching {
  const UndirectedGraph &g;
  vector<int> match;
  vector<int> p;
  int nMatch;
  int n;
  
  int lca(const vector<int> &base, int a, int b) {
    vector<bool> used(match.size());
    while (true) {
      a = base[a];
      used[a] = true;
      if (match[a] == -1) break;
      a = p[match[a]];
    }
    while (true) {
      b = base[b];
      if (used[b]) return b;
      b = p[match[b]];
    }
  }
  
  void markPath(const vector<int> &base, vector<bool> &blossom, int v, int b, int children) {
    for (; base[v] != b; v = p[match[v]]) {
      blossom[base[v]] = blossom[base[match[v]]] = true;
      p[v] = children;
      children = match[v];
    }
  }
  
  int findPath(int root) {
    vector<bool> used(n + 1);
    vector<int> base(n + 1);
    for_inc_range(u, 1, n) {
      p[u] = -1;
      base[u] = u;
    }
    used[root] = true;
    
    int qh = 0;
    int qt = 0;
    vector<int> q(n);
    q[qt++] = root;
    while (qh < qt) {
      int v = q[qh++];
      for (int to : g.getAdjacent(v)) {
        if (base[v] == base[to] || match[v] == to) continue;
        if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
          int curbase = lca(base, v, to);
          vector<bool> blossom = vector<bool>(n + 1);
          markPath(base, blossom, v, curbase, to);
          markPath(base, blossom, to, curbase, v);
          for_inc_range(i, 1, n) {
            if (blossom[base[i]]) {
              base[i] = curbase;
              if (!used[i]) {
                used[i] = true;
                q[qt++] = i;
              }
            }
          }
        } else if (p[to] == -1) {
          p[to] = v;
          if (match[to] == -1)
            return to;
          to = match[to];
          used[to] = true;
          q[qt++] = to;
        }
      }
    }
    return -1;
  }
  
public:
  MaximumMatching(const UndirectedGraph &g): g(g) {
    n = g.getSize();
    match.resize(n + 1);
    for_inc_range(u, 1, n) match[u] = -1;
    p.resize(n + 1);
    for_inc_range(u, 1, n) {
      if (match[u] == -1) {
        int v = findPath(u);
        while (v != -1) {
          int pv = p[v];
          int ppv = match[pv];
          match[v] = pv;
          match[pv] = v;
          v = ppv;
        }
      }
    }
    
    nMatch = 0;
    for_inc_range(u, 1, n) {
      if (match[u] != -1) {
        ++nMatch;
      }
    }
  }
  
  int getMaximumMatchingSize() const {
    return nMatch;
  }
};

#define BASE 31
#define HMOD 1000001927

char s[1010];

// Hackerrank cisco 2015, joining byte blocks
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  while (1) {
    int n;
    if (scanf("%d", &n) != 1) {
      break;
    }
    vector<StringHash<BASE, HMOD>> sh;
    vector<StringHash<BASE, HMOD>> rsh;
    for_inc(i, n) {
      scanf("%s", s);
      string cs(s);
      vector<int> ss(cs.size());
      for_inc(k, cs.size()) {
        ss[k] = cs[k] - 'a';
      }
      sh.push_back(StringHasher<BASE, HMOD>::getHash(ss.begin(), ss.end()));
      rsh.push_back(StringHasher<BASE, HMOD>::getHash(ss.rbegin(), ss.rend()));
    }
    
    UndirectedGraph g;
    g.init(n);
    for_inc(i, n) for_inc(j, i) {
      bool good = false;
      if (StringHasher<BASE, HMOD>::getHashValueConcat(rsh[j], rsh[i]) ==
          StringHasher<BASE, HMOD>::getHashValueConcat(sh[i], sh[j])) {
        good = true;
      }
      
      if (!good) {
        good = StringHasher<BASE, HMOD>::getHashValueConcat(rsh[i], rsh[j]) ==
        StringHasher<BASE, HMOD>::getHashValueConcat(sh[j], sh[i]);
      }
      
      if (good) {
        // LOG(1, i + 1 << " " << j + 1);
        g.addEdge(i + 1, j + 1);
      }
    }
    
    
    MaximumMatching matching(g);
    
    cout << n - matching.getMaximumMatchingSize() / 2<< endl;
    
  }
  return 0;
}
