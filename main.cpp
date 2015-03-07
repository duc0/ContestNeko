#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
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

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
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

template <class T> int sortAndCountInversions(vector<T> a, int l, int r)
{
  if (l>=r) return 0;
  int m=(l+r)/2;
  int s=sortAndCountInversions(a,l,m) + sortAndCountInversions(a,m+1,r);
  int i=0, j=m+1, k=l, n1=m-l+1;
  vector<T> L(n1);
  for (int i=0; i<n1; ++i) L[i]=a[l+i];
  while (i<n1 && j<=r)
    if (L[i] > a[j])
    {
      a[k++]=a[j++];
      s+=n1-i;
    }
    else
      a[k++]=L[i++];
  while (i<n1) a[k++]=L[i++];
  while (j<=r) a[k++]=a[j++];
  return s;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input4.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n + 1);
  
  int nBooks = 0;
  
  for_inc_range(i, 1, n) {
    a[i].resize(m + 1);
    for_inc_range(j, 1, m) {
      int x;
      cin >> x;
      a[i][j] = x;
      nBooks = max(nBooks, x);
    }
  }
  
  vector<pair<int, int>> pos(nBooks + 1);
  
  for_inc_range(i, 1, n) {
    for_inc_range(j, 1, m) {
      int x;
      cin >> x;
      if (x > 0) {
        pos[x] = make_pair(i, j);
      }
    }
  }
  
  int ret = 0;
  
  for_inc_range(i, 1, n) {
    bool same = true;
    vector<int> book;
    for_inc_range(j, 1, m) {
      int x = a[i][j];
      if (x > 0) {
        assert(pos[x].first == i);
        if (pos[x].second != j) {
          same = false;
        }
        book.push_back(x);
      }
    }
    
    if (!same) {
      if (book.size() == m) {
        cout << -1 << endl;
        return 0;
      }
      LOG(1, "Row " << i);
      
      for_inc(j, book.size()) {
        book[j] = pos[book[j]].second;
        LOG(1, book[j]);
      }
      
      int need = sortAndCountInversions<int>(book, 0,(int) book.size() - 1);
      ret += need;
    }
  }
  
  cout << ret << endl;
  
  return 0;
}
