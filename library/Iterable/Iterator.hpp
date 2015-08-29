#include "global.hpp"

#ifndef ITERATOR_H
#define ITERATOR_H

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

template <class T, class UnaryPredicate> bool all(const Iterable<T> &iterable, const UnaryPredicate &pred) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        if (!pred(it->next())) {
            return false;
        }
    }
    return true;
}

template <class T> bool unique(const Iterable<T> &iterable) {
    auto it = iterable.iterator();
    bool first = true;
    T val;
    while (it->hasNext()) {
        T x = it->next();
        if (first) {
            val = x;
            first = false;
        } else {
            if (val != x) {
                return false;
            }
        }
    }
    return true;
}

template <class IN, class OUT> class MapIterator : public Iterator<OUT> {
    Iterator<IN> &in;
    const function<OUT(IN)> &mapper;

public:
    MapIterator(Iterator<IN> &in, const function<OUT(IN)> &mapper):in(in), mapper(mapper) {}

    virtual bool hasNext() const {
        return in.hasNext();
    }

    virtual OUT next() {
        return mapper(in.next());
    }
};

template <class IN, class OUT> class MapIterable : public Iterable<OUT> {
    const Iterable<IN> &in;
    const function<OUT(IN)> &mapper;
public:
    MapIterable(const Iterable<IN> &in, const function<OUT(IN)> &mapper):in(in), mapper(mapper) {}
    virtual Iterator<OUT>* iterator() const {
        return new MapIterator<IN, OUT>(*in.iterator(), mapper);
    }
};

template <class IN, class OUT> MapIterable<IN, OUT> mapIterable(const Iterable<IN> &iterable, const function<OUT(IN)> &mapper) {
    return MapIterable<IN, OUT>(iterable, mapper);
}

template <class T, class ITERATOR> class StdIterator : public Iterator<T> {
    const ITERATOR &begin, &end;
    ITERATOR it;

public:
    StdIterator(const ITERATOR &begin, const ITERATOR &end): begin(begin), end(end), it(begin) {}

    virtual bool hasNext() const {
        return it != end;
    }

    virtual T next() {
        T ret = *it;
        it++;
        return ret;
    }
};

template <class T, class ITERATOR> class StdIterable : public Iterable<T> {
    const ITERATOR &begin, &end;
public:
    StdIterable(const ITERATOR &begin, const ITERATOR &end): begin(begin), end(end) {}
    virtual Iterator<T>* iterator() const {
        return new StdIterator<T, ITERATOR>(begin, end);
    }
};

template <class T, class ITERATOR> StdIterable<T, ITERATOR> stdIterable(const ITERATOR &begin, const ITERATOR &end) {
    return StdIterable<T, ITERATOR>(begin, end);
};

template <class T> T aggregate(const Iterable<T> &iterable, const function<T(T, T)> &aggregator) {
    auto it = iterable.iterator();
    bool first = true;
    T ret;
    while (it->hasNext()) {
        if (first) {
            ret = it->next();
            first = false;
        } else {
            ret = aggregator(ret, it->next());
        }
    }
    return ret;
}

template <class T> vector<T> collect(const Iterable<T> &iterable) {
    auto it = iterable.iterator();
    vector<T> vec;
    while (it->hasNext()) {
        vec.push_back(it->next());
    }
    return vec;
}

template <class T> T aggregateMax(const Iterable<T> &iterable) {
    return aggregate<T>(iterable, [](const T &a, const T &b) {return max(a, b);});
}
#endif