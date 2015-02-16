#include <cstdio>
#include <algorithm>
#include <cstring>

#define NDEBUG
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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)

#define for_inc(i,x) for(auto i=0; i < x;++i)
#define for_dec(i,x) for(auto i=x-1; i >= 0; --i)
#define for_inc_range(i,x,y) for (auto i=x; i<=y; ++i)
#define for_dec_range(i,x,y) for (auto i=x; i>=y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

void testGen() {
  freopen("biginput2.txt", "w", stdout);
  cout << 10000 << endl;
  repeat(10000) {
    cout << 1 << " " << 2 << endl;
  }
  cout << 10000 << endl;
  repeat(10000) {
    cout << 1 << " " << 2 << " " << 1 << endl;
  }
  fclose(stdout);
}

struct interval_part {
  int l, r, id;
  
  bool operator < (const interval_part &other) const {
    if (l < other.l) {
      return true;
    }
    if (l == other.l && r > other.r) {
      return true;
    }
    if (l == other.l && r == other.r) {
      return id < other.id;
    }
    return false;
  }
};


struct interval_actor {
  int l, r, id;
  
  bool operator < (const interval_actor &other) const {
    if (r < other.r) {
      return true;
    }
    if (r == other.r && l > other.l) {
      return true;
    }
    if (r == other.r && l == other.l) {
      return id < other.id;
    }
    return false;
  }
};

int nActor, nPart;

#define MAXN 100100

interval_part part[MAXN];
interval_actor actor[MAXN];
int cap[MAXN];

set<interval_actor> avail_actor;

int assignment[MAXN];

bool compLeft(const interval_actor &i1, const interval_actor &i2) {
  if (i1.l < i2.l) {
    return true;
  }
  if (i1.l == i2.l && i1.r > i2.r) {
    return true;
  }
  if (i1.l == i2.l && i1.r == i2.r) {
    return i1.id < i2.id;
  }

  return false;
}

int main() {
  //testGen();
  freopen("input4.txt", "r", stdin);
  
  scanf("%d", &nPart);
  for_inc_range(i, 1, nPart) {
    scanf("%d%d", &part[i].l, &part[i].r);
    part[i].id = i;
  }
  
  scanf("%d", &nActor);
  for_inc_range(i, 1, nActor) {
    scanf("%d%d%d", &actor[i].l, &actor[i].r, &cap[i]);
    actor[i].id = i;
  }
  
  sort(part + 1, part + nPart + 1);
  sort(actor + 1, actor + nActor + 1, compLeft);
  
  int avail_actor_id = 0;
  for_inc_range(i, 1, nPart) {
    while (avail_actor_id + 1 <= nActor && actor[avail_actor_id + 1].l <= part[i].l) {
      avail_actor.insert(actor[avail_actor_id + 1]);
      avail_actor_id++;
    }
    interval_actor a;
    a.l = part[i].l;
    a.r = part[i].r;
    a.id = 0;
    auto x = avail_actor.lower_bound(a);
    //cout << avail_actor.size() << endl;
    if (x == avail_actor.end()) {
      cout << "NO" << endl;
      return 0;
    }
    assignment[part[i].id] = x->id;
    cap[x->id]--;
    if (cap[x->id] == 0) {
      avail_actor.erase(*x);
    }
  }
  
  cout << "YES" << endl;
  for_inc_range(i, 1, nPart) {
    cout << assignment[i] << " ";
  }
  cout << endl;
  
  return 0;
}