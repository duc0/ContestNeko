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
  
public:
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

#define HMOD1 1000001927
#define HMOD2 1000001963
#define BASE1 3
#define BASE2 5

int lenS, lenT;
string s, t;
pair<StringHash<BASE1, HMOD1>, StringHash<BASE2, HMOD2>> hashS[26], hashT[26];
vector<int64> hT(26), htSorted(26);

bool check(int i) {
  vector<int64> hS(26);
  for_inc(c, 26) {
    hS[c] = StringHasher<BASE1, HMOD1>::getHashValue(hashS[c].first, i, lenT) * HMOD1 + StringHasher<BASE2, HMOD2>::getHashValue(hashS[c].second, i, lenT);
  }
  vector<int64> hsSorted = hS;
  sort(hsSorted.begin(), hsSorted.end());
  for_inc(c, 26) {
    if (hsSorted[c] != htSorted[c]) {
      return false;
    }
  }
  
  for_inc(c1, 26) {
    if (hS[c1] == 0) continue;
    for_inc(c2, 26) {
      if (hS[c1] == hT[c2] && hS[c2] != hT[c1]) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input2.txt", "r", stdin);
#endif
  
  cin >> lenS >> lenT;
  cin >> s >> t;
  
  for_inc(c, 26) {
    vector<int> vs, vt;
    for_inc(i, lenS) {
      vs.push_back((s[i] - 'a') == c);
    }
    for_inc(i, lenT) {
      vt.push_back((t[i] - 'a') == c);
    }
    
    hashS[c] = make_pair(StringHasher<BASE1, HMOD1>::getHash(vs.begin(), vs.end()), StringHasher<BASE2, HMOD2>::getHash(vs.begin(), vs.end()));
    hashT[c] = make_pair(StringHasher<BASE1, HMOD1>::getHash(vt.begin(), vt.end()), StringHasher<BASE2, HMOD2>::getHash(vt.begin(), vt.end()));
  }
  for_inc(c, 26) {
    hT[c] = StringHasher<BASE1, HMOD1>::getHashValue(hashT[c].first) * HMOD1 + StringHasher<BASE2, HMOD2>::getHashValue(hashT[c].second);
  }
  htSorted = hT;
  sort(htSorted.begin(), htSorted.end());
  
  vector<int> ans;
  for_inc(i, lenS - lenT + 1) {
    if (check(i)) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << endl;
  for (int i : ans) cout << (i + 1) << " ";
  
  return 0;
}
