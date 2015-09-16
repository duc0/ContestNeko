#include "global.hpp"
#include "SegmentTree.hpp"

// A segment tree with two queries:
// add(i, j, v): add all elements in range [i, j] by V
// queryMax(i, j)
// all 0 initially.
template <class T> struct MaxTreeQ;
template <class T> class MaxTree : public SegmentTree<T, MaxTreeQ<T>> {
public:
    MaxTree(int minIndex, int maxIndex)
            : SegmentTree<T, MaxTreeQ<T>>(
            minIndex, maxIndex, 0,
            [](const MaxTreeQ<T> &l, const MaxTreeQ<T> &r) {
                return MaxTreeQ<T>(max(l.queryMax, r.queryMax), 0);
            },
            [](const MaxTreeQ<T> &cur, T oldV, T newV, int l, int r) {
                return MaxTreeQ<T>(cur.queryMax + newV, cur.lazy + newV);
            },
            [](MaxTreeQ<T> &cur, MaxTreeQ<T> & lChild, MaxTreeQ<T> & rChild,
               T curV, int l, int m, int r) {
                lChild.lazy += cur.lazy;
                rChild.lazy += cur.lazy;
                lChild.queryMax += cur.lazy;
                rChild.queryMax += cur.lazy;
                cur.lazy = 0;
            }) {}

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