#include "../global.hpp"

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


