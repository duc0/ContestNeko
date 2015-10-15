#include "global.hpp"
#include "WeightedTree.hpp"
#include "SubtreeSize.hpp"

template<class T> class HeavyLightDecomposition {
    const WeightedTree<T> &tree;
    int timeStamp;
    vector<int> start;
    vector<int> finish;
    vector<int> head;
    vector<int> node;
    vector<bool> visit;
    int n;

    void dfs(int u, const SubtreeSize<T> &subtreeSize) {
        stack<int> s;
        s.push(u);
        while (!s.empty()) {
            u = s.top();

            if (!visit[u]) {
                timeStamp++;
                node[timeStamp] = u;
                start[u] = timeStamp;

                int heavyCutoff = subtreeSize[u] / 2;
                int nextNode = -1;

                for (auto &v: tree.getAdjacent(u)) {
                    if (v.first != tree.getParent(u)) {
                        if (subtreeSize[v.first] > heavyCutoff) {
                            nextNode = v.first;
                            break;
                        }
                    }
                }

                for (auto &v: tree.getAdjacent(u)) {
                    if (v.first != tree.getParent(u) && v.first != nextNode) {
                        head[v.first] = v.first;
                        s.push(v.first);
                    }
                }

                if (nextNode != -1) {
                    head[nextNode] = head[u];
                    // Tricky: in non-recursive DFS, if you want to visit nextNode first,
                    // you have to push it last into the stack
                    s.push(nextNode);
                }
                visit[u] = true;
            } else {
                s.pop();
                finish[u] = timeStamp;
            }
        }
    }

public:
    HeavyLightDecomposition(const WeightedTree<T> &tree): tree(tree) {
        n = (int) tree.getSize();
        timeStamp = 0;
        SubtreeSize<int> subtreeSize(tree);
        start.resize(n + 1);
        head.resize(n + 1);
        node.resize(n + 1);
        finish.resize(n + 1);
        visit.resize(n + 1);
        head[tree.getRoot()] = tree.getRoot();
        dfs(tree.getRoot(), subtreeSize);
    }

    const WeightedTree<T>& getTree() const {
        return tree;
    }

    // is the path parent[u] to u light?
    bool isLight(int u) const {
        assert(u != tree.getRoot());
        assert(1 <= u && u <= n);
        return head[u] == u;
    }

    bool isHeavy(int u) const {
        return !isLight(u);
    }

    int getHead(int u) const {
        assert(1 <= u && u <= n);
        return head[u];
    }

    int getStartTime(int u) const {
        assert(1 <= u && u <= n);
        return start[u];
    }

    int getFinishTime(int u) const {
        assert(1 <= u && u <= n);
        return finish[u];
    }

    int getNodeAtTime(int timeStamp) const {
        return node[timeStamp];
    }

    int getHeadTime(int u) const {
        assert(1 <= u && u <= n);
        return start[head[u]];
    }

    bool inSameHeavyPath(int u, int v) const {
        assert(1 <= u && u <= n);
        return head[u] == head[v];
    }
};