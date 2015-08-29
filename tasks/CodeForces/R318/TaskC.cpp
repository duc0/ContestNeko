#include "global.hpp"

#define MAXN 100100

int n;
vector<vector<int>> adj;

int nLeaf[MAXN];
int totalLeaf;

vector<pair<int, int>> edge;

bool check() {
    if (edge.empty()) {
        return true;
    }

    map<int, int> deg;
    for (auto &e: edge) {
        deg[e.first]++;
    }
    int c = 0;
    for (auto &d: deg) {
        if (d.second == 1) {
            ++c;
        }
    }
    return c == 2;
}
void dfs(int u) {
    nLeaf[u] = 0;
    for (int v : adj[u]) {
        if (nLeaf[v] == -1) {
            dfs(v);
            nLeaf[u] += nLeaf[v];

            int thisSub = nLeaf[v];
            int other = totalLeaf - thisSub;

            if (adj[v].size() == 2) {
                thisSub++;
            }
            if (adj[u].size() == 2) {
                other++;
            }

            if (thisSub > 2 && other > 2) {
                edge.emplace_back(u, v);
                edge.emplace_back(v, u);
            }
        }
    }
    if (nLeaf[u] == 0) {
        nLeaf[u] = 1;
    }
}

class TaskC {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        adj.clear();
        adj.resize(n + 1);
        repeat(n - 1) {
            int u, v;
            in >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        totalLeaf = 0;
        for_inc_range(u, 1, n) {
            if (adj[u].size() == 1) {
                totalLeaf++;
            }
        }
        memset(nLeaf, -1, sizeof(nLeaf));
        edge.clear();
        for_inc_range(u, 1, n) {
            if (adj[u].size() != 1) {
                dfs(u);
                break;
            }
        }
        if (check()) {
            out << "Yes" << endl;
        } else {
            out << "No" << endl;
        }
    }
};
