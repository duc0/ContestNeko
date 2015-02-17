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

int main() {
  //testGen();
  //freopen("input2.txt", "r", stdin);
  
  int n, a, b;
  vector<pair<int, int>> s;
  cin >> n;
  repeat(n) {
    cin >> a >> b;
    s.push_back(make_pair(a, b));
  }
  
  int curDay = 0;
  sort(s.begin(), s.end());
  
  for (auto &p : s) {
    if (p.second >= curDay) {
      curDay = p.second;
    } else {
      curDay = p.first;
    }
  }
  
  cout << curDay << endl;
  return 0;
}