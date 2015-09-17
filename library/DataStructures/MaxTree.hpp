#include "global.hpp"
#include "SegmentTree.hpp"

// A segment tree with two queries:
// add(i, j, v): add all elements in range [i, j] by V
// queryMax(i, j)
// all 0 initially.
template <class T> struct MaxTreeQ;
template <class T> class MaxTree : public SegmentTree<T, MaxTreeQ<T>> {
public:
    MaxTree(int minIndex, int maxIndex, T defaultValue) : SegmentTree(minIndex, maxIndex, defaultValue) { }

    virtual MaxTreeQ<T> merge(const MaxTreeQ<T> &leftSide, const MaxTreeQ<T> &rightSide) override {
        return MaxTreeQ<T>(max(leftSide.queryMax, rightSide.queryMax), 0);
    }

    virtual MaxTreeQ<T> updateLeaf(const MaxTreeQ<T> &current, const T &oldValue, const T &currentValue, int leftIndex,
                                   int rightIndex) override {
        return MaxTreeQ<T>(current.queryMax + currentValue, current.lazy + currentValue);
    }

    virtual MaxTreeQ<T> split(MaxTreeQ<T> &current, MaxTreeQ<T> &leftChild, MaxTreeQ<T> &rightChild,
                              const T &currentValue, int leftIndex, int midIndex, int rightIndex) override {
        leftChild.lazy += current.lazy;
        rightChild.lazy += current.lazy;
        leftChild.queryMax += current.lazy;
        rightChild.queryMax += current.lazy;
        current.lazy = 0;
    }

    T queryMax(int l, int r) {
        return SegmentTree<T, MaxTreeQ<T>>::query(l, r).queryMax;
    }

    T queryMax() { return SegmentTree<T, MaxTreeQ<T>>::query().queryMax; }

    void add(int l, int r, T v) { SegmentTree<T, MaxTreeQ<T>>::update(l, r, v); }
};

template <class T> struct MaxTreeQ {
    T queryMax = 0;
    T lazy = 0;
    MaxTreeQ(){};
    MaxTreeQ(T queryMax, T lazy) {
        this->queryMax = queryMax;
        this->lazy = lazy;
    }
};