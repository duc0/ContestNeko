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
vector<vector<int>> child;

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
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
  child.resize(n);
  for_inc(i, n) {
    x = points[i].first;
    y = points[i].second;
    
    deg[i] = 0;
    if (idx.count(make_pair(x - 1, y + 1))) {
      ++deg[i];
    }
    if (idx.count(make_pair(x, y + 1))) {
      ++deg[i];
    }
    if (idx.count(make_pair(x + 1, y + 1))) {
      ++deg[i];
    }
    
    pair<int, int> p;
    p = make_pair(x - 1, y - 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }
    p = make_pair(x, y - 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }
    p = make_pair(x + 1, y - 1);
    if (idx.count(p)) {
      child[i].push_back(idx[p]);
    }
  }
  
  set<int> freeNode;
  for_inc(i, n) {
    if (deg[i] == 0) {
      freeNode.insert(i);
    }
  }
  
  int64 ret = 0;
  bool turn = true;
  while (!freeNode.empty()) {
    int u;
    if (turn) {
      u = *(--freeNode.end());
    } else {
      u = *freeNode.begin();
    }
    turn = !turn;
    
    //LOG(1, u);
    ret = MODP(ret * n + u);
    
    freeNode.erase(u);
    for (auto &v: child[u]) {
      deg[v]--;
      if (deg[v] == 0) {
        freeNode.insert(v);
      }
    }
  }
  
  cout << ret << endl;
  return 0;
}
