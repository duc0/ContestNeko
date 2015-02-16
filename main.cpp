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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n;

#define MAXN 100100

#define MOD 1000000007

// Cay co trong so, vo huong
struct weighted_tree {
  vector< vector< pair<int, int> > > adj;
  
  // pi [u] = nut cha cua not u va trong so
  vector< pair<int, int > > pi;
  
  // depth[u] = do sau cua nut u
  vector< int > depth;
  
  int n;
  int root;
  
  void reset(int n) {
    this->n = n;
    adj.resize(n);
    for (int i = 0; i < n; ++i) {
      adj[i].clear();
    }
    pi.resize(n);
    depth.resize(n);
    for (int i = 0; i < n; ++i) {
      pi[i] = make_pair(-1, -1);
      depth[i] = 0;
    }
  }
  
  weighted_tree() {}
  
  weighted_tree(int n) {
    reset(n);
  }
  
  // dfs de tao mang pi
  void dfs(int u) {
    for (int i = 0; i < adj[u].size(); ++i) {
      int v = adj[u][i].first;
      int c = adj[u][i].second;
      if (pi[v].first == -1) {
        pi[v] = make_pair(u, c);
        depth[v] = depth[u] + 1;
        dfs(v);
      }
    }
  }
  
  // dat goc cua cay va dfs
  void set_root(int u) {
    root = u;
    pi[root].first = -2;
    dfs(root);
  }
  
  void add_edge(int u, int v, int c) {
    adj[u].push_back(make_pair(v, c));
    adj[v].push_back(make_pair(u, c));
  }
  
  
};

#define INF 1000000000

// Cau truc ho tro truy van tim nut cha chung trong thoi gian O(logn)
struct lca {
  // anc [i][j] = to tien cach 2^j cua nut i
  // va trong so nho nhat tren duong di i -> to tien 2^j
  // (co the thay bang thong tin khac tuy theo bai
  // ; sua lai cong thuc cua anc.second)
  vector< vector< pair<int, int> > > anc;
  weighted_tree &t;
  
  lca(weighted_tree &tree):t(tree) {
    anc.resize(t.n);
    for (int i = 0 ; i < t.n; ++i) {
      if (i != t.root) {
        anc[i].push_back(t.pi[i]);
      }
    }
    for (int k = 1; ; ++k) {
      bool ok = false;
      for (int i = 0; i < t.n; ++i) {
        if (anc[i].size() >= k) {
          int j = anc[i][k-1].first;
          if (anc[j].size() >= k) {
            int x = anc[j][k-1].first;
            int c = min(anc[i][k-1].second, anc[j][k-1].second);
            anc[i].push_back(make_pair(x, c));
            ok = true;
          }
        }
      }
      if (!ok) break;
    }
  }
  
  pair<int, int> get_lca(int u, int v) {
    //    cout << u+1 << " " << v+1 << " " << t.depth[u] << " " << t.depth[v] << endl;
    if (t.depth[u] > t.depth[v]) {
      swap(u, v);
    }
    if (t.depth[v] > t.depth[u]) {
      for (int i = (int) anc[v].size()-1; i >=0 ; --i) {
        int w = anc[v][i].first;
        if (t.depth[w] >= t.depth[u]) {
          pair<int ,int> p = get_lca(u, w);
          p.second = min(anc[v][i].second, p.second);
          return p;
        }
      }
    } else { // depth[v] == depth[u]
      if (u == v) {
        return make_pair(u, INF);
      }
      for (int i = (int) anc[u].size()-1; i >=0 ; --i) {
        int x = anc[u][i].first;
        int y = anc[v][i].first;
        if (x != y || i == 0) {
          pair<int ,int> p = get_lca(x, y);
          p.second = min(anc[u][i].second, p.second);
          p.second = min(anc[v][i].second, p.second);
          return p;
        }
      }
    }
    return make_pair(-1, -1);
  }
};

bool visit[MAXN];

weighted_tree tree;
int sumWeight[MAXN]; // sum weight from root

int cntNode[MAXN];
int sumDist[MAXN];
int sumSqrDist[MAXN]; // sum sqr dist from u to all nodes in subtree root u

int sumAllSqrDist[MAXN]; // sum sqr dist from u to all other nodes
int sumAllDist[MAXN]; // sum dist from u to all other nodes

int getDistInc(int w, int v) {
  return ((int64)cntNode[v] * w + sumDist[v]) % MOD;
}

int getSqrDistInc(int w, int v) {
  int sqrDistInc = ((int64)w * w) % MOD;
  sqrDistInc = ((int64)sqrDistInc * cntNode[v]) % MOD;
  sqrDistInc = (sqrDistInc + (int64) 2 * w * sumDist[v]) % MOD;
  sqrDistInc = (sqrDistInc + sumSqrDist[v]) % MOD;
  return sqrDistInc;
}

