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
  freopen("input4.txt", "w", stdout);
  
  int n = 28;
  int x = 1;
  cout << n << endl;
  repeat(n) {
    x += rand() % 10;
    cout << x << endl;
  }
  fclose(stdout);
}

template <class T, class Comparator=less<T> > class RangeMinimumQuery
{
  int n, k;
  Comparator cmp;
  T** a;
public:
  RangeMinimumQuery(vector<T> sequence, int size)
  {
    n=size;
    k=-1;
    while (size>0) {size>>=1; ++k;}
    a=new T*[k+1];
    for (int i=0; i<=k; ++i)
      a[i]=new T[n+1-(1<<i)];
    for (int i=0; i<n; ++i)
      a[0][i]=sequence[i];
    for (int t=1; t<=k; ++t)
      for (int i=0; i<=n-(1<<t); ++i)
      {
        int j=i+(1<<(t-1));
        a[t][i]=cmp(a[t-1][i], a[t-1][j])?a[t-1][i]:a[t-1][j];
      }
  }
  ~RangeMinimumQuery()
  {
    for (int i=0; i<=k; ++i)
      delete[] a[i];
    delete[] a;
  }
  T Query(int i, int j)
  {
    int l=j-i+1, t=-1;
    while (l>0) {l>>=1; ++t;}
    int m=j+1-(1<<t);
    return cmp(a[t][i], a[t][m])?a[t][i]:a[t][m];
  }
};

#define MAXN 200100
int n;
vector<int> a;

void solve1() {
  int best = -1, besti = 0, bestj = 0;
  for_inc_range(i, 1, n) {
    for_inc_range(j, i, n) {
      int m = a[j] % a[i];
      if (m > best) {
        best = m;
        besti = i;
        bestj = j;
      }
    }
  }
  cout << best << endl;
  cout << a[bestj] << " " << a[besti] << endl;
}

void solve2() {
  int best = -1;
  RangeMinimumQuery<int, std::greater<int>> rmq(a, (int)a.size());
  for_inc_range(i, 1, n) {
    int x = a[i];
    for (int leftBound = x; leftBound <= a[n]; leftBound += x) {
      int rightBound = leftBound + x - 1;
      
      auto lSearch = lower_bound(a.begin(), a.end(), leftBound);
      auto rSearch = upper_bound(a.begin(), a.end(), rightBound);
      rSearch--;
      if (lSearch != a.end() && rSearch != a.end() && lSearch <= rSearch && *lSearch >= leftBound && *rSearch <= rightBound) {
        int b = rmq.Query((int)(lSearch - a.begin()), (int)(rSearch - a.begin())) % x;
        best = max(best, b);
        if (b  == x - 1) {
          break;
        }
      }
    }
  }
  cout << best << endl;
}

int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  scanf("%d", &n);
  int x;
  set<int> s;
  repeat(n) {
    scanf("%d", &x);
    s.insert(x);
  }
  n = (int)s.size();
  a.push_back(0);
  for (auto &x: s) {
    a.push_back(x);
  }
  
  //solve1();
  solve2();
  
  return 0;
}