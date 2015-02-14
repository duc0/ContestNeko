#include <cstdio>
#include <algorithm>
#include <cstring>

#define NDEBUG
#include <cassert>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <array>
#include <type_traits>

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

void testGen() {
  freopen("biginput2.txt", "w", stdout);
  
  int n=100000, m=100000, q=100000, h = 700;
  cout << n << " " << m << endl;
  repeat(m) {
    int u, v, c;
    u = rand() % h + 1;
    v = rand() % h + 1;
    c = rand() % h + 1;
    cout << u << " " << v << " " << c << endl;
  }
  cout << q << endl;
  repeat(q) {
    int u, v;
    u = rand() % h + 1;
    v = rand() % h + 1;
    cout << u << " " << v << endl;
  }
  fclose(stdout);
}

#define MAXN 100100
#define MAXM 100100

int n, m, q;
vector< vector<pair<int, int> > > edge;
map< pair<int, int>, int > queryMap;
vector<pair<int, int>> query;
vector<vector<int>> adj;

set<int> relatedVSet;
vector<int> relatedV;

bool visit[MAXN];
int comp[MAXN], compCount;

void dfs(int u) {
  visit[u] = true;
  comp[compCount] = u;
  compCount++;
  for (auto &v : adj[u]) {
    if (!visit[v]) {
      dfs(v);
    }
  }
}

int main() {
  //testGen();
  //freopen("biginput2.txt", "r", stdin);
  
  // The algo is simple, but to make sure the worst case complexity is within limit is tricky. It is probably O(msqrt(m)).
  
  scanf("%d%d",&n,&m);
  int u, v, c;
  edge.resize(m + 1);
  repeat(m) {
    scanf("%d%d%d", &u, &v, &c);
    edge[c].push_back(make_pair(u, v));
  }
  
  scanf("%d", &q);
  repeat(q) {
    scanf("%d%d", &u, &v);
    query.push_back(make_pair(u, v));
    queryMap[make_pair(u, v)] = 0;
  }
  
  adj.resize(n + 1);
  for (int color = 1; color <= m; ++color) {
    relatedVSet.clear();
    for (auto &e : edge[color]) {
      relatedVSet.insert(e.first);
      relatedVSet.insert(e.second);
    }
    relatedV.clear();
    for (auto &v: relatedVSet) {
      relatedV.push_back(v);
      visit[v] = false;
      adj[v].clear();
    }
    for (auto &e : edge[color]) {
      adj[e.first].push_back(e.second);
      adj[e.second].push_back(e.first);
    }
    
    for (auto &v: relatedV) {
      compCount = 0;
      dfs(v);
      for (int i = 0; i < compCount; ++i) {
        for (int j = 0; j < compCount; ++j) if (i != j) {
          pair<int, int> e = make_pair(comp[i], comp[j]);
          if (queryMap.count(e)) {
            queryMap[e]++;
          }
        }
      }
    }
  }
  
  for (auto &q: query ) {
    printf("%d\n", queryMap[q]);
  }
  
  return 0;
}