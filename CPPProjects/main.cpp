//#define SUBMIT

#define C11

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
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11
#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>
#endif

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define countBit __builtin_popcount
#define countBit64 __builtin_popcountl

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)

template <int BASE, int64 MODULO> class StringHash {
  template <int B, int64 M> friend class StringHasher;
  vector<int64> hash;
  
public:
  size_t getSize() const { return hash.size(); }
};

template <int BASE, int64 MODULO> class StringHasher {
  
public:
  static int64 getBasePower(int n) {
    static vector<int64> power; // cache
    if (n > (int)power.size() - 1) {
      int cur = (int)power.size() - 1;
      power.resize(n + 1);
      for_inc_range(i, cur + 1, n) {
        if (i == 0) {
          power[i] = 1;
        } else {
          power[i] = (power[i - 1] * BASE) % MODULO;
        }
      }
    }
    return power[n];
  }

  template <class Iterator>
  static StringHash<BASE, MODULO> getHash(Iterator begin, Iterator end) {
    StringHash<BASE, MODULO> h;
    int n = (int)(end - begin);
    h.hash.resize(n);
    int idx = 0;
    int64 last = 0;
    for (auto it = begin; it != end; ++it) {
      h.hash[idx] = (last * BASE + *it) % MODULO;
      last = h.hash[idx];
      idx++;
    }
    return h;
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh) {
    return sh.hash[sh.getSize() - 1];
  }
  
  static int64 getHashValue(const StringHash<BASE, MODULO> &sh, int first,
                            int len) {
    if (len == 0) return 0;
    assert(0 <= first && first < sh.getSize());
    assert(len >= 1);
    assert(first + len - 1 < sh.getSize());
    
    int last = first + len - 1;
    
    if (first == 0)
      return sh.hash[last];
    
    int64 ret =
    (sh.hash[last] - sh.hash[first - 1] * getBasePower(len)) % MODULO;
    if (ret < 0)
      ret += MODULO;
    return ret;
  }
  
  static int64 getHashValueConcat(const StringHash<BASE, MODULO> &sh1,
                                  const StringHash<BASE, MODULO> &sh2) {
    
    return (getHashValue(sh1) * getBasePower((int)sh2.getSize()) +
            getHashValue(sh2)) %
    MODULO;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

template<int BASE, int64 M> int64 getHash(int i, int c, int n, const StringHash<BASE, M> &h) {
  int64 hL = StringHasher<BASE, M>::getHashValue(h, 0, i);
  int64 hR = StringHasher<BASE, M>::getHashValue(h, i, n - i);
  
  int64 hAll = (hL * BASE + c + 3) % M;
  hAll = (hAll * StringHasher<BASE, M>::getBasePower(n - i) + hR) % M;
  return hAll;
}

#define B1 31
#define B2 37
#define HMOD1 1000001927
#define HMOD2 1000001963

set<pair<int64, int64>> getAll(const vector<int> &s, int n) {
  StringHash<B1, HMOD1> h1 = StringHasher<B1, HMOD1>::getHash(s.begin(), s.end());
  StringHash<B2, HMOD2> h2 = StringHasher<B2, HMOD2>::getHash(s.begin(), s.end());

  
  set<pair<int64, int64>> ans;
  for_inc_range(i, 0, n) {
    for_inc(c, 26) {
      int64 v1 = getHash<B1, HMOD1>(i, c, n, h1);
      int64 v2 = getHash<B2, HMOD2>(i, c, n, h2);
      ans.insert(make_pair(v1, v2));
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  string ss1, ss2;
  cin >> ss1 >> ss2;
  
  vector<int> s1(n);
  for_inc(i, n) s1[i] = ss1[i] - 'a' + 3;
  vector<int> s2(n);
  for_inc(i, n) s2[i] = ss2[i] - 'a' + 3;
  
  set<pair<int64, int64>> all1 = getAll(s1, n);
  set<pair<int64, int64>> all2 = getAll(s2, n);
  
  int64 ans = 0;
  for (auto &hVal : all2) {
    if (all1.count(hVal)) {
      ans++;
    }
  }
  
  cout << ans << endl;
  
  return 0;
}
