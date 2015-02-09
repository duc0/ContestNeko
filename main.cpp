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
#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
#define INT64_INF 2E18L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

struct t_edge {
  int u, v, c, f;
  t_edge(int u, int v, int c, int f):u(u),v(v),c(c),f(f){}
};

struct network {
  int n;
  vector <vector <int> > a;
  vector <t_edge> e;
  int s, t, total_f;
  
  void reset(int n) {
    this->n = n;
    e.clear();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
      a[i].clear();
    }
    total_f = 0;
  }
  
  network() {}
  network(int n) { reset(n); }
  
  void add_edge(int u, int v, int c) {
    e.push_back(t_edge(u, v, c, 0));
    a[u].push_back((int)e.size() - 1);
    a[v].push_back((int)e.size() - 1);
  }
  
  t_edge & get_edge(int i) {return e[i];}
  void set_source(int s) { this->s = s; }
  void set_sink(int t) { this->t = t; }
  inline int source() {return s;}
  inline int sink() {return t;}
  
  int get_flow_value() {
    return total_f;
  }
};

struct edmonds_karp {
  vector<int> pre;
  vector<int> minc;
  
  bool find_aug_path(network &g) {
    queue<int> q;
    q.push(g.s);
    
    pre.resize(g.n);
    for (int u = 0; u < g.n; ++u) pre[u] = -1;
    pre[g.s] = -2;
    
    minc.resize(g.n);
    minc[g.s]=INT_INF;
    
    while (!q.empty()) {
      int u=q.front();
      q.pop();
      for (int i = 0; i < g.a[u].size(); ++i) {
        int t = g.a[u][i];
        t_edge & e = g.e[t];
        if (e.v == u) {
          if (pre[e.u] == -1 && e.f > 0) {
            minc[e.u] = min(minc[u], e.f);
            pre[e.u] = t;
            q.push(e.u);
            if (e.u == g.t) return 1;
          }
        } else {
          if (pre[e.v] == -1 && e.f < e.c) {
            minc[e.v] = min(minc[u], e.c - e.f);
            pre[e.v] = t;
            q.push(e.v);
            if (e.v == g.t) return 1;
          }
        }
      }
    }
    return 0;
  }
  
  void inc_flow(network &g) {
    int d = minc[g.t];
    int v = g.t;
    while (v != g.s) {
      t_edge & e = g.e[pre[v]];
      if (e.v == v) {
        e.f += d;
        v = e.u;
      } else {
        e.f -= d;
        v = e.v;
      }
    }
    g.total_f += d;
  }
  
  edmonds_karp(network &g) {
    while (find_aug_path(g)) {
      inc_flow(g);
    }
  }
  
  bool in_cut_s(int u) {
    return pre[u] != -1;
  }
};

#define MAXN 23
#define MAXS MAXN*MAXN

#define MALE 0
#define FEMALE 1

char board[MAXN][MAXN];

int row[2][MAXS], col[2][MAXS], speed[2][MAXS];

int nRow, nCol, nMale, nFemale;

int dist[MAXN][MAXN][MAXN][MAXN];

#define REPROW(x) for (int x = 0; x < nRow; ++x)
#define REPCOL(x) for (int x = 0; x < nCol; ++x)

#define REPMALE(x) for (int x = 0; x < nMale; ++x)
#define REPFEMALE(x) for (int x = 0; x < nFemale; ++x)

int squareID[MAXN][MAXN], nSquare = 0;
int64 best[2][MAXS][MAXN][MAXN];

#define REPSQUARE(x) for (int x = 0; x < nSquare; ++x)

// TEMP
int idCount[2];
void addScay(int type, int r, int c, int t) {
  r--;
  c--;
  row[type][idCount[type]] = r;
  col[type][idCount[type]] = c;
  speed[type][idCount[type]] = t;
  idCount[type]++;
}