void dfs(int u) {
  visit[u] = true;
  cntNode[u] = 1;
  sumDist[u] = 0;
  sumSqrDist[u] = 0;
  
  for (auto &e : tree.adj[u]) {
    int v = e.first, w = e.second;
    if (v != tree.pi[u].first && !visit[v]) {
      sumWeight[v] = (sumWeight[u] + w) % MOD;      
      dfs(v);
      cntNode[u] += cntNode[v];
      sumDist[u] = (sumDist[u] + getDistInc(w, v)) % MOD;
      sumSqrDist[u] = (sumSqrDist[u] + getSqrDistInc(w, v)) % MOD;
    }
  }
}

void dfsSumAllDist(int u) {
  visit[u] = true;
  for (auto &e : tree.adj[u]) {
    int v = e.first, w = e.second;
    if (v != tree.pi[u].first && !visit[v]) {
      int nOutside = n - cntNode[v];
      int retSumDist = sumAllDist[u];
      retSumDist = (retSumDist - getDistInc(w, v)) % MOD;
      if (retSumDist < 0) retSumDist += MOD;
      
      int retSumSqrDist = sumAllSqrDist[u];
      retSumSqrDist = (retSumSqrDist - getSqrDistInc(w, v)) % MOD;
      if (retSumSqrDist < 0) retSumSqrDist += MOD;
      int inc = ((int64)w*w) % MOD;
      inc = ((int64)inc * nOutside) % MOD;
      inc = (inc + (int64) 2 * w * retSumDist) % MOD;
      retSumSqrDist = (retSumSqrDist + inc) % MOD;
      
      retSumDist = (retSumDist + (int64)w * nOutside) % MOD;
      retSumDist = (retSumDist + sumDist[v]) % MOD;
      sumAllDist[v] = retSumDist;
      
      retSumSqrDist = (retSumSqrDist + sumSqrDist[v]) % MOD;
      sumAllSqrDist[v] = retSumSqrDist;
      
      dfsSumAllDist(v);
    }
  }
}

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  scanf("%d", &n);
  tree.reset(n);
  int a, b, c;
  repeat(n - 1) {
    scanf("%d%d%d", &a, &b, &c);
    tree.add_edge(a - 1, b - 1, c);
  }
  tree.set_root(1 - 1);
  fill0(visit);
  sumWeight[1 - 1] = 0;
  dfs(1 - 1);
  
  fill0(visit);
  sumAllSqrDist[1 - 1] = sumSqrDist[1 - 1];
  sumAllDist[1 - 1] = sumDist[1 - 1];
  dfsSumAllDist(1 - 1);
  
  /*cout << cntNode[1 - 1] << endl;
  cout << sumDist[1 - 1] << endl;
  cout << sumDist[3 - 1] << endl;
  cout << sumSqrDist[1 - 1] << endl;
  cout << sumSqrDist[4 - 1] << endl;
  cout << sumAllDist[3 - 1] << endl;
  cout << sumAllSqrDist[5 - 1] << endl;*/
  
  lca tree_lca(tree);
  int q;
  scanf("%d", &q);
  int u, v;
  repeat(q) {
    scanf("%d%d", &u, &v);
    int ret;
    u--; v--;
    if (u == v) {
      ret = (2 * sumSqrDist[u] - sumAllSqrDist[u]) % MOD;
      if (ret < 0) ret += MOD;
    } else {
      int x = tree_lca.get_lca(u, v).first;
      if (x == v) {
        int w = (sumWeight[u] - sumWeight[v]) % MOD;
        if (w < 0) w+=MOD;
        
        int nOutside = n - cntNode[v];
        ret = 0;
        ret = (sumAllSqrDist[v] - sumSqrDist[v]) % MOD;
        if (ret < 0) ret += MOD;
        
        int retSumDist = (sumAllDist[v] - sumDist[v]) % MOD;
        if (retSumDist < 0) retSumDist += MOD;
        
        int inc = ((int64)w*w) % MOD;
        inc = ((int64)inc * nOutside) % MOD;
        inc = (inc + (int64) 2 * w * retSumDist) % MOD;
        
        ret = (ret + inc) % MOD;
        ret = (sumAllSqrDist[u] - 2 * ret) % MOD;
        if (ret < 0) ret += MOD;
      } else {
        int w = (sumWeight[u] - sumWeight[x]) % MOD;
        if (w < 0) w+=MOD;
        w = (w + sumWeight[v] - sumWeight[x]) % MOD;
        if (w < 0) w+=MOD;
        
        int inc = ((int64)w*w) % MOD;
        inc = ((int64)inc * cntNode[v]) % MOD;
        inc = (inc + (int64) 2 * w * sumDist[v]) % MOD;
        ret = (sumSqrDist[v] + inc) % MOD;
        ret = (2 * ret - sumAllSqrDist[u]) % MOD;
        if (ret < 0) ret += MOD;
      }
    }
    cout << ret << endl;
  }
  
  return 0;
}