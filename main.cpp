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

vector<pair<int, int>> points;
map<pair<int, int>, int> idx;
vector<int> deg;
vector<vector<int>> parent, child;

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
  
  deg.resize(n);
  parent.resize(n);
  child.resize(n);
  for_inc(i, n) {
    x = points[i].first;
    y = points[i].second;
    
    pair<int, int> p;
    p = make_pair(x - 1, y + 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }
    p = make_pair(x, y + 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }
    p = make_pair(x + 1, y + 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }

    p = make_pair(x - 1, y - 1);
    if (idx.count(p)) {
      parent[i].push_back(idx[p]);
    }
    p = make_pair(x, y - 1);
    if (idx.count(p)) {
      parent[i].push_back(idx[p]);
    }
    p = make_pair(x + 1, y - 1);
    if (idx.count(p)) {
      parent[i].push_back(idx[p]);
    }
    deg[i] = (int)parent[i].size();
  }
  
  set<int> freeNode;
  for_inc(i, n) {
    bool isFree = true;
    for (auto &v: child[i]) {
      if (deg[v] == 1) {
        isFree = false;
        break;
      }
    }
    if (isFree) {
      freeNode.insert(i);
    }
  }
  
  int64 ret = 0;
  bool turn = true;
  vector<bool> erase;
  erase.resize(n);
  while (!freeNode.empty()) {
    int u;
    if (turn) {
      u = *(--freeNode.end());
    } else {
      u = *freeNode.begin();
    }
    turn = !turn;
    erase[u] = true;
    
    LOG(1, u);
    ret = MODP(ret * n + u);
    
    freeNode.erase(u);
    for (auto &v: child[u]) if (!erase[v]) {
      deg[v]--;
      if (deg[v] == 1) {
        for (auto &w : parent[v]) {
          if (!erase[w]) {
            freeNode.erase(w);
          }
        }
      }
    }
    for (auto &v: parent[u]) if (!erase[v]) {
      bool isFree = true;
      for (auto &w: child[v]) {
        if (!erase[w] && deg[w] == 1) {
          isFree = false;
          break;
        }
      }
      if (isFree) {
        freeNode.insert(v);
      }
    }
  }
  
  cout << ret << endl;
  return 0;
}
