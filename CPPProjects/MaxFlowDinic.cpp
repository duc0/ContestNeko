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
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)
#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
#define INT64_INF 2E18L

void testGen() {
  freopen("biginput2.txt", "w", stdout);
  int n = 14;
  cout << n << " " << n << " " << n *n << " " << n *n - 1 << endl;
  repeat(n) {
    repeat(n) { cout << "."; }
    cout << endl;
  }
  repeat(2 * n * n) { cout << 1 << " " << 1 << " " << 1 << endl; }
  fclose(stdout);
}

template <class T> class Network {
  struct Edge {
    int u, v;
    T f, c;
  };
  vector<Edge> edgeList;
  vector<vector<int>> adj;
  
public:
  vector<int> &getAdjacent(int u) { return adj[u]; }
  
  Edge &getEdge(int i) { return edgeList[i]; }
  
  void addEdge(int u, int v, T c) {
    Edge e = {u, v, 0, c};
    adj[u].push_back((int)edgeList.size());
    adj[v].push_back((int)edgeList.size());
    edgeList.push_back(e);
  }
  size_t getSize() { return adj.size(); }
  void resetFlow() {
    for (auto &pe : edgeList)
      pe.f = 0;
  }
  void init(int n) {
    edgeList.clear();
    adj.resize(n);
    for (auto &au : adj)
      au.clear();
  }
  Network(int n) { init(n); }
};

template <class T> class Dinic {
  Network<T> &g;
  int s, t;
  vector<T> dist;
  vector<bool> block;
  const T INF = numeric_limits<T>::max() / 2;
  
  bool computeDist() {
    queue<int> q;
    q.push(t);
    fill(dist.begin(), dist.end(), -1);
    dist[t] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto pi : g.getAdjacent(u)) {
        auto &e = g.getEdge(pi);
        int v = -1;
        if (e.v == u && e.f < e.c)
          v = e.u;
        else if (e.u == u && e.f > 0)
          v = e.v;
        if (v != -1 && dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
          if (v == s)
            return true;
        }
      }
    }
    return dist[s] != -1;
  }
  T findAugmentingPath(int u, T delta) {
    if (u == t)
      return delta;
    T inc;
    for (auto pi : g.getAdjacent(u)) {
      auto &e = g.getEdge(pi);
      int v = -1, i = 0, d = 0;
      if (e.u == u && e.f < e.c) {
        v = e.v;
        i = 1;
        d = e.c - e.f;
      } else if (e.v == u && e.f > 0) {
        v = e.u;
        i = -1;
        d = e.f;
      }
      if (v != -1 && !block[v] && dist[u] == dist[v] + 1 &&
          (inc = findAugmentingPath(v, min(delta, d)))) {
        e.f += i * inc;
        return inc;
      }
    }
    block[u] = true;
    return 0;
  }
  
public:
  T totalFlow;
  Dinic(Network<T> &g, int s, int t) : g(g), s(s), t(t) {
    g.resetFlow();
    totalFlow = 0;
    dist.resize(g.getSize());
    block.resize(g.getSize());
  }
  T run() {
    while (computeDist()) {
      fill(block.begin(), block.end(), false);
      while (T inc = findAugmentingPath(s, INF))
        totalFlow += inc;
    }
    return totalFlow;
  }
};

// Sample problem: Rockethon 2015 - problem F

#define MAXN 23
#define MAXS MAXN *MAXN

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
  // testGen();
  freopen("biginput2.txt", "r", stdin);
  
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
      dist[r][c][r2][c2] = min(dist[r][c][r2][c2], d1 + d2);
    }
  }
  
  int64 maxTime = -INT64_INF;
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
    Network<int> g(nNode);
    int source = nNode - 2;
    int sink = nNode - 1;
    REPMALE(m) { g.addEdge(source, MALENODE(m), 1); }
    REPFEMALE(f) { g.addEdge(FEMALENODE(f), sink, 1); }
    REPSQUARE(x) { g.addEdge(SQUARENODEIN(x), SQUARENODEOUT(x), 1); }
    
    REPMALE(m) REPROW(r) REPCOL(c) {
      if (best[MALE][m][r][c] != INT64_INF && best[MALE][m][r][c] <= mid) {
        g.addEdge(MALENODE(m), SQUARENODEIN(squareID[r][c]), 1);
      }
    }
    
    REPFEMALE(f) REPROW(r) REPCOL(c) {
      if (best[FEMALE][f][r][c] != INT64_INF && best[FEMALE][f][r][c] <= mid) {
        g.addEdge(SQUARENODEOUT(squareID[r][c]), FEMALENODE(f), 1);
      }
    }
    
    int bestMatch = Dinic<int>(g, source, sink).run();
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