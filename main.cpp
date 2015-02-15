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
#include <queue>

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)

#define for_inc(i,x) for(auto i=0; i < x;++i)
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
#define for_inc_range(i,x,y) for (auto i=x; i<=y; ++i)
#define for_dec_range(i,x,y) for (auto i=x; i>=y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

struct Network {
  struct Edge {int u, v; ntype f, c;};
  vector<Edge> edgeList;
  vector<vector<int> > adj;
  void addEdge(int u, int v, ntype c) {
    Edge e={u,v,0,c};
    adj[u].push_back((int)edgeList.size());
    adj[v].push_back((int)edgeList.size());
    edgeList.push_back(e);
  }
  int n(){return (int)adj.size();}
  void resetFlow() {
    for (auto &pe : edgeList) pe.f=0;
  }
  void init(int n) {
    edgeList.clear();
    adj.resize(n);
    for (auto &au : adj) au.clear();
  }
  Network(int n){init(n);}
};

class Dinic {
  Network &g;
  int s, t;
  vector<ntype> dist;
  vector<bool> block;
  bool computeDist() {
    queue<int> q;
    q.push(t);
    fill(dist.begin(),dist.end(),-1);
    dist[t]=0;
    while (!q.empty()) {
      int u=q.front();
      q.pop();
      for (auto pi : g.adj[u]) {
        Network::Edge &e=g.edgeList[pi];
#define CONSIDER(v) {if (dist[v]==-1) {dist[v]=dist[u]+1; q.push(v); if (v==s) return true;}}
        if (e.v==u && e.f<e.c) CONSIDER(e.u) else if (e.u==u && e.f>0) CONSIDER(e.v)
#undef CONSIDER
          }
    }
    return dist[s]!=-1;
  }
  ntype findAugmentingPath(int u, ntype delta) {
    if (u==t) return delta;
    ntype inc;
    for (auto pi : g.adj[u]){
      Network::Edge &e=g.edgeList[pi];
#define CONSIDER(v,i,d) {if (!block[v] && dist[u]==dist[v]+1 && (inc=findAugmentingPath(v,min(delta,d)))) {e.f+=i*inc; return inc;}}
      if (e.u==u && e.f<e.c) CONSIDER(e.v,1,e.c-e.f) else if (e.v==u && e.f>0) CONSIDER(e.u,-1,e.f)
#undef CONSIDER
        }
    block[u]=true;
    return 0;
  }
public:
  ntype totalFlow;
  Dinic(Network &g, int s, int t):g(g),s(s),t(t){
    g.resetFlow();
    totalFlow=0;
    dist.resize(g.n());
    block.resize(g.n());
  }
  ntype run () {
    while (computeDist()) {
		    fill(block.begin(), block.end(), false);
		    while (ntype inc = findAugmentingPath(s, N_INF)) totalFlow += inc;
    }
    return totalFlow;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  
  cout << 100 << " " << 100 << endl;
  repeat(100) {
    cout << 1000000000 << " ";
  }
  cout << endl;
  int i = 1;
  repeat(99) {
    cout << i << " " << i + 1 << endl;
    i++;
  }
  cout << 1 << " " << 3 << endl;
  fclose(stdout);
}

#define MAXN 110

vector<pair<int, int>> factor(int n) {
  vector<pair<int, int>> ret;
  int p = 2;
  while (p*p <= n) {
    int c = 0;
    while (n % p == 0) {
      n/=p;
      c++;
    }
    if (c > 0) {
      ret.push_back(make_pair(p, c));
    }
    p++;
  }
  if (n > 1) {
    ret.push_back(make_pair(n, 1));
  }
  return ret;
}

int n, m;
int a[MAXN];

vector<pair<int, int>> primeFactors[MAXN];
int primeDivCount[MAXN];

#define NODE(i,j) (primeDivCount[i-1] + j)
int main() {
  //testGen();
  freopen("input5.txt", "r", stdin);
  
  cin >> n >> m;
  
  primeDivCount[0] = 0;
  for_inc_range(i, 1, n) {
    cin >> a[i];
    primeFactors[i] = factor(a[i]);
    primeDivCount[i] = primeDivCount[i - 1] + (int)primeFactors[i].size();
  }
  
  Network g(primeDivCount[n] + 2);
  int s = primeDivCount[n];
  int t = primeDivCount[n] + 1;
  
  for_inc_range(i, 1, n) {
    for_inc(j, primeFactors[i].size()) {
      if (i % 2 == 0) {
        g.addEdge(s, NODE(i,j), primeFactors[i][j].second);
      } else {
        g.addEdge(NODE(i,j), t, primeFactors[i][j].second);
      }
    }
  }
  
  repeat(m) {
    int u, v;
    cin >> u >> v;
    for_inc(iu, primeFactors[u].size()) {
      for_inc(iv, primeFactors[v].size()) {
        if (primeFactors[u][iu].first == primeFactors[v][iv].first) {
          if (u % 2 == 0) {
            g.addEdge(NODE(u,iu), NODE(v,iv), INT_INF);
          } else {
            g.addEdge(NODE(v,iv), NODE(u,iu), INT_INF);
          }
        }
      }
    }
  }

  int maxFlow = Dinic(g, s, t).run();
  
  cout << maxFlow << endl;
  return 0;
}