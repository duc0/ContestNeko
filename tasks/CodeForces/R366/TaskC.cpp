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
class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);

        int nEdge, nVertex;

        in >> nEdge >> nVertex;

        Graph graph(nVertex);

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
