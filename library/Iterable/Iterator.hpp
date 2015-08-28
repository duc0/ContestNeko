#include "global.hpp"

template <class T> class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

template <class T> class Iterable {
public:
    virtual Iterator<T>* iterator() const = 0;
};


template <class T, class UnaryPredicate> bool any(const Iterable<T> &iterable, const UnaryPredicate &pred) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        if (pred(it->next())) {
            return true;
        }
    }
    return false;
}