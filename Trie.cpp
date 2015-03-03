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

template <class T> class Trie {
  vector<vector<pair<int, T>>> child;
  int root;
  int n;
  
public:
  Trie() {
    reset();
  }
  void reset() {
    child.clear();
    child.push_back({});
    root = 0;
    n = 1;
  }
  
  const vector<pair<int, T>>& getChild(int u) const {
    return child[u];
  }
  
  template<class Iterator> void addWord(Iterator begin, Iterator end) {
    int curNode = root;
    for (auto it = begin; it != end; ++it) {
      T c = *it;
      bool found = false;
      for (auto &v: child[curNode]) {
        if (v.second == c) {
          curNode = v.first;
          found = true;
          break;
        }
      }
      if (!found) {
        ++n;
        child.push_back({});
        child[curNode].push_back(make_pair(n - 1, c));
        curNode = n - 1;
      }
    }
  }
  
  int getRoot() const {
    return root;
  }
  
  int getSize() const {
    return n;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

Trie<char> trie;

vector<bool> win;
vector<bool> lose;

void dfs(int u) {
  win[u] = false;
  if (trie.getChild(u).size() == 0) {
    lose[u] = true;
  } else {
    lose[u] = false;
  }
  for (auto &v: trie.getChild(u)) {
    LOG(1, "Edge " << u << " " << v.first << " " << v.second);
    dfs(v.first);
    if (!win[v.first]) {
      win[u] = true;
    }
    if (!lose[v.first]) {
      lose[u] = true;
    }
  }
}

// Sample: CF260_div2_D
int main() {
#ifndef SUBMIT
  freopen("input5.txt", "r", stdin);
#endif
  
  int n, k;
  cin >> n >> k;
  repeat(n) {
    string s;
    cin >> s;
    trie.addWord(s.begin(), s.end());
  }
  LOG(1, trie.getSize());
  win.resize(trie.getSize());
  lose.resize(trie.getSize());
  dfs(trie.getRoot());
  bool canWin = win[trie.getRoot()];
  bool canLose = lose[trie.getRoot()];
  if (canWin) {
    if (canLose) {
      cout << "First";
    } else if (k % 2 == 1) {
      cout << "First";
    } else {
      cout << "Second";
    }
  } else {
    cout << "Second";
  }
  return 0;
}
