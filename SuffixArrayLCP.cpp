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

template <class T> class SuffixArray {
  vector<T> s;
  size_t n;
  vector<int> suffix, rank, lcp;
  bool shortFirst;
  
  bool saBuilt = false;
  bool lcpBuilt = false;
  
public:
  // If shortFirst is true, the special character is the minimum character.
  // Otherwise it is the maximum.
  SuffixArray(vector<T> s, bool shortFirst = true)
  : s(s), shortFirst(shortFirst), n(s.size()) {}
  
  void buildSuffixArray() {
    s.push_back(0);
    
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
  
  int getLCP(int i) {
    assert(lcpBuilt);
    
    return lcp[i];
  }
};

// Sample: SUBST1, SPOJ
char s[50002];

int main() {
  // freopen("input1.txt", "r", stdin);
  int n;
  long long r, l;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    l = strlen(s);
    SuffixArray<char> sa(vector<char>(s, s + l));
    sa.buildSuffixArray();
    sa.buildLCP();
    r = l * (l + 1) / 2;
    for (int i = 1; i < l; ++i)
      r -= sa.getLCP(i);
    printf("%lld\n", r);
  }
  return 0;
}
