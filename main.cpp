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

bool isPrime(int n) {
  if (n<2) return false; // optional
  for (int i=2; i*i<=n; ++i) if (n%i==0) return false;
  return true;
}

void extendedEuclid(int a, int b, int &x, int &y) {
  if (b==0) {x=1; y=0; return;}
  int x2;
  extendedEuclid(b,a%b,x2,x);
  y=x2-(a/b)*x;
}
int modulo(int64 a, int b) {
  int r=a%b;
  if (r<0) r+=b;
  return r;
}
int modularInverse(int a, int m) {
  int x, y;
  extendedEuclid(a, m, x, y);
  return modulo(x,m);
}

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);

  int n;
  cin >> n;
  if (n == 1) {
    cout << "YES" << endl;
    cout << 1 << endl;
    return 0;
  }
  if (n == 4) {
    cout << "YES" << endl;
    cout << "1" << endl;
    cout << "3" << endl;
    cout << "2" << endl;
    cout << "4" << endl;
    return 0;
  }
  
  
  if (!isPrime(n)) {
    cout << "NO";
  } else {
    cout << "YES" << endl;
    int a = 1;
    for_inc_range(i, 1, n - 1) {
      int x = modulo((int64)i * modularInverse(a, n), n);
      cout << x << endl;
      a = modulo((int64)a * x, n);
    }
    cout << n << endl;
  }
  
  return 0;
}