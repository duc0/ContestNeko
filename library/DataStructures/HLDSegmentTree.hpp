#include "HeavyLightDecomposition.hpp"
#include "SegmentTree.hpp"

template <class T, class Q, class W> class HLDSegmentTree: public SegmentTree<T,Q> {
private:
    const HeavyLightDecomposition<W> &hld;
public:
    explicit HLDSegmentTree(int minIndex, int maxIndex, T defaultValue,
                   const HeavyLightDecomposition<W> &hld)
            : SegmentTree<T,Q>(minIndex, maxIndex, defaultValue), hld(hld) {}

    void updateNode(int u, T v) {
        int s = hld.getStartTime(u);
        this->update(s, s, v);
    }

    void updateSubtree(int u, T v) {
        this->update(hld.getStartTime(u), hld.getFinishTime(u), v);
    }

    // Query the range from the start of the heavy path of u to u
    Q queryHeavyPath(int u) {
        return this->query(hld.getHeadTime(u), hld.getStartTime(u));
    }

    // If v and u are in the same heavy path and v is an ancestor of u,
    // query that range.
    Q queryHeavyPath(int ancestor, int u) {
        assert(hld.inSameHeavyPath(u, ancestor));
        assert(hld.getStartTime(ancestor) <= hld.getStartTime(u));
        return this->query(hld.getStartTime(ancestor), hld.getStartTime(u));
    }

    Q queryNode(int u) {
        return this->query(hld.getStartTime(u), hld.getStartTime(u));
    }

    // Query the path from ancestor to u. O(logn^2).
    // A queryNodeFunc can be used for fast querying value of a node
    // Pass a queryNodeFunc can make a different!
    Q queryPath(int ancestor, int u, const function<Q(int)> &queryNodeFunc) {
        assert(hld.getStartTime(ancestor) <= hld.getStartTime(u));
        Q res = queryNodeFunc(u);
        while (1) {
            res = this->merge(res, queryNodeFunc(u));
            if (u == ancestor) {
                break;
            }
            if (hld.isLight(u)) {
                u = hld.getTree().getParent(u);
            } else {
                if (hld.inSameHeavyPath(u, ancestor)) {
                    Q q = queryHeavyPath(ancestor, u);
                    res = this->merge(res, q);
                    break;
                } else {
                    Q q = queryHeavyPath(u);
                    res = this->merge(res, q);
                    u = hld.getHead(u);
                }
            }
        }
        return res;
    }

    Q queryPath(int ancestor, int u) {
        return queryPath(ancestor, u, [&](int u){return queryNode(u);});
    }
};

template <class T, class Q, class W> class SimpleHLDSegmentTree : public HLDSegmentTree<T, Q, W> {

public:
    virtual Q initLeaf(const T &value, int leftIndex, int rightIndex) = 0;

    explicit SimpleHLDSegmentTree(int minIndex, int maxIndex, T defaultValue, const HeavyLightDecomposition<W> &hld)
            : HLDSegmentTree<T, Q, W>(minIndex, maxIndex, defaultValue, hld) { }

private:
    Q updateLeaf(const Q &current, const T &oldValue, const T &currentValue, int leftIndex,
                         int rightIndex) override {
        return initLeaf(currentValue, leftIndex, rightIndex);
    }

    Q split(Q &current, Q &leftChild, Q &rightChild, const T &currentValue, int leftIndex, int midIndex,
                    int rightIndex) override {
        leftChild = initLeaf(currentValue, leftIndex, midIndex);
        rightChild = initLeaf(currentValue, midIndex + 1, rightIndex);
        return current;
    }
};
