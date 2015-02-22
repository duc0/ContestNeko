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

template <class T> class RangeQuery {
  size_t n, k;
  vector<vector<T>> a;
  function<T(T, T)> combine;
  
public:
  RangeQuery() {}
  
  template <class Iterator>
  RangeQuery(Iterator begin, Iterator end) {
    init(begin, end);
  }
  
  template <class Iterator>
  RangeQuery(Iterator begin, Iterator end, const function<T(T, T)> &combine) {
    init(begin, end, combine);
  }
  
  // The default combine function is min (Range Minimum Query).
  template <class Iterator>
  void init(Iterator begin, Iterator end) {
    init(begin, end, [](T a, T b) { return min(a, b); });
  }
  
  template <class Iterator>
  void init(Iterator begin, Iterator end, const function<T(T, T)> &combine) {
    this->combine = combine;
    n = end - begin;
    k = -1;
    size_t s = n;
    while (s > 0) {
      s >>= 1;
      ++k;
    }
    a.resize(k + 1);
    for (int i = 0; i <= k; ++i) {
      a[i].resize(n + 1 - (1 << i));
    }
    auto it = begin;
    for (int i = 0; i < n; ++i) {
      a[0][i] = *it;
      ++it;
    }
    for (int t = 1; t <= k; ++t) {
      for (int i = 0; i <= n - (1 << t); ++i) {
        a[t][i] = combine(a[t - 1][i], a[t - 1][i + (1 << (t - 1))]);
      }
    }
  }
  
  T query(int i, int j) {
    int l = j - i + 1, t = -1;
    while (l > 0) {
      l >>= 1;
      ++t;
    }
    int m = j + 1 - (1 << t);
    return combine(a[t][i], a[t][m]);
  }
};

template <class T> class SuffixArray {
  vector<T> s;
  size_t n;
  vector<int> suffix, rank, lcp;
  bool shortFirst;
  RangeQuery<int> rangeLCP;
  
  bool saBuilt = false;
  bool lcpBuilt = false;
  bool rangeLCPBuilt = false;
public:
  // If shortFirst is true, the special character is the minimum character.
  // Otherwise it is the maximum.
  template <class Iterator> SuffixArray(Iterator begin, Iterator end, bool shortFirst = true)
  : shortFirst(shortFirst), n(end - begin) {
    s.resize(n + 1);
    auto it = begin;
    for (int i = 0; i < n; ++i) {
      s[i] = *it;
      it++;
    }
    s.push_back(0);
  }
  
  void buildSuffixArray() {
    suffix.resize(n);
    rank.resize(n + 1);
    
    vector<int> tmp;
    tmp.resize(n);
    
    for (int i = 0; i < n; ++i) {
      suffix[i] = i;
    }
    
    auto compareInitial = [this](int i, int j) { return s[i] < s[j]; };
    sort(suffix.begin(), suffix.end(), compareInitial);
    rank[suffix[0]] = 0;
    for (int i = 1; i < n; ++i)
      rank[suffix[i]] =
      rank[suffix[i - 1]] + compareInitial(suffix[i - 1], suffix[i]);
    rank[n] = shortFirst ? -1 : (int)n;
    
    for (int step = 1; step < n; step <<= 1) {
      auto compare = [this, &step](int i, int j) {
        return ((rank[i] < rank[j]) ||
                (rank[i] == rank[j] && rank[i + step] < rank[j + step]));
      };
      sort(suffix.begin(), suffix.end(), compare);
      tmp[suffix[0]] = 0;
      for (int i = 1; i < n; ++i)
        tmp[suffix[i]] = tmp[suffix[i - 1]] + compare(suffix[i - 1], suffix[i]);
      for (int i = 0; i < n; ++i)
        rank[i] = tmp[i];
    }
    saBuilt = true;
  }
  
  void buildLCP() {
    assert(saBuilt);
    
    lcp.resize(n);
    int h = 0;
    for (int i = 0; i < n; ++i) {
      if (rank[i] != 0) {
        int j = suffix[rank[i] - 1];
        while (s[i + h] == s[j + h])
          ++h;
        lcp[rank[i]] = h;
        if (h > 0)
          --h;
      }
    }
    
    lcpBuilt = true;
  }
  
  void buildRangeLCP() {
    assert(lcpBuilt);
    
    rangeLCP.init(lcp.begin(), lcp.end());
    
    rangeLCPBuilt = true;
  }
  
  int getLCP(int i) {
    assert(lcpBuilt);
    
    i = rank[i];
    return lcp[i];
  }
  
  int getPrevSuffix(int i) {
    assert(saBuilt);
    
    return suffix[rank[i] - 1];
  }
  
  // O(logN)
  int getLCP(int i, int j) {
    assert(rangeLCPBuilt);
    assert(i != j);
    i = rank[i];
    j = rank[j];
    
    if (i > j) swap(i, j);
    
    return rangeLCP.query(i + 1, j);
  }
  
  // Compare two substrings [i1, j1] and [i2, j2], O(logn)
  int compareSubstr(int i1, int j1, int i2, int j2) {
    assert(rangeLCPBuilt);
    assert(0 <= i1 && i1 <= j1 && j1 < n);
    assert(0 <= i2 && i2 <= j2 && j2 < n);
    int l1 = j1 - i1 + 1;
    int l2 = j2 - i2 + 1;
    if (l1 > l2) {
      swap(l1, l2); swap(i1, i2); swap(j1, j2);
    }
    int l = getLCP(i1, i2);
    if (l >= l1) {
      return l1 == l2 ? 0 : -1;
    } else {
      T c1 = s[i1 + l];
      T c2 = s[i2 + l];
      if (c1 < c2) return -1;
      if (c1 > c2) return 1;
      return 0;
    }
  }
};

// Sample: SUBST1, SPOJ
char s[50002];

int main() {
  //freopen("input1.txt", "r", stdin);
  int n;
  long long r, l;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    l = strlen(s);
    SuffixArray<char> sa(s, s + l);
    sa.buildSuffixArray();
    sa.buildLCP();
    r = l * (l + 1) / 2;
    for (int i = 1; i < l; ++i)
      r -= sa.getLCP(i);
    printf("%lld\n", r);
  }
  return 0;
}
