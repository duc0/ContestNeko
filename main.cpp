#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Weighted undirected tree
template <class T> class WeightedTree {
  vector<vector<pair<int, T>>> adj;
  
  // p [u] = parent of u and weight p[u] -> u
  vector<pair<int, T>> p;
  
  vector<int> depth;
  
  int n;
  int root;
  
public:
  vector<pair<int, T>> &getAdjacent(int u) { return adj[u]; }
  
  void reset(int size) {
    this->n = size;
    adj.resize(n + 1);
    for_inc_range(i, 1, n) adj[i].clear();
    p.resize(n + 1);
    depth.resize(n + 1);
    for_inc_range(i, 1, n) {
      p[i] = make_pair(-1, -1);
      depth[i] = 0;
    }
  }
  
  WeightedTree() {}
  
  WeightedTree(int n) { reset(n); }
  
  void dfs(int u) {
    for (auto &e : adj[u]) {
      int v = e.first;
      int c = e.second;
      if (p[v].first == -1) {
        p[v] = make_pair(u, c);
        depth[v] = depth[u] + 1;
        dfs(v);
      }
    }
  }
  
  int getParent(int u) { return p[u].first; }
  
  T getWeight(int u) { return p[u].second; }
  
  int getDepth(int u) { return depth[u]; }
  
  size_t getSize() { return n; }
  
  int getRoot() { return root; }
  
  void setRoot(int u) {
    for_inc_range(v, 1, n) {
      p[v].first = -1;
    }
    root = u;
    p[root].first = -2;
    dfs(root);
  }
  
  void addEdge(int u, int v, int c) {
    adj[u].push_back(make_pair(v, c));
    adj[v].push_back(make_pair(u, c));
  }
};

WeightedTree<int> tree;

vector<int64> dIn, dBest;

void dfs1(int u) {
  dIn[u] = 0;
  for (auto &v: tree.getAdjacent(u)) {
    if (v.first != tree.getParent(u)) {
      dfs1(v.first);
      dIn[u] = max(dIn[u], v.second + dIn[v.first]);
    }
  }
}

void dfs2(int u, int64 dOut) {
  dBest[u] = max(dIn[u], dOut);
  
  int dInBest = -1, dInBest2 = -1;
  for (auto &v: tree.getAdjacent(u)) {
    if (v.first != tree.getParent(u)) {
      if (dInBest == -1 || dIn[dInBest] + tree.getWeight(dInBest) <= dIn[v.first] + v.second) {
        dInBest2 = dInBest;
        dInBest = v.first;
      } else if (dInBest2 == -1 || dIn[dInBest2] + tree.getWeight(dInBest2) < dIn[v.first] + v.second) {
        dInBest2 = v.first;
      }
    }
  }
  
  for (auto &v: tree.getAdjacent(u)) {
    if (v.first != tree.getParent(u)) {
      int64 bestOut = dOut + v.second;
      if (dInBest != -1) {
        if (dInBest != v.first) {
          bestOut = max(bestOut, v.second + dIn[dInBest] + tree.getWeight(dInBest));
        } else if (dInBest2 != -1) {
          bestOut = max(bestOut, v.second + dIn[dInBest2] + tree.getWeight(dInBest2));
        }
      }
      dfs2(v.first, bestOut);
    }
  }
  
}

vector<int> answer, exclude;
int finalAns;
vector<pair<int64, int>> ancestors;

int64 l;
void dfsSolve(int u) {
  int leftIndex = 0, rightIndex = (int)ancestors.size() - 1, mid, final = -1;
  while (leftIndex <= rightIndex) {
    mid = (leftIndex + rightIndex) / 2;
    
    if (dBest[u] - ancestors[mid].first <= l) {
      rightIndex = mid - 1;
    } else {
      final = ancestors[mid].second;
      leftIndex = mid + 1;
    }
  }
  if (final != -1) {
    exclude[final]++;
  }
  
    
  answer[u] = 1;
  exclude[u] = 0;
  ancestors.push_back(make_pair(dBest[u], u));
  for (auto &v: tree.getAdjacent(u)) {
    if (v.first != tree.getParent(u)) {
      assert(dBest[u] <= dBest[v.first]);
      dfsSolve(v.first);
      answer[u] += answer[v.first];
    }
  }
  answer[u] -= exclude[u];
  finalAns = max(finalAns, answer[u]);
  ancestors.pop_back();
}

int main() {
  //freopen("input2.txt", "r", stdin);
 
  int n, x, y, v;
  cin >> n;
  tree.reset(n);
  repeat(n - 1) {
    cin >> x >> y >> v;
    tree.addEdge(x, y, v);
  }
  tree.setRoot(1);
  
  dIn.resize(n + 1);
  dBest.resize(n + 1);
  
  dfs1(tree.getRoot());
  
  dfs2(tree.getRoot(), 0);

  //for_inc_range(i, 1, n) cout << dIn[i] << endl;
  //for_inc_range(i, 1, n) cout << dBest[i] << endl;
  
  int root = -1;
  for_inc_range(u, 1, n) {
    if (root == -1 || dBest[u] < dBest[root]) {
      root = u;
    }
  }
  tree.setRoot(root);
  
  int q;
  cin >> q;
  answer.resize(n + 1);
  exclude.resize(n + 1);
  repeat(q) {
    cin >> l;
    finalAns = 0;
    dfsSolve(tree.getRoot());
    ancestors.clear();
    cout << finalAns << endl;
  }
  
  return 0;
}
