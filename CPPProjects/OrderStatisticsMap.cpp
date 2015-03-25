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

#define LOG(l, x)                                                              \
if (l <= LOGLEVEL)                                                           \
cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L
#define MOD 1000000007
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0)
    r += MOD;
  return r;
}

#include <vector>
#include <queue>
#include <iostream>
#include <functional>
#include <string>
using namespace std;

template <class K, class V, class Comparator = less<K>>
struct OrderStatisticsMap {
  // Treap implementation
  struct Node {
    K key;
    V value;
    int p, l, r, size;
  };
  vector<Node> node;
  queue<int> trash;
  Comparator isLess;
  int root;
  
  inline void newNode() {
    if (trash.empty())
      node.push_back(Node());
  }
  
  inline int getNewNode() {
    if (trash.empty())
      return (int)node.size() - 1;
    int t = trash.front();
    trash.pop();
    return t;
  }
  
  inline void eraseNode(int p) { trash.push(p); }
  
  bool isLessNode(int i, int j) const {
    if (j == -1)
      return i != -1;
    return i != -1 && node[i].p < node[j].p;
  }
  
  void update(int p) {
    if (p == -1)
      return;
    node[p].size = 1;
    if (node[p].l != -1)
      node[p].size += node[node[p].l].size;
    if (node[p].r != -1)
      node[p].size += node[node[p].r].size;
  }
  
  void rotateLeft(int &p) {
    int q = node[p].l;
    node[p].l = node[q].r;
    node[q].r = p;
    update(p);
    p = q;
  }
  
  void rotateRight(int &p) {
    int q = node[p].r;
    node[p].r = node[q].l;
    node[q].l = p;
    update(p);
    p = q;
  }
  
  int put(int p, const K &key, const V &value) {
    if (p == -1) {
      newNode();
      p = getNewNode();
      node[p].l = node[p].r = -1;
      node[p].size = -1;
      node[p].p = rand();
      node[p].key = key;
      node[p].value = value;
    } else if (isLess(key, node[p].key)) {
      int tmp = put(node[p].l, key, value);
      node[p].l = tmp;
      if (isLessNode(node[p].l, p))
        rotateLeft(p);
    } else if (isLess(node[p].key, key)) {
      int tmp = put(node[p].r, key, value);
      node[p].r = tmp;
      if (isLessNode(node[p].r, p))
        rotateRight(p);
    }
    update(p);
    return p;
  }
  
  bool erase(int &p, const K &key) {
    if (p == -1)
      return false;
    bool ret;
    if (isLess(key, node[p].key))
      ret = erase(node[p].l, key);
    else if (isLess(node[p].key, key))
      ret = erase(node[p].r, key);
    else {
      if (node[p].l == -1 && node[p].r == -1) {
        eraseNode(p);
        p = -1;
        ret = true;
      } else if (isLessNode(node[p].l, node[p].r)) {
        rotateLeft(p);
        ret = erase(node[p].r, key);
      } else {
        rotateRight(p);
        ret = erase(node[p].l, key);
      }
    }
    update(p);
    return ret;
  }
  
  int orderOfKey(int p, const K &key) const {
    if (p == -1)
      return 0;
    if (!isLess(node[p].key, key))
      return orderOfKey(node[p].l, key);
    return orderOfKey(node[p].r, key) + 1 +
    ((node[p].l != -1) ? node[node[p].l].size : 0);
  }
  
  K findByOrder(int p, int rank) const {
    int t = 0;
    if (node[p].l != -1)
      t = node[node[p].l].size;
    if (rank < t)
      return findByOrder(node[p].l, rank);
    rank -= t;
    if (rank == 0)
      return node[p].key;
    --rank;
    return findByOrder(node[p].r, rank);
  }
  
public:
  OrderStatisticsMap() { root = -1; }
  
  void clear() {
    node.clear();
    trash = queue<int>();
    root = -1;
  }
  
  void put(const K &key, const V &value) {
    int tmp = put(root, key, value);
    root = tmp;
  }
  
  size_t size() const {
    if (root == -1)
      return 0;
    return node[root].size;
  }
  
  bool empty() const { return size() == 0; }
  
  bool erase(const K &key) { return erase(root, key); }
  
  int orderOfKey(const K &key) const { return orderOfKey(root, key); }
  
  K findByOrder(int rank) const {
    assert(root != -1 && rank >= 0 && rank < node[root].size);
    return findByOrder(root, rank);
  }
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

// Example: TIMUS 1028

int main() {
#ifndef SUBMIT
  freopen("input1.txt", "r", stdin);
#endif
  int n;
  vector<pair<int, int>> a;
  cin >> n;
  repeat(n) {
    int x, y;
    cin >> x >> y;
    a.push_back(make_pair(x, y));
  }
  sort(a.begin(), a.end());
  OrderStatisticsMap<pair<int, int>, bool> s;
  vector<int> ret;
  ret.resize(n + 1);
  for (auto &p : a) {
    int rank = s.orderOfKey(make_pair(p.second, p.first));
    LOG(1, "Rank of " << p.first << ", " << p.second << ": " << rank);
    s.put(make_pair(p.second, p.first), true);
    LOG(1, "Find by order: " << s.findByOrder(0).first << "!");
    ret[rank]++;
  }
  for_inc_range(i, 0, n - 1) { cout << ret[i] << endl; }
  
  return 0;
}
