#include "global.hpp"

#ifndef COMBO_H
#define COMBO_H

// Usage:
// Construct comboUtils(n): Compute some combo numbers with up to n objects.

template<class T> class ComboUtils {
  vector<T> factorial;
  int maxN;
public:
  int getMaxN() const {
    return maxN;
  }
  
  ComboUtils(int n) {
    this->maxN = n;
    factorial.resize(n + 1);
    factorial[0] = 1;
    for_inc_range(i, 1, n) {
      factorial[i] = factorial[i - 1] * i;
    }
  }
  
  // Number of ways to choose k objects from n objects
  T C(int n, int k) const {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] / factorial[k] / factorial[n - k];
  }
  
  // Number of ways to choose k objects from n objects and ordering is important
  T A(int n, int k) const {
    assert (0 <= n && n <= maxN);
    if (k < 0 || k > n) return 0;
    return factorial[n] / factorial[n - k];
  }
  
  // Number of ways to arrange n objects
  T P(int n) const {
    assert (0 <= n && n <= maxN);
    return factorial[n];
  }
  
  // Number of ways to choose k objects from n objects, with repetition
  T repeatC(int n, int k) const {
    return C(n + k - 1, k);
  }
  
  // Return a vector c[i] = C(i, k) for i <= n, O(n)
  static vector<T> getCombByK(int n, int k) {
    vector<T> c(n + 1);
    c[k] = 1;
    for_inc_range(i, k + 1, n) {
      c[i] = c[i - 1] * i / (i - k);
    }
    return c;
  }
  
  // Return a vector c[i] = C(n, i) for i <= n, O(n)
  static vector<T> getCombByN(int n) {
    vector<T> c(n + 1);
    c[0] = 1;
    for_inc_range(i, 1, n) {
      c[i] = c[i - 1] * (n - i + 1)/ i;
    }
    return c;
  }
  
  // Return a vector p[i] = a^i for i <= n, O(n)
  static vector<T> getPower(int n, T a) {
    vector<T> p(n + 1);
    p[0] = 1;
    for_inc_range(i, 1, n) {
      p[i] = p[i - 1] * a;
    }
    return p;
  }
};

#endif