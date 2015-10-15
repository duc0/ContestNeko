#include "global.hpp"

#ifndef H_WEIGHTED_TREE
#define H_WEIGHTED_TREE

// Weighted undirected tree
template <class T> class WeightedTree {
    vector<vector<pair<int, T>>> adj;

    // p [u] = parent of u and weight p[u] -> u
    vector<pair<int, T>> p;

    vector<int> depth;

    int n;
    int root;

public:
    const vector<pair<int, T>> &getAdjacent(int u) const { return adj[u]; }

    void reset(int size) {
        this->n = size;
        adj.resize(n + 1);
        for_inc_range(i, 1, n) adj[i].clear();
        p.resize(n + 1);
        depth.resize(n + 1);
        for_inc_range(i, 1, n) {
            p[i] = make_pair(-1, -1);
            depth[i] = 0;
        }
    }

    WeightedTree() {}

    WeightedTree(int n) { reset(n); }

    void dfs(int u) {
        stack<int> node;
        node.push(u);
        while (!node.empty()) {
            u = node.top();
            node.pop();
            for (auto &e : adj[u]) {
                int v = e.first;
                int c = e.second;
                if (p[v].first == -1) {
                    p[v] = make_pair(u, c);
                    depth[v] = depth[u] + 1;
                    node.push(v);
                }
            }
        }
    }

    int getParent(int u) const { return p[u].first; }

    T getWeight(int u) const { return p[u].second; }

    void setWeight(int u, T w) { p[u].second = w; }

    int getDepth(int u) const { return depth[u]; }

    size_t getSize() const { return n; }

    int getRoot() const { return root; }

    void setRoot(int u) {
        for_inc_range(v, 1, n) {
            p[v].first = -1;
        }
        root = u;
        p[root].first = -2;
        dfs(root);
    }

    void addEdge(int u, int v, int c) {
        adj[u].push_back(make_pair(v, c));
        adj[v].push_back(make_pair(u, c));
    }
};

#endif