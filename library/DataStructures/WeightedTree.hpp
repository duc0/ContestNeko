#include "global.hpp"

#ifndef H_WEIGHTED_TREE
#define H_WEIGHTED_TREE

// Weighted undirected tree
// Doesn't yet do any input validation.
template <class WeightType, WeightType DefaultWeight> class WeightedTree {
public:
    WeightedTree() {
    }

    WeightedTree(int size) {
        reset(size);
    }

    // Return all the adjacent nodes of a node, including the node's parent (if tree is already rooted).
    const vector<pair<int, WeightType>> &getAdjacentNodes(int node) const {
        return adj[node];
    }

    // Reset the tree with given number of nodes.
    void reset(int size) {
        this->numNodes = size;
        adj.resize(numNodes + 1);
        for_inc_range(i, 1, numNodes) {
            adj[i].clear();
        }
        parent.resize(numNodes + 1);
        depth.resize(numNodes + 1);
        for_inc_range(i, 1, numNodes) {
            parent[i] = make_pair(-1, -1);
            depth[i] = 0;
        }
    }

    int getParent(int u) const {
        return parent[u].first;
    }

    WeightType getWeight(int u) const {
        return parent[u].second;
    }

    void setWeight(int u, WeightType w) {
        parent[u].second = w;
    }

    int getDepth(int u) const {
        return depth[u];
    }

    size_t getSize() const {
        return numNodes;
    }

    int getRoot() const {
        return root;
    }

    void setRoot(int u) {
        for_inc_range(v, 1, numNodes) {
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