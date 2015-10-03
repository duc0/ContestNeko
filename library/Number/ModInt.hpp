#include "global.hpp"
#include "NumberTheory.hpp"

#ifndef MODINT_H
#define MODINT_H

template<class T, T M>
class ModInt {
    T x = 0;

    static inline T get(ModInt x) { return x.get(); }

    static inline T get(T x) { return x; }

public:
    ModInt() : ModInt(0) { }

    ModInt(int64 y) { x = modulo(y, M); }

    T get() const { return x; }

    template<class Q>
    ModInt operator+(const Q &y) const {
        return ModInt(x + get(y));
    }

    template<class Q>
    ModInt &operator+=(const Q &y) {
        x = modulo(x + get(y), M);
        return *this;
    }

    template<class Q>
    ModInt operator-(const Q &y) const {
        return ModInt(x - get(y));
    }

    template<class Q>
    ModInt &operator-=(const Q &y) {
        x = modulo(x - get(y), M);
        return *this;
    }

    template<class Q>
    bool operator!=(const Q &y) const {
        return x != get(y);
    }

    template<class Q>
    ModInt operator*(const Q &y) const {
        return ModInt((int64) x * get(y));
    }

    template<class Q>
    ModInt &operator*=(const Q &y) {
        x = modulo((int64) x * get(y), M);
        return *this;
    }

    template<class Q>
    ModInt operator/(const Q &y) const {
        return ModInt(
                (int64) x * modularInverse(get(y), MOD));
    }

    template<class Q>
    ModInt &operator/=(const Q &y) {
        x = modulo((int64) x * modularInverse(get(y), MOD), M);
        return *this;
    }

    ModInt &operator=(const T &y) {
        x = modulo(y, M);
        return *this;
    }

    ModInt &operator=(const ModInt &y) {
        x = y.x;
        return *this;
    }

    template<class Q>
    bool operator==(const Q &y) const {
        return x == get(y);
    }

    template<class Q>
    bool operator>(const Q &y) const {
        return x > get(y);
    }

    template<class Q>
    bool operator>=(const Q &y) const {
        return x >= get(y);
    }

    template<class Q>
    bool operator<(const Q &y) const {
        return x < get(y);
    }

    template<class Q>
    bool operator<=(const Q &y) const {
        return x <= get(y);
    }

    friend std::ostream &operator<<(std::ostream &stream, const ModInt &val) {
        stream << get(val);
        return stream;
    }
};

#endif