#include "global.hpp"

#ifndef MATH_H
#define MATH_H

namespace math {
// Compute a^n in log(n)
    template<class T>
    T power(const T &a, int n) {
        assert(n >= 1);
        if (n == 1) {
            return a;
        } else if (n % 2 == 0) {
            T tmp = power(a, n / 2);
            return tmp * tmp;
        } else {
            return a * power(a, n - 1);
        }
    }
}

#endif