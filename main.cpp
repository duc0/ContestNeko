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

template <class T> struct TreeNode {
  int nextNode[26];
  int length = 0;
  int suffixLink = 0;
  int count = 0;
  
  TreeNode() {
    memset(nextNode, -1, sizeof(nextNode));
  }
  
  bool hasNextNode(T c) const {
    return nextNode[c] != -1;
  }
  
  int getNextNode(T c) const {
    return nextNode[c];
  }
  
  void setNextNode(T c, int v) {
    nextNode[c] = v;
  }
};


template<class T> class PalindromicTree {
  const int FAKE_ROOT_MINUS_1 = 0;
  const int FAKE_ROOT_0 = 1;
  
  vector<T> s;
  
  vector<TreeNode<T>> node;
  
  int n;
  
  int maxSuffixPalindrome;
  
  int newNode(int length, int suffixLink) {
    TreeNode<T> p;
    p.length = length;
    p.suffixLink = suffixLink;
    node.push_back(p);
    return (int)node.size() - 1;
  }
  
  bool addLetter(int pos) {
    int curNode = maxSuffixPalindrome, curLength = 0;
    T letter = s[pos];
    
    while (true) {
      curLength = node[curNode].length;
      if (pos - 1 - curLength >= 0 && s[pos - 1 - curLength]  == s[pos]) {
        break;
      }
      curNode = node[curNode].suffixLink;
    }
    
    if (node[curNode].hasNextNode(letter)) {
      maxSuffixPalindrome = node[curNode].getNextNode(letter);
      return false;
    }
    
    newNode(node[curNode].length + 2, FAKE_ROOT_MINUS_1);
    maxSuffixPalindrome = (int) node.size() - 1;
    node[curNode].setNextNode(letter, maxSuffixPalindrome);
    
    TreeNode<T> &mNode = node[maxSuffixPalindrome];
    
    if (mNode.length == 1) {
      mNode.suffixLink = FAKE_ROOT_0;
      mNode.count = 1;
      return true;
    }
    
    while (true) {
      curNode = node[curNode].suffixLink;
      curLength = node[curNode].length;
      if (pos - 1 - curLength >= 0 && s[pos - 1 - curLength] == s[pos]) {
        mNode.suffixLink = node[curNode].getNextNode(letter);
        break;
      }
    }
    
    mNode.count = 1 + node[mNode.suffixLink].count;
    
    return true;
  }
public:
  template <class Iterator> PalindromicTree(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; ++it) {
      s.push_back(*it);
    }
    
    n = (int) s.size();
    
    newNode(-1, FAKE_ROOT_MINUS_1);
    newNode(0, FAKE_ROOT_MINUS_1);
    
    maxSuffixPalindrome = FAKE_ROOT_0;
    
    for_inc(i, n) {
      addLetter(i);
    }
  }
  
  int getLongestPalindromicSubstringLength() {
    int ans = 0;
    for (auto &p: node) {
      ans = max(ans, p.length);
    }
    return ans;
  }
  
  int getNumberOfDistinctPalindromicSubstrings() {
    return (int) node.size() - 2;
  }
  
  int64 getNumberOfPalindromicSubstrings() {
    int64 ans = 0;
    for (auto &p: node) {
      ans += p.count;
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  

  string s;
  cin >> s;
  
  int n = (int) s.size();
  vector<char> st(n);
  for_inc(i, n) {
    st[i] = s[i] - 'a';
  }
  
  PalindromicTree<char> tree(st.begin(), st.end());
  
  cout << tree.getNumberOfPalindromicSubstrings() << endl;
  
  return 0;
}
