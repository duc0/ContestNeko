#include "global.hpp"
#include "UndirectedGraph.hpp"

struct Equation {
    int l, r;
};

int n, k;

Equation getEquation(int r, int c) {
    if (r + c > n + 1) {
        return getEquation(n - c + 1, n - r + 1);
    }
    if (r > c) {
        return getEquation(c, r);
    }
    int diag = c - r + 1;
    Equation e;
    e.l = diag;
    e.r = diag + 2 * (r - 1);
    if (e.l <= 2) {
        e.l = 0;
    } else e.l -= 2;

    return e;
}

UndirectedGraph sameGraph, compGraph;

vector<vector<int>> diffEdge;

class TaskD {
public:
    void solve(std::istream& in, std::ostream& out) {
        in >> n >> k;
        int a, b, c; string s;

        diffEdge.resize(n + 2);

        sameGraph.init(n + 1);

        repeat(k) {
            in >> a >> b >> s;
            c = s[0] == 'x';
            Equation e = getEquation(a, b);
            int u = e.l == 0 ? n + 1 : e.l;
            int v = e.r == 0 ? n + 1 : e.r;
            if (c == 0) {
                diffEdge[u].push_back(v);
                diffEdge[v].push_back(u);
            } else {
                sameGraph.addEdge(u, v);
            }
        }

        sameGraph.buildCC();

        compGraph.init(sameGraph.getNumberOfComponents());
        for_inc_range(u, 1, n + 1) {
            for (auto &v: diffEdge[u]) {
                int cu = sameGraph.getComponent(u);
                int cv = sameGraph.getComponent(v);
                if (cu == cv) {
                    out << 0;
                    return;
                } else {
                    compGraph.addEdge(cu, cv);
                }
            }
        }

        compGraph.buildCC();
        if (compGraph.hasOddCycle()) {
            out << 0;
            return;
        }

        int ret = 1;
        for_inc_range(i, 1, compGraph.getNumberOfComponents() - 1) {
            ret = (ret * 2) % MOD;
        }
        out << ret << endl;
    }
};
