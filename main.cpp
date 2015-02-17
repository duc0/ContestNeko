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
#define INT64_INF 1E18L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template <class T, class Comparator=less<T> > class RangeMinimumQuery
{
  int n, k;
  Comparator cmp;
  T** a;
  int** bestId;
  int** bestId2;
public:
  RangeMinimumQuery(T sequence[], int size)
  {
    n=size;
    k=-1;
    while (size>0) {size>>=1; ++k;}
    a=new T*[k+1];
    bestId = new int*[k + 1];
    bestId2 = new int*[k + 1];
    for (int i=0; i<=k; ++i) {
      a[i]=new T[n+1-(1<<i)];
      bestId[i] = new int[n + 1 - (1 << i)];
      bestId2[i] = new int[n + 1 - (1 << i)];
    }
    for (int i=0; i<n; ++i) {
      a[0][i]=sequence[i];
      bestId[0][i] = i;
      bestId2[0][i] = -1;
    }
    for (int t=1; t<=k; ++t)
      for (int i=0; i<=n-(1<<t); ++i)
      {
        int j=i+(1<<(t-1));
        if (cmp(a[t-1][i], a[t-1][j])) {
          a[t][i] = a[t - 1][i];
          bestId[t][i] = bestId[t - 1][i];
          bestId2[t][i] = bestId2[t - 1][i];
        } else if (cmp(a[t-1][j], a[t-1][i])) {
          a[t][i] = a[t - 1][j];
          bestId[t][i] = bestId[t - 1][j];
          bestId2[t][i] = bestId2[t - 1][j];
        } else {
          a[t][i] = a[t - 1][i];
          int x = bestId[t - 1][i];
          bestId[t][i] = x;
          bestId2[t][i] = bestId2[t - 1][i];
          if (bestId[t - 1][j] != -1 && bestId[t - 1][j] != x) {
            bestId2[t][i] = bestId[t - 1][j];
          } else if (bestId2[t - 1][j] != -1 && bestId2[t - 1][j] != x) {
            bestId2[t][i] = bestId2[t - 1][j];
          }
        }
      }
  }
  ~RangeMinimumQuery()
  {
    for (int i=0; i<=k; ++i)
      delete[] a[i];
    delete[] a;
  }
  pair<T, pair<int, int>> Query(int i, int j)
  {
    int l=j-i+1, t=-1;
    while (l>0) {l>>=1; ++t;}
    int m=j+1-(1<<t);
    if (cmp(a[t][i], a[t][m])) {
      return make_pair(a[t][i], make_pair(bestId[t][i], bestId2[t][i]));
    } else if (cmp(a[t][m], a[t][i])) {
      return make_pair(a[t][m], make_pair(bestId[t][m], bestId2[t][m]));
    } else {
      int x = bestId[t][i];
      int y = bestId2[t][i];
      if (bestId[t][m] != -1 && bestId[t][m] != x) {
        y = bestId[t][m];
      } else if (bestId2[t][m] != -1 && bestId2[t][m] != x) {
        y = bestId2[t][m];
      }
      return make_pair(a[t][i], make_pair(x, y));
    }
  }
};

#define MAXN 200100

int n, q;

int64 h[MAXN];
int64 d[MAXN];
int64 dst[MAXN];

int64 hplusd[MAXN];
int64 hminusd[MAXN];

int main() {
  //testGen();
  //freopen("input3.txt", "r", stdin);
  
  cin >> n >> q;
  for_inc_range(i, 1, n) {
    cin >> dst[i];
  }
  for_inc_range(i, 1, n) {
    cin >> h[i];
  }
  
  for_inc_range(i, n + 1, 2 * n) {
    dst[i] = dst[i - n];
    h[i] = h[i - n];
  }
  
  n = n * 2;
  d[1] = 0;
  for_inc_range(i, 2, n) {
    d[i] = d[i - 1] + dst[i - 1];
  }
  
  for_inc_range(i, 1, n) {
    hplusd[i - 1] = 2 * h[i] + d[i];
    hminusd[i - 1] = 2 * h[i] - d[i];
  }
  
  RangeMinimumQuery<int64, std::greater<int64>> rmqplus(hplusd, n);
  RangeMinimumQuery<int64, std::greater<int64>> rmqminus(hminusd, n);
  
  int a, b;
  int leftBound, rightBound;
  repeat(q) {
    cin >> a >> b;
    if (a <= b) {
      leftBound = b + 1;
      rightBound = a - 1 + n / 2;
    } else {
      leftBound = b + 1;
      rightBound = a - 1;
    }
    
    leftBound--;
    rightBound--;
    
    pair<int64, pair<int, int>> mplus;
    pair<int64, pair<int, int>> mminus;
  
    int64 best = -INT64_INF, bt;
    
    int id;
    
    mplus = rmqplus.Query(leftBound, rightBound);
    for_inc(loop, 2) {
      if (loop == 0) {
        id = mplus.second.first;
      } else {
        id = mplus.second.second;
      }
      if (id == -1) continue;
      bt = -INT64_INF;
      if (leftBound <= id - 1) {
        bt = max(bt, rmqminus.Query(leftBound, id - 1).first);
      }
      if (id + 1 <= rightBound) {
        bt = max(bt, rmqminus.Query(id + 1, rightBound).first);
      }
      best = max(best, mplus.first + bt);
    }
    
    mminus = rmqminus.Query(leftBound, rightBound);
    for_inc(loop, 2) {
      if (loop == 0) {
        id = mminus.second.first;
      } else {
        id = mminus.second.second;
      }
      if (id == -1) continue;
      bt = -INT64_INF;
      if (leftBound <= id - 1) {
        bt = max(bt, rmqplus.Query(leftBound, id - 1).first);
      }
      if (id + 1 <= rightBound) {
        bt = max(bt, rmqplus.Query(id + 1, rightBound).first);
      }
      best = max(best, mminus.first + bt);
    }
    
    cout << best << endl;
  }
  
  return 0;
}