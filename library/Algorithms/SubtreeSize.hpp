#include "global.hpp"
#include "WeightedTree.hpp"

template<class T> class SubtreeSize {
    const WeightedTree<T> &tree;
    vector<int> subtreeSize;
    vector<bool> visit;

    void dfs(int u) {
        stack<int> node;
        node.push(u);
        while (!node.empty()) {
            u = node.top();
            if (visit[u]) {
                node.pop();
                subtreeSize[u] = 1;
            }
            for (auto &v: tree.getAdjacent(u)) {
                if (v.first != tree.getParent(u)) {
                    if (!visit[u]) {
                        node.push(v.first);
                    } else {
                        subtreeSize[u] += subtreeSize[v.first];
                    }
                }
            }
            visit[u] = true;
        }
    }

public:
    SubtreeSize(const WeightedTree<T> &tree): tree(tree) {
        subtreeSize.resize(tree.getSize() + 1);
        visit.resize(tree.getSize() + 1);
        dfs(tree.getRoot());
    }

    const int operator[](int u) const {
        assert(1 <= u && u <= tree.getSize());
        return subtreeSize[u];
    }
};
