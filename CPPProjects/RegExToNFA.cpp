//#define SUBMIT

#define C11

#ifdef SUBMIT
#define LOGLEVEL 0
//#define NDEBUG
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

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

class DirectedGraph {
  vector<vector<int>> nodeFrom;
  vector<vector<int>> nodeTo;
  vector<int> degIn, degOut;
  vector<bool> erase;
  int _minNode, _maxNode;
public:
  void init(bool zeroBased, int n) {
    if (zeroBased) {
      _minNode = 0;
      _maxNode = n - 1;
    } else {
      _minNode = 1;
      _maxNode = n;
    }
    nodeFrom.resize(_maxNode + 1);
    nodeTo.resize(_maxNode + 1);
    degIn.resize(_maxNode + 1);
    degOut.resize(_maxNode + 1);
    erase.resize(_maxNode + 1);
    for_inc_range(u, _minNode, _maxNode) {
      degIn[u] = 0;
      degOut[u] = 0;
      nodeFrom[u].clear();
      nodeTo[u].clear();
      erase[u] = false;
    }
  }
  
  int getSize() const {
    return _maxNode - _minNode + 1;
  }
  
  void addEdge(int u, int v) {
    nodeFrom[u].push_back(v);
    degOut[u]++;
    
    nodeTo[v].push_back(u);
    degIn[v]++;
  }
  
  const vector<int> getNodeFrom(int u) const {
    vector<int> r;
    for (auto &v: nodeFrom[u]) {
      if (!erase[v]) {
        r.push_back(v);
      }
    }
    return r;
  }
  
  const vector<int> getNodeTo(int u) const {
    vector<int> r;
    for (auto &v: nodeTo[u]) {
      if (!erase[v]) {
        r.push_back(v);
      }
    }
    return r;
    
  }
  
  int getDegIn(int u) const {
    assert(!erase[u]);
    return degIn[u];
  }
  
  int getDegOut(int u) const {
    assert(!erase[u]);
    return degOut[u];
  }
  
  void removeNode(int u) {
    assert(!erase[u]);
    for (auto &v: getNodeFrom(u)) {
      degIn[v]--;
    }
    for (auto &v: getNodeTo(u)) {
      degOut[v]--;
    }
    erase[u] = true;
  }
};

// Convert a regex to NFA of epsilon transitions
// Each node corresponds to an index in the regex
// If regex[i] is a character, there's an implicit edge
// from i to i + 1 that is not added to the graph
class RegExToNFA {
  DirectedGraph g;
  string regex;
  
  static string preprocess(const string &s) {
    ostringstream ss;
    ss << "(";
    ss << s;
    ss << ")";
    return ss.str();
  }
  
public:
  RegExToNFA(const string &iregex) {
    regex = preprocess(iregex);
    int n = (int) regex.length();
    g.init(true, n + 1);
    stack<int> s;
    for_inc(i, n) {
      int t = i;
      if (regex[i] == '(' || regex[i] == '|') {
        s.push(i);
      } else if (regex[i] == ')') {
        vector<int> orIdx;
        while (regex[s.top()] == '|') {
          orIdx.push_back(s.top());
          s.pop();
        }
        int start = s.top();
        s.pop();
        assert(regex[start] == '(');
        
        for (int k : orIdx) {
          g.addEdge(start, k + 1);
          g.addEdge(k, i);
        }
        t = start;
      }
      if (i < n - 1 && regex[i + 1] == '*') {
        g.addEdge(t, i + 1);
        g.addEdge(i + 1, t);
      }
      if (regex[i] == '(' || regex[i] == '*' || regex[i] == ')') {
        g.addEdge(i, i + 1);
      }
    }
  }
  
  const string &getPreprocessedRegex() const {
    return regex;
  }
  
  const DirectedGraph &getNFA() const {
    return g;
  }
};
void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

void testNFA(const string& regex) {
  RegExToNFA converter(regex);
  const DirectedGraph &g = converter.getNFA();
  int n = g.getSize();
  LOG(1, "** NFA for " << "(" << regex << ") :");
  LOG(1, "Number of nodes " << n);
  for_inc(u, n) {
    for (auto &v: g.getNodeFrom(u)) {
      LOG(1, "Edge: " << u << " " << v );
    }
  }
}

bool visit[130][2050];

int solve(const string &regex, int minLen) {
  fill0(visit);
  
  //testNFA(regex);
  RegExToNFA converter(regex);
  const DirectedGraph &g = converter.getNFA();
  
  string s = converter.getPreprocessedRegex();
  deque<pair<int, int>> q;
  q.push_back(make_pair(0, 0));
  visit[0][0] = true;
  int targetNode = (int)s.length() - 1;
  int lastDist = 0;
  while (!q.empty()) {
    pair<int, int> cur = q.front();
    int curNode = cur.first;
    int curDist = cur.second;
    LOG(2, "Cur " << curNode << " " << curDist);
    if (curDist < lastDist) {
      //      exit(0);
    }
    lastDist = curDist;
    if (cur.first == targetNode && curDist >= minLen) {
      if (curDist > 500) {
        return -1;
      }
      return curDist;
    }
    q.pop_front();
    for (auto &nextNode: g.getNodeFrom(curNode)) {
      int nextDist = cur.second;
      if (!visit[nextNode][nextDist]) {
        q.push_front(make_pair(nextNode, nextDist));
        visit[nextNode][nextDist] = true;
      }
    }
    
    if (curNode < targetNode && s[curNode] != '(' && s[curNode] != ')' && s[curNode] != '|' && s[curNode] != '*') {
      int nextNode = curNode + 1;
      int nextDist = cur.second + 1;
      if (!visit[nextNode][nextDist]) {
        q.push_back(make_pair(nextNode, nextDist));
        visit[nextNode][nextDist] = true;
      }
    }
  }
  return -1;
}

// CISCO 2015 Smallest Regex Match String
int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  testNFA("");
  testNFA("a");
  testNFA("ab");
  testNFA("c(a|b*)");
  testNFA("(a|b)*");
  testNFA("a|b|c");
  
  int nTest;
  cin >> nTest;
  repeat(nTest) {
    int minLen;
    cin >> minLen;
    string regex;
    cin >> regex;
    int ans = solve(regex, minLen);
    assert(ans <= 500);
    cout << ans << endl;
  }
  return 0;
}
