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
    assert(0 <= first && first < sh.getSize());
    assert(len >= 1);
    assert(first + len - 1 < sh.getSize());

    int last = first + len - 1;

    if (first == 0)
      return sh.hash[last];

    int64 ret =
        (sh.hash[last] - sh.hash[first - 1] * getBasePower(len)) % MODULO;
    if (ret < MODULO)
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

// O(V^3)
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

#define BASE 300
#define HMOD 100000000000000007LL

char s[1010];

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("biginput1.txt", "r", stdin);
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
      string ss(s);
      sh.push_back(StringHasher<BASE, HMOD>::getHash(ss.begin(), ss.end()));
      rsh.push_back(StringHasher<BASE, HMOD>::getHash(ss.rbegin(), ss.rend()));
    }

    BipartiteGraph g(n, n);
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
        g.addEdge(j + 1, i + 1);
      }
    }
    BipartiteMatching matching(g);
    cout << matching.getMaximumMatchingSize() / 2 << endl;
  }
  return 0;
}
