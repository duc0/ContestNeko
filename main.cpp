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

template<class T> class CommonSubsequence {
  vector<int> seq1, seq2;
  int l1, l2;
  
  vector<vector<int>> pos; // pos[l][i] = min{j, lcs(i, j) = l, or l2 if not exists}
public:
  CommonSubsequence(const vector<T> &s1, const vector<T> &s2, int upper) {
    // Discretize
    unordered_map<T, int> valueMap;
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
    seq1 = s1;
    seq2 = s2;
    l1 = (int) seq1.size();
    l2 = (int) seq2.size();
    for_inc(i, l1) {
      seq1[i] = valueMap[seq1[i]];
    }
    for_inc(i, l2) {
      seq2[i] = valueMap[seq2[i]];
    }
    pos.resize(upper + 1);
    for (auto &v: pos) {
      v.resize(l1);
    }
    
    vector<int> minPos;
    int numValues = (int)valueMap.size();
    minPos.resize(valueMap.size());
    
    for_inc(x, numValues) {
      minPos[x] = l2;
    }
    for_dec(j, l2) {
      minPos[seq2[j]] = j;
    }
    
    if (minPos[seq1[0]] < l2) {
      pos[1][0] = minPos[seq1[0]];
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
            LOG(1, "Update pos " << l << ", " << i << " with " << minPos[seq1[i]] << ", cur: " << pos[l][i]);
            pos[l][i] = min(pos[l][i], minPos[seq1[i]]);
          }
          
        }
      }
    }
    
  }
  
  // Is there a j so that {lcs(i, j) = l}
  bool hasCommonSubsequence(int i, int l) {
    return pos[l][i] != l2;
  }
  
  // Return min{j, lcs(i, j) = l}
  int getPos(int i, int l) {
    return pos[l][i];
  }
};

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
  int maxCS = s / e;
  CommonSubsequence<int> cs(s1, s2, maxCS);
  
  int best = 0;
  for_inc_range(l, 1, maxCS) {
    int remainingEnergy = s - l * e;
    for_inc(i, l1) {
      if (cs.hasCommonSubsequence(i, l)) {
        int j = cs.getPos(i, l);
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
