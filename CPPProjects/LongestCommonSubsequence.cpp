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

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Compute LCS up ot length L of two sequences in O(L*(l1 + l2)) where l1, l2
// are the length of the two sequences
// Memory: O(L*l1)
// Usage: construct with the two sequences, and L
template<class T> class LongestCommonSubsequence {
  vector<int> seq1, seq2;
  int l1, l2, upper, longest;
  
  vector<vector<int>> pos; // pos[l][i] = min{j, lcs(i, j) = l, or l2 if not exists}
  
  unordered_map<T, int> valueMap;
  
  void discretize(const vector<T> &s1, const vector<T> &s2) {
    int idx = 0;
    for (auto &x: s1) {
      if (!valueMap.count(x)) {
        valueMap[x] = idx;
        idx++;
      }
    }
    for (auto &x: s2) {
      if (!valueMap.count(x)) {
        valueMap[x] = idx;
        idx++;
      }
    }
    
    l1 = (int) s1.size();
    l2 = (int) s2.size();
    upper=min(upper, l1);
    upper=min(upper, l2);
    
    seq1.resize(l1);
    seq2.resize(l2);
    for_inc(i, l1) {
      seq1[i] = valueMap[s1[i]];
    }
    for_inc(i, l2) {
      seq2[i] = valueMap[s2[i]];
    }
  }
public:
  LongestCommonSubsequence(const vector<T> &s1, const vector<T> &s2, int upper) {
    this->upper = upper;
    
    discretize(s1, s2);
    
    pos.resize(upper + 1, vector<int>(l1));
    
    int numValues = (int)valueMap.size();
    
    vector<int> minPos(numValues, l2);
    
    for_dec(j, l2) {
      minPos[seq2[j]] = j;
    }
    
    longest = 0;
    
    if (minPos[seq1[0]] < l2) {
      pos[1][0] = minPos[seq1[0]];
      longest = 1;
    } else {
      pos[1][0] = l2;
    }
    for_inc_range(i, 1, l1 - 1) {
      pos[1][i] = pos[1][i - 1];
      if (minPos[seq1[i]] < l2) {
        pos[1][i] = min(pos[1][i], minPos[seq1[i]]);
      }
    }
    
    for_inc_range(l, 2, upper) {
      pos[l][0] = l2;
      
      int leftIndex = l2;
      for_inc(x, numValues) {
        minPos[x] = l2;
      }
      
      for_inc_range(i, 1, l1 - 1) {
        pos[l][i] = pos[l][i - 1];
        if (pos[l - 1][i - 1] != l2) {
          int newLeftIndex = pos[l - 1][i - 1] + 1;
          for_dec_range(j, leftIndex - 1, newLeftIndex) {
            minPos[seq2[j]] = j;
          }
          leftIndex = newLeftIndex;
          if (minPos[seq1[i]] < l2) {
            pos[l][i] = min(pos[l][i], minPos[seq1[i]]);
          }
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
  int getMinPos(int i, int l) const {
    assert(hasLCS(i, l));
    return pos[l][i];
  }
};

// Sample: CF243_C
int l1, l2, s, e;
vector<int> s1, s2;

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  cin >> l1 >> l2 >> s >> e;
  int x;
  repeat(l1) {
    cin >> x;
    s1.push_back(x);
  }
  repeat(l2) {
    cin >> x;
    s2.push_back(x);
  }
  if (s1.size() > s2.size()) {
    swap(s1, s2);
    swap(l1, l2);
  }
  int maxCS = s / e;
  LongestCommonSubsequence<int> lcs(s1, s2, maxCS);
  
  int best = 0;
  for_inc_range(l, 1, maxCS) {
    int remainingEnergy = s - l * e;
    for_inc(i, l1) {
      if (lcs.hasLCS(i, l)) {
        int j = lcs.getMinPos(i, l);
        if (i + 1 + j + 1 <= remainingEnergy) {
          best = l;
          break;
        }
      }
    }
  }
  
  cout << best << endl;
  return 0;
}
