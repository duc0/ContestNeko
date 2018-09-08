#include "Scanner.hpp"
#include "global.hpp"
#include "HLDSegmentTree.hpp"
#include "LowestCommonAncestor.hpp"
#include "NDArray.hpp"

#define CAP 10

#define NodeStruct cl::BoundedSortedSet<int, CAP>

class HSeg : public SimpleHLDSegmentTree<NodeStruct, NodeStruct, int> {
public:
    HSeg(int minIndex, int maxIndex, const NodeStruct &defaultValue, const HeavyLightDecomposition<int> &hld)
            : SimpleHLDSegmentTree(minIndex, maxIndex, defaultValue, hld) { }


    virtual NodeStruct initLeaf(const NodeStruct &value, int leftIndex, int rightIndex) override {
        return value;
    }

    virtual NodeStruct merge(const NodeStruct &leftSide, const NodeStruct &rightSide) override {
        return cl::merge(leftSide, rightSide);
    }
};


class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);
        int n, nPeople, q;
        in >> n >> nPeople >> q;

        WeightedTree<int> tree;
        tree.reset(n);
        vector<pair<int, int>> edge;

        REPEAT(n - 1) {
            int u, v;
            in >> u >> v;
            tree.addEdge(u, v, 1);
            edge.push_back(make_pair(u, v));
        }

        tree.setRoot(1);


        HeavyLightDecomposition<int> hld(tree);

        cl::Array1<NodeStruct> who(n);

        FOR_INC_RANGE(i, 1, nPeople) {
            int city;
            in >> city;
            who[city].add(i);
        }

        HSeg hseg(1, n, NodeStruct(), hld);
        

        FOR_INC_RANGE(i, 1, n) {
            hseg.updateNode(i, who[i]);
        }

        LowestCommonAncestor<int, int> lca(tree);

        auto nodeFunc = [&](int u) {return who[u];};

        REPEAT(q) {
            int u, v, a;
            in >> u >> v >> a;
            int ancestor = lca.getLCA(u, v).first;

            //LOG(1, u << " " << v << " LCA : " << ancestor);


            NodeStruct q1 = hseg.queryPath(ancestor, u, nodeFunc);
            NodeStruct q2 = hseg.queryPath(ancestor, v, nodeFunc);
            NodeStruct q3 = cl::merge(q1, q2);

            int sz = min(a, q3.size());
            out << sz;
            FOR_INC(i, sz) {
                out << " " << q3[i];
            }
            out.newline();
        }
    }
};
