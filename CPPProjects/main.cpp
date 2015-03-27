//#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

#include <unordered_set>
#include <unordered_map>
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
#include <deque>
#include <climits>
#include <cfloat>
#include <random>

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

#define next _next

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
  template <typename T, typename U> struct hash<pair<T,U>> {
    size_t operator()(const std::pair<T, U> &v) const {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

unordered_map<pair<int, int>, int> cur;
int n;

const  int dx[] = {0, 0, -1 ,1};
const int dy[] = {1, -1, 0, 0};

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  cin >> n;
  cur[make_pair(0, 0)] = n;
  
  while (true) { 
    bool found = false;
    for (auto it : cur) {
      if (it.second < 4) {
        continue;
      }
      found = true;
      int each = it.second / 4;
      for (int d = 0; d < 4; ++d) {
        pair<int ,int> p2 = make_pair(it.first.first + dx[d], it.first.second + dy[d]);
        cur[p2] += each;
      }
      cur[it.first] -= 4 * each;
    }
    if (!found) {
      break;
    }
  }
  int q;
  cin >> q;
  repeat(q) {
    int x, y;
    cin >> x >> y;
    cout << cur[make_pair(x, y)] << endl;
  }
  
  return 0;
}
