//#define SUBMIT

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
#include <sstream>

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

// Note: 1-base index
template<class T> class PrefixFunction {
  vector<T> s;
  int n;
  
  vector<int> p; // p[i] = max{j, j < i && s[1..j] is a suffix of s[1..i]}, or 0 if not
  
  inline T getS(int i) const {return s[i - 1];}
public:
  template<class Iterator> PrefixFunction(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; it++) {
      s.push_back(*it);
    }
    n = (int) s.size();
    
    p.resize(n + 1);
    
    p[0] = 0;
    p[1] = 0;
    int k = 0;
    
    for_inc_range(i, 2, n) {
      while (k > 0 && getS(k + 1) != getS(i)) {
        k = p[k];
      }
      if (getS(k + 1) == getS(i)) {
        k++;
      }
      p[i] = k;
    }
  }
  
  int get(int i) const {
    assert(0 <= i && i <= n);
    return p[i];
  }
};


// Note: 1-base index
template <class T, T BeginAlphabet, T EndAlphabet> class SuffixAutomata {
  vector<T> s;
  int n;
  int alphabetSize;
  vector<vector<int>> next;
  
  inline T getS(int i) const {return s[i - 1];}
public:
  template<class Iterator> SuffixAutomata(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; it++) {
      s.push_back(*it);
    }
    n = (int) s.size();
    
    alphabetSize = EndAlphabet - BeginAlphabet + 1;
    next.resize(alphabetSize);
    for_inc(c, alphabetSize) {
      next[c].resize(n + 1);
    }
    
    PrefixFunction<T> p(begin, end);
    for_inc_range(i, 0, n) {
      for_inc(c, alphabetSize) {
        if (c == getS(i + 1) - BeginAlphabet) {
          next[c][i] = i + 1;
        } else {
          next[c][i] = next[c][p.get(i)];
        }
      }
    }
  }
  
  int getNext(int i, T c) const {
    assert(0 <= i && i <= n);
    assert(BeginAlphabet <= c && c <= EndAlphabet);
    return next[c - BeginAlphabet][i];
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// SPOJ - PSTRING

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  while (1) {
    string x, y;
    if (!(cin >> x)) break;
    cin >> y;
    
    SuffixAutomata<char, 'a', 'z'> sa(y.begin(), y.end());
    
    int n = (int)x.size();
    vector<vector<int>>f;
    int m = (int)y.size();
    f.resize(n + 1);
    
    for_inc_range(i, 0, n) {
      f[i].resize(m + 1);
    }
    
    for_inc_range(i, 0, n) {
      for_inc_range(s, 0, m) {
        f[0][s] = -INT_INF;
      }
    }
    f[0][0] = 0;
    
    for_inc_range(i, 0, n - 1) {
      for_inc_range(s, 0, m - 1) {
        if (f[i][s] == -INT_INF) continue;
        f[i + 1][s] = max(f[i + 1][s], f[i][s]);
        int s2 = sa.getNext(s, x[i + 1 - 1]);
        LOG(1, "Go " << s << " " << x[i + 1 - 1] << " " << s2);
        if (s2 < m) {
          f[i + 1][s2] = max(f[i + 1][s2], f[i][s] + 1);
        }
      }
    }
    
    for_inc_range(i, 0, n) {
      for_inc_range(s, 0, m) {
        LOG(1, i << " " << s << " " << f[i][s]);
      }
    }
    int best = n;
    for_inc_range(s, 0, m - 1) {
      best = min(best, n - f[n][s]);
    }
    
    cout << best << endl;
  }
  return 0;
}
