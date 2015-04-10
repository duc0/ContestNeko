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


class BipartiteGraph {
  friend class BipartiteMatching;
  
  vector<vector<int>> adj;
  int nLeft, nRight;
  
  void reset(int nLeft, int nRight) {
    this->nLeft = nLeft;
    this->nRight = nRight;
    adj.resize(nLeft + 1);
    for_inc_range(u, 1, nLeft) adj[u].clear();
  }
  
public:
  BipartiteGraph(int nLeft, int nRight) {
    reset(nLeft, nRight);
  }
  
  void addEdge(int x, int y) {
    assert(1 <= x && x <= nLeft);
    assert(1 <= y && y <= nRight);
    adj[x].push_back(y);
  }
};

// O(V(V+E))
struct BipartiteMatching {
  vector<int> pre;
  vector<int> mx, my;
  int nMatch;
  const BipartiteGraph &g;
  
  bool match(int x) {
    if (x == -1)
      return true;
    for (int y : g.adj[x]) {
      if (pre[y] != -1)
        continue;
      pre[y] = x;
      if (match(my[y])) {
        my[y] = x;
        mx[x] = y;
        return true;
      }
    }
    return false;
  }
  
  void greedyMatch() {
    for_inc_range(x, 1, g.nLeft) {
      if (mx[x] == -1) {
        for (int y : g.adj[x]) {
          if (my[y] == -1) {
            mx[x] = y;
            my[y] = x;
            ++nMatch;
            break;
          }
        }
      }
    }
  }
  
public:
  BipartiteMatching(const BipartiteGraph &g) : g(g) {
    nMatch = 0;
    
    mx.resize(g.nLeft + 1);
    for_inc_range(x, 1, g.nLeft) mx[x] = -1;
    my.resize(g.nRight + 1);
    for_inc_range(y, 1, g.nRight) my[y] = -1;
    pre.resize(g.nRight + 1);
    
    greedyMatch();
    for_inc_range(x, 1, g.nLeft) if (mx[x] == -1) {
      for_inc_range(y, 1, g.nRight) pre[y] = -1;
      if (match(x)) {
        ++nMatch;
      }
    }
  }
  
  int getMaximumMatchingSize() const { return nMatch; }
};

// SPOJ - NKBM
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int nLeft, nRight, m;
  cin >> nLeft >> nRight >> m;
  
  BipartiteGraph g(nLeft, nRight);
  repeat(m) {
    int x, y;
    cin >> x >> y;
    g.addEdge(x, y);
  }
  
  BipartiteMatching matching(g);
  cout << matching.getMaximumMatchingSize() << endl;
  
  return 0;
}
