#include <stdio.h>

template <int base = 10> class BigInteger {
  vector<int> d;
  bool isInfinity = false;
  
  inline int getDigit(int i) const { return i >= d.size() ? 0 : d[i]; }
  
public:
  static BigInteger getMaxValue() {
    BigInteger r;
    r.isInfinity = true;
    return r;
  }
  
  template <class Iterator> BigInteger(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; ++it) {
      d.push_back(*it);
    }
    reverse(d.begin(), d.end());
  }
  
  BigInteger() : BigInteger(0) {}
  
  template <class T> BigInteger(T n) {
    if (n == 0) {
      d.push_back(0);
      return;
    }
    while (n > 0) {
      d.push_back(n % base);
      n /= base;
    }
  }
  
  BigInteger operator+(const BigInteger &a) {
    BigInteger r;
    size_t m = max(d.size(), a.d.size());
    r.d.resize(m + 1);
    for (int i = 0, c = 0; i < m + 1; ++i) {
      r.d[i] = getDigit(i) + a.getDigit(i) + c;
      if (r.d[i] >= base) {
        c = 1;
        r.d[i] -= base;
      } else
        c = 0;
    }
    return r;
  }
  
  template <class T> T mod(T p) {
    T r = 0;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
      r = (r * base + *it) % p;
    }
    return r;
  }
  
  bool operator<(const BigInteger &a) const {
    if (a.isInfinity) {
      return true;
    }
    if (isInfinity) {
      return false;
    }
    size_t m = max(d.size(), a.d.size());
    for (int i = (int)m - 1; i >= 0; --i) {
      if (getDigit(i) < a.getDigit(i))
        return true;
      if (getDigit(i) > a.getDigit(i))
        return false;
    }
    return false;
  }
  
  string toString() {
    string s;
    for (auto it = d.rbegin(); it != d.rend(); ++it) {
      s += (char)(*it + '0');
    }
    return s;
  }
};