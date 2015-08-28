#include "global.hpp"

// O(sqrt(n))
bool isPrime(int64 n) {
    for (int64 i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// O(sqrtn*logn)
set<int64> findDivisors(int64 n) {
    set<int64> ret;
    ret.insert(1);
    ret.insert(n);
    for (int64 i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ret.insert(i);
            ret.insert(n / i);
        }
    }
    return ret;
}

template <class T> void extendedEuclid(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    T x2;
    extendedEuclid(b, a % b, x2, x);
    y = x2 - (a / b) * x;
}

template <class T> T modulo(int64 a, T b) {
    T r = a % b;
    if (r < 0)
        r += b;
    return r;
}

template <class T> T modularInverse(T a, T m) {
    T x, y;
    extendedEuclid(a, m, x, y);
    return modulo(x, m);
}

template <class T> bool isPalindromic(T x) {
    int n = x;
    int rev = 0;
    while (n > 0)
    {
        int d = n % 10;
        rev = rev * 10 + d;
        n /= 10;
    }
    return x == rev;
}

