#include "global.hpp"
#include "Scanner.hpp"

struct Edge {
    int edgeId;
    int begin, end;
    bool signBegin, signEnd;

    Edge(int edgeId, int begin, int end, bool signBegin, bool signEnd) :
            edgeId(edgeId), begin(begin), end(end), signBegin(signBegin), signEnd(signEnd) {

    }
};

struct Graph {
    int nVertex;
    int nEdge;

    vector< vector<Edge> > adjList;
    vector <int> degree;

    Graph(int nVertex) : nVertex(nVertex) {
        adjList.clear();
        adjList.resize(nVertex);
        degree.resize(nVertex);
        nEdge = 0;
        for_inc(i, nVertex) {
            degree[i] = 0;
        }
    }

    void addEdge(int begin, int end, bool signBegin, bool signEnd) {
        begin--;
        end--;
        int edgeId = nEdge;

        Edge edge(edgeId, begin, end, signBegin, signEnd);
        adjList[begin].push_back(edge);

        Edge invEdge(edgeId, end, begin, signEnd, signBegin);
        adjList[end].push_back(invEdge);

        degree[begin]++;
        degree[end]++;

        nEdge++;
    }

    vector<bool> edgeVisited;

    vector<bool> nodeVisited;

    vector<Edge> chain;

    void initDfs() {
        edgeVisited.resize(nEdge);
        nodeVisited.resize(nVertex);

        for_inc(i, nVertex) {
            nodeVisited[i] = false;
        }

        for_inc(i, nEdge) {
            edgeVisited[i] = false;
        }
    }

    void initNewChain() {
        chain.clear();
    }

    void dfs(int start) {
        nodeVisited[start] = true;
        for (auto &e : adjList[start]) {
            if (!edgeVisited[e.edgeId]) {
                chain.push_back(e);
                edgeVisited[e.edgeId] = true;
                dfs(e.end);
            }
        }
    }

    void logChain() {
        LOG(1, "New chain");
        for (auto &e : chain) {
            LOG(1, e.begin + 1 << " - " << e.end  + 1<< " signBegin: " << e.signBegin << ", signEnd: " << e.signEnd);
        }
    }
};


int getVal(int val, int sign) {
    return sign ? val : (1-val);
}

int f[2][2][2][100100];
int knownVal[100100];

struct ChainSolver {

    const vector<Edge> &chain;

    int n;
    vector <int> f;

    ChainSolver(const vector<Edge> &chain) : chain(chain) {
        n = chain.size();
    }

    int solve(int target, int offset, int beginVal, int endVal) {
        int firstPos = offset;
        int lastPos = chain.size() - 1 - offset;
        Edge firstEdge = chain[firstPos];
        Edge lastEdge = chain[lastPos];


        int signedBeginVal = getVal(beginVal, firstEdge.signBegin);
        int signedEndVal = getVal(endVal, lastEdge.signEnd);
        knownVal[firstEdge.begin] = beginVal;
        if (knownVal[lastEdge.end] != -1 && knownVal[lastEdge.end] != endVal) {
            return 0;
        }
        knownVal[lastEdge.end] = endVal;

        int result = 0;

        for_inc(nextBeginVal, 2) {
            if (knownVal[firstEdge.end] != -1 && nextBeginVal != knownVal[firstEdge.end]) {
                continue;
            }
            int signedNextBeginVal = getVal(nextBeginVal, firstEdge.signEnd);
            int signFirstEdgeVal = signedBeginVal ^ signedNextBeginVal;

            for_inc(nextEndVal, 2) {
                if (knownVal[lastEdge.begin] != -1 && nextEndVal != knownVal[lastEdge.begin]) {
                    continue;
                }
                int signedNextEndVal = getVal(nextEndVal, lastEdge.signBegin);
                int signLastEdgeVal = signedEndVal ^ signedNextEndVal;

                result += solve();
            }
        }

    }

    int solve(int target) {
        fill0(f);
        return solve(target, 0, 0, 0) + solve(target, 0, 0, 1) + solve(target, 0, 1, 0) + solve(target, 0, 1, 1);
    }



};
class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);

        int nEdge, nVertex;

        in >> nEdge >> nVertex;

        Graph graph(nVertex);

        for_inc(i, nVertex) {
            knownVal[i] = -1;
        }

        repeat(nEdge) {
            int k;
            in >> k;

            assert(k <= 2);

            int begin, end, signBegin, signEnd;

            in >> begin;
            signBegin = (begin > 0);
            begin = abs(begin);

            if (k == 2) {
                in >> end;
                signEnd = (end > 0);
                end = abs(end);
            } else {
                end = begin;
                signEnd = signBegin;
            }

            graph.addEdge(begin, end, signBegin, signEnd);
        }

        graph.initDfs();

        // Path
        for (int i = 0; i < nVertex; i++) {
            if (graph.degree[i] == 1 && !graph.nodeVisited[i]) {
                graph.initNewChain();
                graph.dfs(i);
                graph.logChain();
                ChainSolver cs(graph.chain);
            }
        }

        // Cycle
        for (int i = 0; i < nVertex; i++) {
            if (graph.degree[i] > 0 && !graph.nodeVisited[i]) {
                graph.initNewChain();
                graph.dfs(i);
                graph.logChain();
            }
        }

        for (int i = 0; i < nVertex; i++) {
            if (graph.degree[i] == 0) {
                // TODO:
            }
        }

        Writer out(outStream);
    }
};
