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

class C {
public:
    void solve(std::istream& cin, std::ostream& cout) {
        int n, q, t, l, r, x;
        cin >> n >> q;
        auto merge = [](const ColorsQuery &lNode, const ColorsQuery &rNode) {
            return ColorsQuery(lNode.sum + rNode.sum, 0);
        };

        auto leaf = [](const ColorsQuery &cur, const int &oldV, const int &newV,
                       int lIndex, int rIndex) {
            return ColorsQuery(cur.sum + 1LL * abs(newV - oldV) * (rIndex - lIndex + 1),
                               cur.delta + 1LL * abs(newV - oldV));
        };

        auto split = [](ColorsQuery &cur, ColorsQuery &lNode, ColorsQuery &rNode,
                        int v, int leftIndex, int midIndex, int rightIndex) {
            lNode.sum += cur.delta * (midIndex - leftIndex + 1);
            lNode.delta += cur.delta;
            rNode.sum += cur.delta * (rightIndex - midIndex);
            rNode.delta += cur.delta;
            cur.delta = 0;
        };

        SegmentTree<int64, ColorsQuery> tree(1, n, 0, merge, leaf, split);
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