#define MALENODE(x) x
#define FEMALENODE(x) (nMale + x)
#define SQUARENODEIN(x) (nMale + nFemale + x)
#define SQUARENODEOUT(x) (nMale + nFemale + nSquare + x)

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
  cin >> nRow >> nCol >> nMale >> nFemale;
  if ((nMale + nFemale) % 2 == 0) {
    cout << -1;
    return 0;
  }
  if (abs(nMale - nFemale) >= 2) {
    cout << -1;
    return 0;
  }
  REPROW(i) {
    cin >> board[i];
    assert(strlen(board[i]) == nCol);
  }
  idCount[MALE] = idCount[FEMALE] = 0;
  int r, c, t;
  cin >> r >> c >> t;
  if (nMale == nFemale + 1) {
    addScay(FEMALE, r, c, t);
  } else {
    addScay(MALE, r, c, t);
  }
  for (int i = 0; i < nMale; ++i) {
    cin >> r >> c >> t;
    addScay(MALE, r, c, t);
  }
  for (int i = 0; i < nFemale; ++i) {
    cin >> r >> c >> t;
    addScay(FEMALE, r, c, t);
  }
  if (nMale == nFemale + 1) {
    nFemale++;
  } else {
    nMale++;
  }
  
  REPROW(r) REPCOL(c) REPROW(r2) REPCOL(c2) {
    dist[r][c][r2][c2] = INT_INF;
    if (r2 == r && c2 == c) {
      dist[r][c][r2][c2] = 0;
    } else if (abs(r2 - r) + abs(c2 - c) == 1) {
      if (board[r][c] != '#' && board[r2][c2] != '#') {
        dist[r][c][r2][c2] = 1;
      }
    }
  }
  
  REPROW(rk) REPCOL(ck) REPROW(r) REPCOL(c) REPROW(r2) REPCOL(c2) {
    int d1 = dist[r][c][rk][ck];
    int d2 = dist[rk][ck][r2][c2];
    if (d1 != INT_INF && d2 != INT_INF) {
      dist[r][c][r2][c2] = min (dist[r][c][r2][c2], d1 + d2);
    }
  }
  
  
  int64 maxTime = -INT64_INF;
  REPMALE(m) REPFEMALE(f) {
    REPROW(r) REPCOL(c) {
      REPMALE(m) {
        best[MALE][m][r][c] = INT64_INF;
        int dMale = dist[r][c][row[MALE][m]][col[MALE][m]];
        if (dMale != INT_INF) {
          int64 timeMale = (int64)dMale * speed[MALE][m];
          best[MALE][m][r][c] = timeMale;
          maxTime = max(maxTime, timeMale);
        }
      }
      
      REPFEMALE(f) {
        best[FEMALE][f][r][c] = INT64_INF;
        int dFemale = dist[r][c][row[FEMALE][f]][col[FEMALE][f]];
        if (dFemale != INT_INF) {
          int64 timeFemale = (int64)dFemale * speed[FEMALE][f];
          best[FEMALE][f][r][c] = timeFemale;
          maxTime = max(maxTime, timeFemale);
        }
      }
    }
  }
  
  REPROW(r) REPCOL(c) {
    if (board[r][c] == '.') {
      squareID[r][c] = nSquare;
      nSquare++;
    }
  }
  
  int64 left = 0, right = maxTime, mid, ret = -1;
  while (left <= right) {
    mid = (left + right) / 2;

    int nNode = nMale + nFemale + 2 * nSquare + 2;
    network g(nNode);
    g.set_source(nNode - 2);
    g.set_sink(nNode - 1);
    REPMALE(m) {
      g.add_edge(g.source(), MALENODE(m), 1);
    }
    REPFEMALE(f) {
      g.add_edge(FEMALENODE(f), g.sink(), 1);
    }
    REPSQUARE(x) {
      g.add_edge(SQUARENODEIN(x), SQUARENODEOUT(x), 1);
    }
    
    REPMALE(m) REPROW(r) REPCOL(c) {
      if (best[MALE][m][r][c] != INT64_INF && best[MALE][m][r][c] <= mid) {
        g.add_edge(MALENODE(m), SQUARENODEIN(squareID[r][c]), 1);
      }
    }
    
    REPFEMALE(f) REPROW(r) REPCOL(c) {
      if (best[FEMALE][f][r][c] != INT64_INF && best[FEMALE][f][r][c] <= mid) {
        g.add_edge(SQUARENODEOUT(squareID[r][c]), FEMALENODE(f), 1);
      }
    }
    
    edmonds_karp maxflow(g);
    int bestMatch = g.get_flow_value();
    if (bestMatch == nMale) {
      ret = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  
  cout << ret << endl;
  
    
  return 0;
}