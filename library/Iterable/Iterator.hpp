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
    virtual unique_ptr<Iterator<T>> iterator() const = 0;
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
    unique_ptr<Iterator<IN>> in;
    const function<OUT(IN)> &mapper;

public:
    MapIterator(unique_ptr<Iterator<IN>> in, const function<OUT(IN)> &mapper):in(move(in)), mapper(mapper) {}

    virtual bool hasNext() const {
        return in->hasNext();
    }

    virtual OUT next() {
        return mapper(in->next());
    }
};

template <class IN, class OUT> class MapIterable : public Iterable<OUT> {
    const Iterable<IN> &in;
    const function<OUT(IN)> &mapper;
public:
    MapIterable(const Iterable<IN> &in, const function<OUT(IN)> &mapper):in(in), mapper(mapper) {}
    virtual unique_ptr<Iterator<OUT>> iterator() const {
        return unique_ptr<Iterator<OUT>>(new MapIterator<IN, OUT>(in.iterator(), mapper));
    }
};

template <class IN, class OUT> MapIterable<IN, OUT> mapIterable(const Iterable<IN> &iterable, const function<OUT(IN)> &mapper) {
    return MapIterable<IN, OUT>(iterable, mapper);
}

template <class T> class FilterIterator : public Iterator<T> {
    unique_ptr<Iterator<T>> in;
    const function<bool(T)> &pred;
    T nextElement;
    bool hasNextElement;

    void findNext() {
        hasNextElement = false;
        while (in->hasNext()) {
            nextElement = in->next();
            if (pred(nextElement)) {
                hasNextElement = true;
                break;
            }
        }
    }
public:
    FilterIterator(unique_ptr<Iterator<T>> in, const function<bool(T)> &pred):in(move(in)), pred(pred) {
       findNext();
    }

    virtual bool hasNext() const {
        return hasNextElement;
    }

    virtual T next() {
        T ret = nextElement;
        findNext();
        return ret;
    }
};

template <class T> class FilterIterable : public Iterable<T> {
    const Iterable<T> &in;
    const function<bool(T)> &pred;
public:
    FilterIterable(const Iterable<T> &in, const function<bool(T)> &pred):in(in), pred(pred) {}
    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new FilterIterator<T>(in.iterator(), pred));
    }
};

template <class T> FilterIterable<T> filter(const Iterable<T> &iterable, const function<bool(T)> &filter) {
    return FilterIterable<T>(iterable, filter);
}

template <class IN1, class IN2, class OUT> class ProductIterator : public Iterator<OUT> {
    const Iterable<IN1> &in1;
    const Iterable<IN2> &in2;

    unique_ptr<Iterator<IN1>> in1Iter;
    unique_ptr<Iterator<IN2>> in2Iter;
    const function<OUT(IN1, IN2)> &mapper;
    IN1 cur1;
    IN2 cur2;
    OUT nextElement;
    bool hasNextElement;

    void findNext() {
        if (in2Iter->hasNext()) {
            cur2 = in2Iter->next();
            nextElement = mapper(cur1, cur2);
            hasNextElement = true;
        } else {
            if (in1Iter->hasNext()) {
                cur1 = in1Iter->next();
                in2Iter = in2.iterator();
                findNext();
            } else {
                hasNextElement = false;
            }
        }
    }
public:
    ProductIterator(const Iterable<IN1> &in1, const Iterable<IN2> &in2, const function<OUT(IN1, IN2)> &mapper):in1(in1), in2(in2), mapper(mapper) {
        in1Iter = in1.iterator();
        if (in1Iter->hasNext()) {
            cur1 = in1Iter->next();
            in2Iter = in2.iterator();
            findNext();
        } else {
            hasNextElement = false;
        }
    }

    virtual bool hasNext() const {
        return hasNextElement;
    }

    virtual OUT next() {
        OUT ret = nextElement;
        findNext();
        return ret;
    }
};

template <class IN1, class IN2, class OUT> class ProductIterable : public Iterable<OUT> {
    const Iterable<IN1> &in1;
    const Iterable<IN2> &in2;
    const function<OUT(IN1, IN2)> &mapper;
public:
    ProductIterable(const Iterable<IN1> &in1, const Iterable<IN2> &in2, const function<OUT(IN1, IN2)> &mapper):in1(in1), in2(in2), mapper(mapper) {}
    virtual unique_ptr<Iterator<OUT>> iterator() const {
        return unique_ptr<Iterator<OUT>>(new ProductIterator<IN1, IN2, OUT>(in1, in2, mapper));
    }
};

template <class IN1, class IN2, class OUT> ProductIterable<IN1, IN2, OUT> product(const Iterable<IN1> &in1, const Iterable<IN2> &in2, const function<OUT(IN1, IN2)> &mapper) {
    return ProductIterable<IN1, IN2, OUT>(in1, in2, mapper);
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
    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new StdIterator<T, ITERATOR>(begin, end));
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


template <class T> void forEach(const Iterable<T> &iterable, const function<void(T)> &f) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        f(it->next());
    }
}

template <class T> void printInterable(const Iterable<T> &iterable) {
    auto it = iterable.iterator();
    while (it->hasNext()) {
        LOG(1, it->next() << " ");
    }
    LOG(1, endl);
}

template <class T> T aggregateMax(const Iterable<T> &iterable) {
    return aggregate<T>(iterable, [](const T &a, const T &b) {return max(a, b);});
}

template <class T> T aggregateSum(const Iterable<T> &iterable) {
    return aggregate<T>(iterable, [](const T &a, const T &b) {return a + b;});
}

template<class T> using predicate = function<bool(T)>;

#endif