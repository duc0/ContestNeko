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

char d[10];
bool isPalin(int x) {
  int n = x;
  int rev = 0;
  while (n > 0)
  {
    int d = n % 10;
    rev = rev * 10 + d;
    n /= 10;
  }
  return x == rev;
}


int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  
  const int BOUND = 2000000;
  PrimeGenerator pg(BOUND);
  
  int p, q;
  cin >> p >> q;
  
  int nPrime = 0;
  int nPalin = 0;
  vector<double> ratio(BOUND + 1);
  for_inc_range(x, 1, BOUND) {
    if (pg.isPrime(x)) {
      nPrime++;
    }
    if (isPalin(x)) {
      nPalin++;
    }
    ratio[x] = (double) (nPrime * 1.0) / nPalin;
  }
  for_dec_range(x, BOUND, 1) {
    if (ratio[x] * q <= p) {
      cout << x << endl;
      return 0;
    }
  }
  return 0;
}
