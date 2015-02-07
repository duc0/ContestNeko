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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(a, 0, sizeof(a))

void testGen() {
  freopen("biginput1.txt", "w", stdout);
}

#define MAXN 10

#define real double

int n, l[MAXN], r[MAXN], minL, maxR;

real pickGreater(int l, int r, int p) {
  if (r <= p) {
    return 0;
  }
  if (l > p) {
    return 1;
  }
  return ((real)r - p) / ((real)r - l + 1);
}

real pickGEQ(int l, int r, int p) {
  if (r < p) {
    return 0;
  }
  if (l >= p) {
    return 1;
  }
  return ((real)r - p + 1) / ((real) r - l + 1);
}

real pickSmaller(int l, int r, int p) {
  return 1 - pickGEQ(l, r, p);
}

real pickSEQ(int l, int r, int p) {
  return 1 - pickGreater(l, r, p);
}

real pickEQ(int l, int r, int p) {
  if (l <= p && p <= r) {
    return ((real) 1 / ((real) r - l + 1));
  } else {
    return 0;
  }
}

int main() {
  //testGen();
  //freopen("input2.txt", "r", stdin);
  
  cin >> n;
  
  for (int i = 1; i <= n; ++i) {
    cin >> l[i] >> r[i];
  }
  
  minL = l[1]; maxR = r[1];
  for (int i = 1; i <= n; ++i) {
    minL = min(minL, l[i]);
    maxR = max(maxR, r[i]);
  }
  
  real ret = 0;
  for (int p = minL; p <= maxR; ++p) {
    // p : second bid
    real prob = 0;
    
    // Case: winner bid more than p
    for (int winner = 1; winner <= n; ++winner) {
      real prob_winner = pickGreater(l[winner], r[winner], p);
      if (prob_winner == 0) {
        continue;
      }
      bool cont = false;
      real total_prob_leq = 1;
      real total_prob_le = 1;
      for (int i = 1; i <= n; ++i) if (i != winner) {
        real prob_leq = pickSEQ(l[i], r[i], p);
        if (prob_leq == 0) {
          cont = true;
          break;
        }
        real prob_le = pickSmaller(l[i], r[i], p);
        total_prob_leq *= prob_leq;
        total_prob_le *= prob_le;
      }
      if (cont) continue;
      real prob_case = prob_winner * (total_prob_leq - total_prob_le);
      prob += prob_case;
    }
    
    // Case: winner bid p
    // There must be at least two winners bid p
    for (int winner1 = 1; winner1 < n; ++winner1) {
      real prob_winner1 = pickEQ(l[winner1], r[winner1], p);
      if (prob_winner1 == 0) {
        continue;
      }
      for (int winner2 = winner1 + 1; winner2 <= n; ++winner2) {
        real prob_winner2 = pickEQ(l[winner2], r[winner2], p);
        if (prob_winner2 == 0) {
          continue;
        }
        bool cont = false;
        real prob_case = prob_winner1 * prob_winner2;
        for (int i = 1; i < winner1; ++i) {
          real prob_le = pickSmaller(l[i], r[i], p);
          if (prob_le == 0) {
            cont = true;
            break;
          }
          prob_case *= prob_le;
        }
        if (cont) continue;
        for (int i = winner1 + 1; i < winner2; ++i) {
          real prob_le = pickSmaller(l[i], r[i], p);
          if (prob_le == 0) {
            cont = true;
            break;
          }
          prob_case *= prob_le;
        }
        if (cont) continue;
        for (int i = winner2 + 1; i <= n; ++i) {
          real prob_leq = pickSEQ(l[i], r[i], p);
          if (prob_leq == 0) {
            cont = true;
            break;
          }
          prob_case *= prob_leq;
        }
        if (cont) continue;
        prob += prob_case;
      }
    }
    
    ret += prob * p;
  }

  printf("%.10lf\n", ret);
  return 0;
}