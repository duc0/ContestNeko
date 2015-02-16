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

struct interval {
  int l, r, id;
};

struct comp_left {
  bool operator () (const interval &i1, const interval &i2) const {
    if (i1.l < i2.l) return true;
    if (i1.l > i2.l) return false;
    if (i1.r > i2.r) return true;
    if (i1.r < i2.r) return false;
    return i1.id < i2.id;
  }
};

struct comp_right {
  bool operator () (const interval &i1, const interval &i2) const {
    if (i1.r < i2.r) return true;
    if (i1.r > i2.r) return false;
    if (i1.l > i2.l) return true;
    if (i1.l < i2.l) return false;
    return i1.id < i2.id;
  }
};

int nActor, nPart;

#define MAXN 100100

interval part[MAXN];
interval actor[MAXN];
int cap[MAXN];

set<interval, comp_right> avail_actor;

int assignment[MAXN];

int main() {
  //testGen();
  //freopen("input1.txt", "r", stdin);
  
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
  
  sort(part + 1, part + nPart + 1, comp_left());
  sort(actor + 1, actor + nActor + 1, comp_left());
  
  int avail_actor_id = 0;
  
  // Assign each part according to the part ordering
  for_inc_range(i, 1, nPart) {
    while (avail_actor_id + 1 <= nActor && actor[avail_actor_id + 1].l <= part[i].l) {
      avail_actor.insert(actor[avail_actor_id + 1]);
      avail_actor_id++;
    }
    interval a;
    a.l = part[i].l;
    a.r = part[i].r;
    a.id = 0;
    
    // Greedy assignment: find the min actor x (according to the actor ordering) that can do this part.
    auto x = avail_actor.lower_bound(a);
    if (x == avail_actor.end()) {
      // We can prove that if there is no greedy assignment for this part, there is no solution
      // Prove by contradiction. Assume that there is a solution. I.e. there must be
      // an augmenting path. Let this part be X. Since there's an augmenting path, there will
      // be two actors A, B and another part Y such that A can do both X and Y; Y is currently
      // assigned to A. B can do Y and B still has capacity. But from the ordering, we can show that
      // B can do X as well, so the greedy assignment must have assigned X to B.
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