#include "global.hpp"
#include "WeightedTree.hpp"

// LCA O(logn)
template <class T, class Q> class LowestCommonAncestor {
    // anc[i][j] = ancestor 2^j dist away from i and a combined value generated
    // from the path from i to that ancestor,
    // default to the min weight
    vector<vector<pair<int, Q>>> anc;
    WeightedTree<T> &t;
    function<Q(Q, Q)> combine;

public:
    LowestCommonAncestor(WeightedTree<T> &tree)
            : LowestCommonAncestor(
            tree, [](WeightedTree<T> &t, int u) { return t.getWeight(u); },
            [](Q a, Q b) { return min(a, b); }) {}

    LowestCommonAncestor(WeightedTree<T> &tree,
                         const function<Q(WeightedTree<T> &, int)> &getInitial,
                         const function<Q(Q, Q)> &combine)
            : t(tree), combine(combine) {
        anc.resize(t.getSize() + 1);
        for_inc_range(i, 1, t.getSize()) {
            if (i != t.getRoot()) {
                anc[i].push_back(make_pair(t.getParent(i), getInitial(t, i)));
            }
        }
        for (int k = 1;; ++k) {
            bool ok = false;
            for_inc_range(i, 1, t.getSize()) {
                if (anc[i].size() >= k) {
                    int j = anc[i][k - 1].first;
                    if (anc[j].size() >= k) {
                        int x = anc[j][k - 1].first;
                        anc[i].push_back(make_pair(
                                x, combine(anc[i][k - 1].second, anc[j][k - 1].second)));
                        ok = true;
                    }
                }
            }
            if (!ok)
                break;
        }
    }

    // Get the kth ancestor of k, t = 0 .. depth[u]
    int getAncestor(int u, int k) {
        assert(0 <= k && k <= t.getDepth(u));
        if (k == 0) {
            return u;
        }
        int b = 0;
        while ((1 << b) <= k) ++b;
        --b;
        return getAncestor(anc[u][b].first, k - (1 << b));
    }

    Q queryAncestor(int u, int k) {
        assert(0 <= k && k <= t.getDepth(u));
        if (k == 0) {
            return u;
        }
        int b = 0;
        while ((1 << b) <= k) ++b;
        --b;
        return combine(anc[u][b].second, queryAncestor(anc[u][b].first, k - (1 << b)));
    }

    pair<int, T> getLCA(int u, int v) {
        if (t.getDepth(u) > t.getDepth(v)) {
            swap(u, v);
        }
        if (t.getDepth(v) > t.getDepth(u)) {
            for_dec(i, anc[v].size()) {
                int w = anc[v][i].first;
                if (t.getDepth(w) >= t.getDepth(u)) {
                    pair<int, T> p = getLCA(u, w);
                    p.second = min(anc[v][i].second, p.second);
                    return p;
                }
            }
        } else { // depth[v] == depth[u]
            if (u == v) {
                return make_pair(u, INT_INF);
            }
            for_dec(i, anc[u].size()) {
                int x = anc[u][i].first;
                int y = anc[v][i].first;
                if (x != y || i == 0) {
                    pair<int, T> p = getLCA(x, y);
                    p.second = combine(anc[u][i].second, p.second);
                    p.second = combine(anc[v][i].second, p.second);
                    return p;
                }
            }
        }
        return make_pair(-1, -1);
    }
};