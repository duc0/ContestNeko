#include "global.hpp"
#include "SegmentTree.hpp"

struct ColorsQuery {
    // Sum of colourfulness
    int64 sum;

    // Lazy propagation of colourfulness
    int64 delta;

    ColorsQuery() {
        sum = 0;
        delta = 0;
    }

    ColorsQuery(int64 sum, int64 delta) {
        this->sum = sum;
        this->delta = delta;
    }
};


class ColorTree : public SegmentTree<int64, ColorsQuery> {
public:
    virtual ColorsQuery merge(const ColorsQuery& lNode, const ColorsQuery& rNode) override {
        return ColorsQuery(lNode.sum + rNode.sum, 0);
    }


    virtual ColorsQuery updateLeaf(const ColorsQuery &current, const long long int &oldValue,
                                   const long long int &currentValue, int leftIndex, int rightIndex) override {
        return ColorsQuery(current.sum + 1LL * abs(currentValue - oldValue) * (rightIndex - leftIndex + 1),
                           current.delta + 1LL * abs(currentValue - oldValue));
    }


    virtual ColorsQuery split(ColorsQuery &current, ColorsQuery &leftChild, ColorsQuery &rightChild,
                              const long long int &currentValue, int leftIndex, int midIndex, int rightIndex) override {
        leftChild.sum += current.delta * (midIndex - leftIndex + 1);
        leftChild.delta += current.delta;
        rightChild.sum += current.delta * (rightIndex - midIndex);
        rightChild.delta += current.delta;
        current.delta = 0;
    }

    explicit ColorTree(int minIndex, int maxIndex, int64 defaultValue) : SegmentTree<int64, ColorsQuery>(minIndex, maxIndex, defaultValue) {

    }
};

class C {
public:
    void solve(std::istream& cin, std::ostream& cout) {
        int n, q, t, l, r, x;
        cin >> n >> q;

        ColorTree tree(1, n, 0);
        for_inc_range(i, 1, n) { tree.update(i, i, i); }
        repeat(q) {
            cin >> t;
            if (t == 1) {
                cin >> l >> r >> x;
                tree.update(l, r, x);
            } else {
                cin >> l >> r;
                int64 exclude = (int64)(r - l + 1) * (r + l) / 2;
                cout << tree.query(l, r).sum - exclude << endl;
            }
        }
    }
};
