#define SUBMIT

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


template<class T> T binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
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

// Find LIS in O(nlogn)
// Usage: construct with iterators
// Then query the LIS
// O(nlogn)

template <class T> class LongestIncreasingSubsequence {
  int n, longest;
  vector<int> minVal; // minVal[k] = min{a[i], lis(i) = k}
  
public:
  template<class Iterator> LongestIncreasingSubsequence(Iterator begin, Iterator end) {
    vector<T> seq(begin, end);
    
    n = (int) seq.size();
    
    minVal.resize(n + 1);
    minVal[1] = seq[0];
    
    longest = 1;
    for_inc_range(i, 1, n - 1) {
      int k = binarySearchMax<int>(1, longest, [&](int l) {return minVal[l] < seq[i];});
      if (k == longest) {
        longest++;
        minVal[longest] = seq[i];
      } else {
        minVal[k + 1] = min(minVal[k + 1], seq[i]);
      }
    }
  }
  
  int getLength() {
    return longest;
  }
};

// Sample : COCI 14 15 Round 7 - Police

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n + 1);
  
  int nBooks = 0;
  
  for_inc_range(i, 1, n) {
    a[i].resize(m + 1);
    for_inc_range(j, 1, m) {
      int x;
      cin >> x;
      a[i][j] = x;
      nBooks = max(nBooks, x);
    }
  }
  
  vector<pair<int, int>> pos(nBooks + 1);
  
  bool hasEmpty = false;
  for_inc_range(i, 1, n) {
    for_inc_range(j, 1, m) {
      int x;
      cin >> x;
      if (x > 0) {
        pos[x] = make_pair(i, j);
      } else {
        hasEmpty = true;
      }
    }
  }
  
  int ret = 0;
  
  for_inc_range(i, 1, n) {
    bool same = true;
    vector<int> book;
    for_inc_range(j, 1, m) {
      int x = a[i][j];
      if (x > 0) {
        assert(pos[x].first == i);
        if (pos[x].second != j) {
          same = false;
        }
        book.push_back(x);
      }
    }
    
    if (!same) {
      if (book.size() == m && !hasEmpty) {
        cout << -1 << endl;
        return 0;
      }
      LOG(1, "Row " << i);
      
      for_inc(j, book.size()) {
        book[j] = pos[book[j]].second;
        LOG(1, book[j]);
      }
      
      LongestIncreasingSubsequence<int> lis(book.begin(), book.end());
      
      int need = (int) book.size() - lis.getLength();
      if (book.size() == m) {
        ret += need + 1;
      } else {
        ret += need;
      }
    }
  }
  
  cout << ret << endl;
  
  return 0;
}
