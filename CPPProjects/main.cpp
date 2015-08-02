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

// A segment tree with two queries:
// update(i, j, v): set Element[k] = max(Element[k], v) for all i <= k <= j
// queryMax(i, j)
// all 0 initially.
template<class T> struct TreeNode {
  int l, r;
  T v;
public:
  TreeNode(int l, int r, T v): l(l), r(r), v(v){}
};

template <class T> class MaxMaxTree {
  vector<TreeNode<T>> node;
  int minIndex, maxIndex;
  int root;
  
  int addNode(T v) {
    node.push_back(TreeNode<T>(-1, -1, v));
    return (int)node.size() - 1;
  }
  
  T queryMax(int l, int r, int curNodeId, int curNodeL, int curNodeR) {
    int mid = (curNodeL + curNodeR) / 2;
    T ret = node[curNodeId].v;
    if (l <= mid) {
      if (node[curNodeId].l != -1) {
        ret = max(ret, queryMax(l, r, node[curNodeId].l, curNodeL, mid));
      }
    }
    if (mid < r) {
      if (node[curNodeId].r != -1) {
        ret = max(ret, queryMax(l, r, node[curNodeId].r, mid + 1, curNodeR));
      }
    }
    return ret;
  }
  
  void update(int l, int r, T v, int curNodeId, int curNodeL, int curNodeR) {
    if (l <= curNodeL && curNodeR <= r) {
      node[curNodeId].v = max(node[curNodeId].v, v);
      return;
    }
    
    int m = (curNodeL + curNodeR) / 2;
    if (l <= m) {
      if (node[curNodeId].l == -1) {
        int tmp;
        tmp = addNode(node[curNodeId].v);
        node[curNodeId].l = tmp;
      }
      update(l, r, v, node[curNodeId].l, curNodeL, m);
    }
    
    if (r > m) {
      if (node[curNodeId].r == -1) {
        int tmp;
        tmp = addNode(node[curNodeId].v);
        node[curNodeId].r = tmp;
      }
      update(l, r, v, node[curNodeId].r, m + 1, curNodeR);
    }
    
    //merge(curNodeId);
  }
  
public:
  MaxMaxTree(int minIndex, int maxIndex) {
    root = addNode(0);
    this->minIndex = minIndex;
    this->maxIndex = maxIndex;
  }
  
  T queryMax(int l, int r) {
    return queryMax(l, r, 0, minIndex, maxIndex);
  }
  
  void update(int l, int r, T v) {
    update(l, r, v, 0, minIndex, maxIndex);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

int n, q;

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  //testGen();
  freopen("input1.txt", "r", stdin);
#endif
  cin >> n >> q;
  
  MaxMaxTree<int> maxRow(1, n), maxCol(1, n);
  set<int> usedX, usedY;
  for_inc_range(i, 1, q) {
    int x, y;
    string s;
    cin >> x >> y >> s;
    bool isUp = s[0] == 'U';
    int ret = 0;
    if (isUp) {
      if (!usedX.count(x)) {
        int maxy = maxCol.queryMax(x, x);
        LOG(1, "Query" << x << " " << x << " " << maxy);
        ret = y - maxy;
        maxRow.update(maxy + 1, y, x);
        usedX.insert(x);
      }
    } else {
      if (!usedY.count(y)) {
        int maxx = maxRow.queryMax(y, y);
        
        ret = x - maxx;
        LOG(1, " Update " << maxx + 1 << " " << x << " " << y);
        maxCol.update(maxx + 1, x, y);
        usedY.insert(y);
      }
    }
    cout << ret << endl;
  }
  
  return 0;
}
