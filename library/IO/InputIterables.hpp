#include "global.hpp"
#include "Iterator.hpp"

template <class T> class InputIterator : public Iterator<T> {
    int size;
    std::istream& in;

public:
    InputIterator(std::istream& in, int size):in(in), size(size) {}

    virtual bool hasNext() const {
        return size > 0;
    }

    virtual T next() {
        T x;
        in >> x;
        size--;
        return x;
    }
};

template <class T> class InputIterable : public Iterable<T> {
    int size;
    std::istream& in;
public:
    InputIterable(std::istream& in, int size):in(in), size(size) {}
    virtual unique_ptr<Iterator<T>> iterator() const {
        return unique_ptr<Iterator<T>>(new InputIterator<T>(in, size));
    }
};

template <class T> InputIterable<T> inputIterable(std::istream& in, int size) {
    return InputIterable<T>(in, size);
}