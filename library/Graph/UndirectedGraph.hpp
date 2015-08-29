#include "global.hpp"

class UndirectedGraph {
    friend class UndirectedGraphEdgeMarker;

    vector<vector<int>> adj;
    // indexMap[u][i] = the index of the same edge in adj[v]
    vector<vector<int>> indexMap;
    vector<int> comp;
    vector<int> color;
    vector<int> deg;
    bool ccBuilt = false;
    int nEdge = 0;
    int n, nComp;
    bool _hasOddCycle = false;

    void dfs(int u, int c) {
        comp[u] = nComp;
        color[u] = c;
        for (auto &v: adj[u]) {
            if (comp[v] == -1) {
                dfs(v, 1 - c);
            } else {
                if (color[v] != 1 - c) {
                    _hasOddCycle = true;
                }
            }
        }
    }

public:
    void init(int n) {
        this->n = n;
        adj.resize(n + 1);
        indexMap.resize(n + 1);
        deg.resize(n + 1);
        for_inc_range(u, 1, n) {
            adj[u].clear();
            indexMap[u].clear();
        }
        nEdge = 0;
        ccBuilt = false;
    }

    const vector<int> &getAdjacent(int u) const {
        return adj[u];
    }

    void addEdge(int u, int v) {
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        adj[u].push_back(v);
        adj[v].push_back(u);
        indexMap[u].push_back((int)adj[v].size() - 1);
        indexMap[v].push_back((int)adj[u].size() - 1);
        nEdge++;
        deg[u]++;
        deg[v]++;
        ccBuilt = false;
    }

    int getDeg(int u) const {
        return deg[u];
    }

    int getSize() const {
        return n;
    }

    int getNumEdges() const {
        return nEdge;
    }

    // Find connected components and detect odd cycle
    void buildCC() {
        ccBuilt = true;
        comp.resize(n + 1);
        fill(comp.begin(), comp.end(), -1);
        color.resize(n + 1);
        nComp = 0;
        _hasOddCycle = false;
        for_inc_range(u, 1, n) {
            if (comp[u] == -1) {
                nComp++;
                dfs(u, 0);
            }
        }
    }

    bool hasOddCycle() {
        assert(ccBuilt);
        return _hasOddCycle;
    }

    int getComponent(int u) {
        assert(ccBuilt);
        return comp[u];
    }

    int getNumberOfComponents() {
        assert(ccBuilt);
        return nComp;
    }
};

class UndirectedGraphEdgeMarker {
    UndirectedGraph g;
    vector<vector<bool>> flag;
    int n;

    void set(int u, int i, bool b) {
        assert(i >= 0 && i < g.getAdjacent(u).size());
        flag[u][i] = b;
        int v = g.getAdjacent(u)[i];
        flag[v][g.indexMap[u][i]] = b;
    }
public:
    UndirectedGraphEdgeMarker(const UndirectedGraph &g): g(g) {
        n = g.getSize();
        flag.resize(n + 1);
        for_inc_range(u, 1, n) {
            flag[u].resize(g.getAdjacent(u).size());
        }
    }

    void mark(int u, int i) {
        set(u, i, true);
    }

    void unmark(int u, int i) {
        set(u, i, false);
    }

    bool test(int u, int i) const {
        assert(i >= 0 && i < g.getAdjacent(u).size());
        return flag[u][i];
    }
};