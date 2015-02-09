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
#define checkMin(x, y) x = min(x, y)
#define checkMax(x, y) x = max(x, y)

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

#define MAXN 1000100

int n, c;
// No need to store all the constraints, since
// let minL[i] = min(j, j is left of i), maxL[i] = max(j, j is left of i),
// we know that all nodes from minL[i] to maxL[i] should be left of i (due to properties
// of pre-order traversal).
int minL[MAXN], minR[MAXN], maxL[MAXN], maxR[MAXN];

int ret[MAXN];
int cntRet = 0;
int cur = 0;

bool dfs(int u, int m) {
  // Subtree rooted at u should at least have up to node m
  
  cur++;
  assert(cur == u);
  
  if (minL[u] != 0) {
    // Go left
    // We don't care about m when going to the left subtree
    if (!dfs(cur + 1, maxL[u])) {
      return false;
    }
  }
  ret[cntRet] = u;
  cntRet++;
  if (minR[u] != 0 && cur + 1 > minR[u]) {
    return false;
  }
  // Go right, we need to build up to m if maxR[u] < m
  int t = max(maxR[u], m);
  if (t >= cur + 1) {
    if (!dfs(cur + 1, t)) {
      return false;
    }
  }
  
  return true;
}

int main() {
  //testGen();
  //freopen("input5.txt", "r", stdin);
  
  cin >> n >> c;
  int a, b;
  string s;
  repeat(c) {
    cin >> a >> b >> s;
    if (a >= b) {
      cout << "IMPOSSIBLE";
      return 0;
    }
    if (s[0] == 'L') {
      if (minL[a] == 0) {
        minL[a] = b;
        maxL[a] = b;
      } else {
        checkMin(minL[a], b);
        checkMax(maxL[a], b);
      }
    } else {
      if (minR[a] == 0) {
        minR[a] = b;
        maxR[a] = b;
      } else {
        checkMin(minR[a], b);
        checkMax(maxR[a], b);
      }
    }
  }
  
  if (!dfs(1, n)) {
    cout << "IMPOSSIBLE";
  } else {
    for (int i = 0; i < n; ++i) {
      cout << ret[i] << " ";
    }
  }
  
  return 0;
}