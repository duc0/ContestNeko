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
#define fill0(x) memset(a, 0, sizeof(a))
#define foreach(s,i) for (typeof(s.begin()) i=s.begin(); i!=s.end(); ++i)

void testGen() {
  }

int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  int n1, n2, k1, k2;
  cin >> n1 >> n2 >> k1 >> k2;
  if (n1 <= n2) {
    cout << "Second";
  } else {
    cout << "First";
  }
  return 0;
}