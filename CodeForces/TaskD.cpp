#include "global.hpp"
#include "Scanner.hpp"
#include "WeightedTree.hpp"

class TaskD {
public:
    bool isBFS(Scanner& in, const WeightedTree<int>& tree) const {
        int n = tree.getSize();

        int lastOrder = -1;
        vector<int> order(n + 1);
        for (int i = 1; i <= n; i++) {
            order[i] = -1;
        }
        order[1] = 0;

        int currentOrder = 0;

        repeat(n) {
            int x;
            in >> x;
            if (order[x] == -1 || order[x] < lastOrder) {
                return false;
            }
            for (auto& nextNode : tree.getAdjacent(x)) {
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

        WeightedTree<int> tree;
        tree.reset(n);

        repeat(n - 1) {
            int u, v;
            in >> u >> v;
            tree.addEdge(u, v, 1);
        }

        tree.setRoot(1);

        if (isBFS(in, tree)) {
            out << "Yes";
        } else {
            out << "No";
        }
    }
};
