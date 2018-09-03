#include "global.hpp"
#include "Scanner.hpp"
#include "WeightedTree.hpp"
#include "Collections.hpp"

class TaskD {
public:
    bool isBFS(Scanner& in, const UnweightedTree& tree) const {
        int n = tree.getSize();

        int lastOrder = -1;
        cl::Array1<int> order(n);
        FOR_INC_RANGE(i, 1, n) {
            order[i] = -1;
        }
        order[1] = 0;

        int currentOrder = 0;

        REPEAT(n) {
            int x;
            in >> x;
            REQUIRE_OR_RET_FALSE(order[x] != -1 && order[x] >= lastOrder);
            for (auto& nextNode : tree.getAdjacentNodes(x)) {
                int v = nextNode.first;
                if (v != tree.getParent(x)) {
                    order[v] = currentOrder + 1;
                }
            }
            lastOrder = order[x];
            currentOrder++;
        }

        return true;
    }

    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        in >> n;

        UnweightedTree tree;
        tree.reset(n);

        REPEAT(n - 1) {
            int u, v;
            in >> u >> v;
            tree.addEdge(u, v);
        }

        tree.setRoot(1);

        if (isBFS(in, tree)) {
            out << "Yes";
        } else {
            out << "No";
        }
    }
};
