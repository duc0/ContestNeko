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
  freopen("input5.txt", "w", stdout);
  
  int n = 100;
  for_inc(i, n) {
    char c = rand() % 4 + 'a';
    cout << c;
  }
  fclose(stdout);
}

template <class T, int AlphabetSize> class FixedAlphabetTreeNode {
  template <class TT, class NN> friend class PalindromicTree;
  
  int nextNode[AlphabetSize];
  int length = 0;
  int suffixLink = 0;
  int lazy = 0;
  int count = 0;
  
  FixedAlphabetTreeNode() {
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
  
  vector<T> getNextNodes() const {
    vector<T> ret;
    for_inc(c, AlphabetSize) {
      if (nextNode[c] != -1) {
        ret.push_back(c);
      }
    }
    return ret;
  }
  
public:
  int getCount() const {
    return count;
  }
  
  int getLength() const {
    return length;
  }
};

// A nice tree structure to store palindromic substrings.
// See http://adilet.org/blog/25-09-14/ for more details.
// Each node correspond to a palindromic substring and has data like
// length
// number of such substrings
// Construction: O(N)

template<class T, class TreeNode> class PalindromicTree {
  const int FAKE_ROOT_MINUS_1 = 0;
  const int FAKE_ROOT_0 = 1;
  vector<T> s;
  vector<TreeNode> node;
  int n;
  int maxSuffixPalindrome;
  
  int newNode(int length, int suffixLink) {
    TreeNode p;
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
      node[maxSuffixPalindrome].lazy ++;
      return false;
    }
    
    maxSuffixPalindrome = newNode(node[curNode].length + 2, FAKE_ROOT_MINUS_1);
    node[curNode].setNextNode(letter, maxSuffixPalindrome);
    
    TreeNode &mNode = node[maxSuffixPalindrome];
    
    if (mNode.length == 1) {
      mNode.suffixLink = FAKE_ROOT_0;
      mNode.lazy ++;
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
    
    mNode.lazy++;
    
    return true;
  }
  
  void propagateCount() {
    for_dec(i, (int) node.size()) {
      TreeNode &p = node[i];
      p.count += p.lazy;
      if (p.suffixLink > FAKE_ROOT_0) {
        node[p.suffixLink].lazy += p.lazy;
      }
    }
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
    
    propagateCount();
  }
  
  int getLongestPalindromicSubstringLength() const {
    int ans = 0;
    for (auto &p: node) {
      ans = max(ans, p.length);
    }
    return ans;
  }
  
  int getNumberOfDistinctPalindromicSubstrings() const {
    return (int) node.size() - 2;
  }
  
  int64 getNumberOfPalindromicSubstrings() const {
    int64 ans = 0;
    for (auto &p: node) {
      ans += p.count;
    }
    return ans;
  }
  
  const vector<TreeNode>& getNodes() const {
    return node;
  }
  
  void printAllDebug(int u, ostringstream &sb) const {
    LOG(1, "Current palindrome: " << sb.str() << ", count " << node[u].count << ", length: " << node[u].length);
    vector<T> next = node[u].getNextNodes();
    for(auto &c: next) {
      ostringstream sb2;
      char ch = c + 'a';
      if (u == FAKE_ROOT_MINUS_1) {
        sb2 << ch;
      } else {
        sb2 << ch << sb.str() << ch;
      }
      printAllDebug(node[u].getNextNode(c), sb2);
    }
  }
  
  void printAllDebug() const {
    ostringstream sb;
    printAllDebug(FAKE_ROOT_MINUS_1, sb);
  }
};

bool isPalindrome(string s) {
  int n = (int) s.length();
  for_inc(i, n) {
    if (s[i] != s[n - i - 1]) {
      return false;
    }
  }
  return true;
}

int solveSlow(string s) {
  int n = (int) s.length();
  int ret = 0;
  for_inc_range(l, 1, n) {
    for_inc(j, n - l + 1) {
      for_inc(i, j) {
        if (s.substr(i, l) == s.substr(j, l) && isPalindrome(s.substr(i, l))) {
          ++ret;
        }
      }
    }
  }
  return ret;
}

// Hackerrank w14 - Palindromic Border
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input5.txt", "r", stdin);
#endif
  
  string s;
  cin >> s;
  int n = (int) s.length();
  
  vector<char> st(n);
  for_inc(i, n) {
    st[i] = s[i] - 'a';
  }
  
  PalindromicTree<char, FixedAlphabetTreeNode<char, 26>> tree(st.begin(), st.end());
  
  int64 ans = 0;
  for (auto &p: tree.getNodes()) {
    int64 c = p.getCount();
    if (c > 1) {
      ans = (ans + c * (c - 1) / 2) % MOD;
    }
  }
  
  cout << ans << endl;
  //cout << solveSlow(s) << endl;
  
  return 0;
}
