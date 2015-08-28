#include "global.hpp"
#include "BinaryIndexedTree.hpp"

template <class T> class RangeUpdateArray {
    BinaryIndexedTree<T> tree;
    int minIndex, maxIndex;

public:
    RangeUpdateArray() {}

    RangeUpdateArray(int n) {
        init(1, n);
    }

    RangeUpdateArray(int minIndex, int maxIndex) {
        init(minIndex, maxIndex);
    }

    void init(int minIndex, int maxIndex) {
        this->minIndex = minIndex;
        this->maxIndex = maxIndex;
        tree.init(minIndex, maxIndex);
    }

    // Do a[k] = a[k] + v for i <= k <= j
    // O(logn)
    void add(int i, int j, T v) {
        assert(minIndex <= i && i <= j && j <= maxIndex);
        if (j < maxIndex) {
            tree.add(j + 1, -v);
        }
        tree.add(i, v);
    }

    // Return a[i] in O(logn)
    T get(int i) {
        assert (minIndex <= i && i <= maxIndex);
        return tree.sum(i);
    }

    const T operator[](int i) {
        return get(i);
    }
};