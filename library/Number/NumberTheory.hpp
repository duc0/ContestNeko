#include "global.hpp"
#include "Iterator.hpp"

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

template <class T> class DivisorIterator : public Iterator<T> {
    T cur, next_, n;

public:
    DivisorIterator(T n) {
        assert(n > 0);
        this->n = n;
        cur = 0;
        next_ = 1;
    }

    virtual bool hasNext() const {
        return next_ != -1;
    }

    virtual T next() {
        cur = next_;
        if (next_ * next_ < n) {
            next_ = n / next_;
        } else if (next_ * next_ == n) {
            next_ = -1;
        } else {
            next_ = n / next_ + 1;
            bool found = false;
            while (next_ * next_ <= n) {
                if (n % next_ == 0) {
                    found = true;
                    break;
                }
                next_++;
            }
            if (!found) {
                next_ = -1;
            }
        }
        return cur;
    }
};

template <class T> class DivisorIterable : public Iterable<T> {
    T n;
public:
    DivisorIterable(T n) {
        this->n = n;
    }
    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new DivisorIterator<T>(n));
    }
};

template <class T> DivisorIterable<T> divisors(T n) {
    return DivisorIterable<T>(n);
}

template <class T> class DigitIterator : public Iterator<T> {
    T n;

public:
    DigitIterator(T n) {
        assert(n > 0);
        this->n = n;
    }

    virtual bool hasNext() const {
        return n > 0;
    }

    virtual T next() {
        T ret = n % 10;
        n /= 10;
        return ret;
    }
};

template <class T> class DigitIterable : public Iterable<T> {
    T n;
public:
    DigitIterable(T n) {
        this->n = n;
    }
    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new DigitIterator<T>(n));
    }
};

template <class T> DigitIterable<T> digits(T n) {
    return DigitIterable<T>(n);
}

template <class T> class RangeIterator : public Iterator<T> {
    T begin, end, step, cur;
    bool goUp;

public:
    RangeIterator(T begin, T end, T step): begin(begin), end(end), step(step), cur(begin), goUp(begin <= end) {}

    virtual bool hasNext() const {
        return goUp? (cur <= end) : (cur >= end);
    }

    virtual T next() {
        T ret = cur;
        if (goUp) {
            cur += step;
        } else {
            cur -= step;
        }
        return ret;
    }
};

template <class T> class RangeIterable : public Iterable<T> {
    T begin, end, step;
public:
    RangeIterable(T begin, T end, T step): begin(begin), end(end), step(step) {}

    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new RangeIterator<T>(begin, end, step));
    }
};

template <class T> RangeIterable<T> range(T begin, T end, T step) {
    return RangeIterable<T>(begin, end, step);
}

template <class T> RangeIterable<T> range(T begin, T end) {
    return RangeIterable<T>(begin, end, 1);
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

