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
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}


// extendedEuclid: tim x, y sao cho ax + by = (a,b)
void extendedEuclid(int a, int b, int &x, int &y) {
  if (b==0) {x=1; y=0; return;}
  int x2;
  extendedEuclid(b,a%b,x2,x);
  y=x2-(a/b)*x;
}

// modulo: tra ve a mod b, nhung ket qua dam bao luon duong
int modulo(int64 a, int b) {
  int r=a%b;
  if (r<0) r+=b;
  return r;
}

// modularInverse: dieu kien (a, m) = 1, tra ve a^-1 sao cho a*(a^-1) = 1 (mod m)
int modularInverse(int a, int m) {
  int x, y;
  extendedEuclid(a, m, x, y);
  return modulo(x,m);
}

int n;
vector<int> parent;
vector<int> color;
vector<vector<int>> child;

vector <vector<int>> f;

void dfs(int u) {
  int prod = 1;
  
  for (auto &v: child[u]) {
    //cout << u << " " << v << endl;
    dfs(v);
    prod = MODP((int64)prod * (f[0][v] + f[1][v]));
  }
  
  f[0][u] = f[0][u] * prod;
  if (color[u] == 1) {
    f[0][u] = 0;
    f[1][u] = prod;
  } else {
    f[0][u] = prod;
    f[1][u] = 0;
    for (auto &v: child[u]) {
      if (f[1][v] > 0) {
        f[1][u] = MODP(f[1][u] + (int64) f[1][v] * MODP((int64)prod * modularInverse(f[0][v] + f[1][v], MOD)));
      }
    }
  }
}

int main() {
  //freopen("input3.txt", "r", stdin);
  cin >> n;
  parent.resize(n + 1);
  child.resize(n + 1);
  color.resize(n + 1);
  parent[1] = -1;
  int p;
  for_inc_range(u, 2, n) {
    cin >> p;
    parent[u] = p + 1;
    child[p + 1].push_back(u);
  }
  for_inc_range(u, 1, n) {
    cin >> color[u];
  }
  
  f.resize(2);
  for_inc_range(i, 0, 1) {
    f[i].resize(n + 1);
  }
  dfs(1);
  cout << f[1][1] << endl;
  
  return 0;
}
