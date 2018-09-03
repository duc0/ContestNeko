#include "global.hpp"

#ifndef H_WEIGHTED_TREE
#define H_WEIGHTED_TREE

// Weighted undirected tree
// Doesn't yet do any input validation.
template <class WeightType, WeightType DefaultWeight> class WeightedTree {
public:
    WeightedTree() {}

    WeightedTree(int size) { reset(size); }

    // Return all the adjacent nodes of a node, including the node's parent (if tree is already rooted).
    const vector<pair<int, WeightType>> &getAdjacentNodes(int node) const {
        return adj[node];
    }

    // Reset the tree with given number of nodes.
    void reset(int size) {
        this->numNodes = size;
        adj.resize(numNodes + 1);
        FOR_INC_RANGE(i, 1, numNodes) {
            adj[i].clear();
        }
        parent.resize(numNodes + 1);
        depth.resize(numNodes + 1);
        FOR_INC_RANGE(i, 1, numNodes) {
            parent[i] = make_pair(-1, -1);
            depth[i] = 0;
        }
        root = -1;
    }

    bool isRootSet() const {
        return root != -1;
    }

    int getParent(int u) const {
        assertHasRoot();
        return parent[u].first;
    }

    WeightType getWeightParentEdge(int u) const {
        assertHasRoot();
        return parent[u].second;
    }

    void setWeightParentEdge(int u, WeightType w) {
        assertHasRoot();
        parent[u].second = w;
    }

    int getDepth(int u) const {
        assertHasRoot();
        return depth[u];
    }

    size_t getSize() const {
        return numNodes;
    }

    int getRoot() const {
        assertHasRoot();
        return root;
    }

    // Root the tree, and then do a dfs from the root to update parent, depth.
    void setRoot(int u) {
        FOR_INC_RANGE(v, 1, numNodes) {
            parent[v].first = -1;
        }
        root = u;
        parent[root].first = -2;
        dfs(root);
    }

    // Create an edge between two nodes.
    void addEdge(int u, int v, WeightType weight = DefaultWeight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

private:
    // adjacency list
    vector<vector<pair<int, WeightType>>> adj;

    // parent[u] = parent of u and weight parent[u] -> u
    vector<pair<int, WeightType>> parent;

    vector<int> depth;

    int numNodes;
    int root;

    void assertHasRoot() const {
        ASSERT(isRootSet(), "Root must be set");
    }

    // Run a DFS on the tree and update parent, depth.
    void dfs(int u) {
        stack<int> node;
        node.push(u);
        while (!node.empty()) {
            u = node.top();
            node.pop();
            for (auto &e : adj[u]) {
                int v = e.first;
                int weight = e.second;
                if (parent[v].first == -1) {
                    parent[v] = make_pair(u, weight);
                    depth[v] = depth[u] + 1;
                    node.push(v);
                }
            }
        }
    }
};

using UnweightedTree = WeightedTree<int, 1>;

#endif