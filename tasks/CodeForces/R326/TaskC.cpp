#include "global.hpp"
#include "HLDSegmentTree.hpp"
#include "LowestCommonAncestor.hpp"
#include "Collections.hpp"

#define CAP 10

struct NodeStruct {
    int sz = 0;
    int a[CAP];
    void add(int x) {
        for_inc(i, sz) {
            if (a[i] == x) {
                return;
            }
        }
        if (sz < CAP) {
            a[sz] = x;
            sz++;
        } else {
            a[sz - 1] = min(a[sz - 1], x);
        }
        sort(a, a + sz);
    }
};

NodeStruct mergeNode(const NodeStruct &s1, const NodeStruct &s2) {
    NodeStruct s;
    int i1 = 0, i2 = 0;
    while (i1 < s1.sz || i2 < s2.sz) {
        bool use1;
        if (i2 == s2.sz) {
            use1 = true;
        } else if (i1 == s1.sz) {
            use1 = false;
        } else {
            use1 = s1.a[i1] < s2.a[i2];
        }
        if (use1) {
            if (s.sz == 0 || s.a[s.sz - 1] < s1.a[i1]) {
                s.a[s.sz] = s1.a[i1];
                s.sz++;
            }
            i1++;
        } else {
            if (s.sz == 0 || s.a[s.sz - 1] < s2.a[i2]) {
                s.a[s.sz] = s2.a[i2];
                s.sz++;
            }
            i2++;
        }
        if (s.sz == CAP) {
            break;
        }
    }
    return s;
}

class HSeg : public SimpleHLDSegmentTree<NodeStruct, NodeStruct, int> {


public:

    HSeg(int minIndex, int maxIndex, const NodeStruct &defaultValue, const HeavyLightDecomposition<int> &hld)
            : SimpleHLDSegmentTree(minIndex, maxIndex, defaultValue, hld) { }


    virtual NodeStruct initLeaf(const NodeStruct &value, int leftIndex, int rightIndex) override {
        return value;
    }

    virtual NodeStruct merge(const NodeStruct &leftSide, const NodeStruct &rightSide) override {
        return mergeNode(leftSide, rightSide);
    }
};


class TaskC {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n, nPeople, q;
        in >> n >> nPeople >> q;

        WeightedTree<int> tree;
        tree.reset(n);
        vector<pair<int, int>> edge;

        repeat(n - 1) {
            int u, v;
            in >> u >> v;
            tree.addEdge(u, v, 1);
            edge.push_back(make_pair(u, v));
        }

        tree.setRoot(1);


        HeavyLightDecomposition<int> hld(tree);

        cl::Array1<NodeStruct> who(n);

        for_inc_range(i, 1, nPeople) {
            int city;
            in >> city;
            who[city].add(i);
        }

        HSeg hseg(1, n, NodeStruct(), hld);
        

        for_inc_range(i, 1, n) {
            hseg.updateNode(i, who[i]);
        }

        LowestCommonAncestor<int, int> lca(tree);

        repeat(q) {
            int u, v, a;
            in >> u >> v >> a;
            int ancestor = lca.getLCA(u, v).first;

            //LOG(1, u << " " << v << " LCA : " << ancestor);

            NodeStruct q1 = hseg.queryPath(ancestor, u);
            NodeStruct q2 = hseg.queryPath(ancestor, v);

            NodeStruct q3 = mergeNode(q1, q2);

            int sz = min(a, q3.sz);
            out << sz;
            for_inc(i, sz) {
                out << " " << q3.a[i];
            }
            out << endl;
        }
    }
};
