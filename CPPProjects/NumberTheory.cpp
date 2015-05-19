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

class NumberTheory {
public:
  // O(sqrt(n))
  static bool isPrime(int64 n) {
    for (int64 i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }
  
  // O(sqrtn*logn)
  static set<int64> findDivisors(int64 n) {
    set<int64> ret;
    ret.insert(1);
    ret.insert(n);
    for (int64 i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
        ret.insert(i);
        ret.insert(n / i);
      }
    }
    return ret;
  }
};

class PrimeGenerator {
  vector<bool> prime;
  vector<int> primeList;
  int upper;
public:
  // Generate all primes between 2 and upper
  PrimeGenerator(int upper) {
    assert(upper >= 2);
    this->upper = upper;
    
    prime.resize(upper + 1);
    for_inc_range(i, 0, upper) {
      prime[i] = true;
    }
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= upper; ++i) {
      if (prime[i]) {
        for (int j = i * i; j <= upper; j += i) {
          prime[j] = false;
        }
      }
    }
    
    for_inc_range(i, 2, upper) {
      if (prime[i]) {
        primeList.push_back(i);
      }
    }
  }
  
  // O(1)
  bool isPrime(int n) const {
    assert(n <= upper);
    if (n < 2) {
      return false;
    }
    return prime[n];
  }
  
  // Get 1-based prime, e.g. getPrime(1) = 2, getPrime(2) = 3,...
  int getPrime(int id) const {
    assert(id >=1 && id <= primeList.size());
    return primeList[id - 1];
  }
  
  const vector<int> &getPrimeList() const {
    return primeList;
  }
};

// VK2015 R3 - D
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  int64 n;
  cin >> n;
  
  set<int64> divs = NumberTheory::findDivisors(n);
  
  int upper = 1200000;
  PrimeGenerator gen(upper);
  
  // p^k such that p^k + 1 divides n
  vector<pair<int64, pair<int, int64>>> primePower;
  
  for (int p : gen.getPrimeList()) {
    int k = 1;
    int64 ppower = p;
    while (ppower + 1 <= n) {
      if (divs.count(ppower + 1)) {
        primePower.push_back(make_pair(p, make_pair(k, ppower)));
      }
      ppower *= p;
      k++;
    }
  }
  
  for (int64 d: divs) {
    if (d - 1 > upper && NumberTheory::isPrime(d - 1)) {
      primePower.push_back(make_pair(d - 1, make_pair(1, d - 1)));
    }
  }
  
  sort(primePower.begin(), primePower.end());
  
  vector<int64> prime;
  vector<vector<int>> power;
  vector<vector<int64>> ppower;
  for (auto &entry: primePower) {
    if (prime.empty() || *prime.rbegin() < entry.first) {
      prime.push_back(entry.first);
      power.push_back(vector<int>());
      ppower.push_back(vector<int64>());
    }
    (*power.rbegin()).push_back(entry.second.first);
    (*ppower.rbegin()).push_back(entry.second.second);
  }
  
  vector<int64> vDivs(divs.begin(), divs.end());
  map<int64, int> divId;
  for_inc(i, vDivs.size()) {
    divId[vDivs[i]] = i;
  }
  int numDivs = (int) vDivs.size();
  
  vector<int> dp;
  dp.resize(numDivs);
  
  int numPrime = (int)prime.size();
  dp[divId[1]] = 1;
  for_inc(i, numPrime) {
    for_dec(id, numDivs) {
      int64 div = vDivs[id];
      
      
      for_inc(j, power[i].size()) {
        int64 pk = ppower[i][j];
        // p^k
        if (div % (pk + 1) == 0) {
          int64 div2 = div / (pk + 1);
          int64 id2 = divId[div2];
          dp[id] = (dp[id] + dp[id2]) % MOD;
        }
      }
    }
  }
  
  cout << dp[divId[n]] << endl;
  
  return 0;
}
