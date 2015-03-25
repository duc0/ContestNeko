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
#include <unordered_map>

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

class BinarySearch {
public:
  template<class T> static T binarySearchMin(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = maxIndex + 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        rightIndex = midIndex - 1;
      } else {
        leftIndex = midIndex + 1;
      }
    }
    return ret;
  }
  
  template<class T> static T binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
    T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = minIndex - 1;
    while (leftIndex <= rightIndex) {
      midIndex = leftIndex + (rightIndex - leftIndex) / 2;
      if (predicate(midIndex)) {
        ret = midIndex;
        leftIndex = midIndex + 1;
      } else {
        rightIndex = midIndex - 1;
      }
    }
    return ret;
  }
  
  static double binarySearchMaxReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        ret = m;
        l = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
  static double binarySearchMinReal(double minRange, double maxRange, double epsilon, const function<bool(double)> &predicate) {
    double l = minRange, r = maxRange, m, ret = maxRange + 1;
    while (r - l > epsilon) {
      m = l + (r - l) / 2;
      if (predicate(m)) {
        l = m;
        ret = m;
      } else {
        r = m;
      }
    }
    return ret;
  }
  
};

// seq2 must implement getNextPos(i, c) = min{j, j >= i && seq2[j] = c}
// Memory: O(L * L1)
// Time: O(L * L1 * Q) in which Q is the running time of seq2.getNextPos(i, c)
template<class T, class S> class LongestCommonSubsequenceSmallAlphabet {
  int l1, longest, upper;
  int64 l2;
  vector<vector<int64>> pos; // pos[l][i] = min{j, lcs(i, j) = l, or l2 if not exists}
  
public:
  LongestCommonSubsequenceSmallAlphabet(const vector<T> &seq1, const S &seq2, int upper) {
    l1 = (int)seq1.size();
    l2 = seq2.size();
    upper = min(upper, l1);
    upper = min(upper, (int)l2);
    this->upper = upper;
    
    pos.resize(upper + 1, vector<int64>(l1));
    
    longest = 0;
    
    for_inc(i, l1) {
      pos[1][i] = l2;
      if (i >= 1) {
        pos[1][i] = pos[1][i - 1];
      }
      pos[1][i] = min(pos[1][i], seq2.getNextPos(0, seq1[i]));
      if (pos[1][i] != l2) {
        longest = 1;
      }
    }
    
    for_inc_range(l, 2, upper) {
      for_inc(i, l1) {
        pos[l][i] = l2;
        if (i >= 1) {
          pos[l][i] = pos[l][i - 1];
        }
        if (i >= 1 && pos[l - 1][i - 1] != l2) {
          pos[l][i] = min(pos[l][i], seq2.getNextPos(pos[l - 1][i - 1] + 1, seq1[i]));
        }
        if (pos[l][i] != l2) {
          longest = l;
        }
      }
    }
    
  }
  
  int getLongest() const {
    return longest;
  }
  
  // Is there a j so that {lcs(i, j) = l}
  bool hasLCS(int i, int l) const {
    if (l > upper) return false;
    return pos[l][i] != l2;
  }
  
  // Return min{j, lcs(i, j) = l}
  int64 getMinPos(int i, int l) const {
    assert(hasLCS(i, l));
    return pos[l][i];
  }
};

class SimpleHyperString {
  string s;
  int n;
  vector<vector<int>> next;
  
public:
  SimpleHyperString(string s) {
    this->s = s;
    n = (int) s.length();
    next = vector<vector<int>>(26, vector<int>(n));
    
    for_dec(i, n) {
      for_inc(c, 26) {
        next[c][i] = n;
        if (i + 1 < n) {
          next[c][i] = next[c][i + 1];
        }
        if (s[i] - 'a' == c) {
          next[c][i] = i;
        }
      }
    }
  }
  
  int64 getNextPos(int64 i, char c) const {
    if (i >= n) return n;
    return next[c - 'a'][i];
  }
  
  int64 size() const {
    return n;
  }
};

class HyperString {
  const vector<string> &base;
  const vector<int> &indices;
  
  vector<SimpleHyperString> hp;
  vector<int64> begin;
  
  vector<vector<int64>> next;
  
  int64 n;
  int nSeq;
  
  int getSeqIndex(int64 i) const {
    return BinarySearch::binarySearchMax<int>(0, nSeq - 1, [&](int s){return begin[s] <= i;});
  }
  
public:
  HyperString(const vector<string> &base, const vector<int> &indices): base(base), indices(indices) {
    n = 0;
    for (auto &i: indices) {
      n += base[i].size();
    }
    
    for (auto &s: base) {
      hp.push_back(SimpleHyperString(s));
    }
    
    nSeq = (int) indices.size();
    begin.resize(nSeq);
    begin[0] = 0;
    for_inc_range(i, 1, nSeq - 1) {
      begin[i] = begin[i - 1] + base[indices[i - 1]].size();
    }
    
    next = vector<vector<int64>>(26, vector<int64>(nSeq));
    
    for_dec(i, nSeq) {
      for_inc(c, 26) {
        next[c][i] = hp[indices[i]].getNextPos(0, c + 'a');
        int l = (int)base[indices[i]].size();
        if (next[c][i] < l) {
          next[c][i] += begin[i];
        } else {
          if (i + 1 < nSeq) {
            next[c][i] = next[c][i + 1];
          } else {
            next[c][i] = n;
          }
        }
      }
    }
  }
  
  int64 size() const {
    return n;
  }
  
  int64 getNextPos(int64 i, char c) const {
    if (i >= n) return n;
    int seq = getSeqIndex(i);
    int64 iLocal = i - begin[seq];
    int64 ans = hp[indices[seq]].getNextPos(iLocal, c);
    if (ans < base[indices[seq]].size()) {
      ans += begin[seq];
    } else if (seq + 1 < nSeq) {
      ans = next[c - 'a'][seq + 1];
    } else {
      ans = n;
    }
    return ans;
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

vector<string> base;

// CF Croc Champ 2012 - Round 2 - D

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  
  repeat(n) {
    string s;
    cin >> s;
    base.push_back(s);
  }
  
  int m;
  cin >> m;
  vector<int> indices;
  repeat(m) {
    int i;
    cin >> i;
    i--;
    indices.push_back(i);
  }
  
  string s;
  cin >> s;
  
  vector<char> s1;
  for (char c: s) {
    s1.push_back(c);
  }
  HyperString hs(base, indices);
  
  LongestCommonSubsequenceSmallAlphabet<char, HyperString> lcs(s1, hs, (int)s1.size());
  
  cout << lcs.getLongest() << endl;
  
  return 0;
}
