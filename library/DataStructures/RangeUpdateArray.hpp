#include "global.hpp"
#include "BinaryIndexedTree.hpp"

/**
 * A data structure that allows adding all elements in a range by the same quantity, and retrieve an element
 * in logarithmic time.
 */
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

    /**
     *  Add toAdd to every element in the range [from, to]. Complexity: O(logn)
     *  @param from The from index
     *  @param to The to index (inclusive)
     *  @param toAdd The quantity to add
     */
    void add(int from, int to, T toAdd) {
        assert(minIndex <= from && from <= to && to <= maxIndex);
        if (to < maxIndex) {
            tree.add(to + 1, -toAdd);
        }
        tree.add(from, toAdd);
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