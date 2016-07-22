#include "global.hpp"
#include "Scanner.hpp"

struct MyEdge {
    int id, begin, end, weight;
    MyEdge() {}
    MyEdge(int id, int begin, int end, int weight): id(id), begin(begin), end(end), weight(weight) {}
};

struct Solution {
    vector<MyEdge> edges;
    int weight = 0;

    void addEdge(const MyEdge &edge) {
        edges.push_back(edge);
        weight += edge.weight;
    }

    bool isBetter(const Solution &other) {
        return weight < other.weight;
    }
};

class WeightedUndirectedGraph {
public:
    vector<vector<MyEdge>> adj;
    int nNodes;
    int edgeCount;
    vector<bool> deletedEdges;

    WeightedUndirectedGraph(int nNodes): nNodes(nNodes) {
        adj.resize(nNodes);
        edgeCount = 0;
    }

    void addEdge(int end1, int end2, int weight) {
        adj[end1].push_back(MyEdge(edgeCount, end1, end2, weight));
        adj[end2].push_back(MyEdge(edgeCount, end2, end1, weight));
        edgeCount++;
    }

    void finishGraph() {
        deletedEdges.resize(edgeCount);
        for (int i = 0; i < edgeCount; i++) {
            deletedEdges[i] = false;
        }
    }

    void deleteEdge(int edgeIndex) {
        deletedEdges[edgeIndex] = true;
    }

    void undeleteEdge(int edgeIndex) {
        deletedEdges[edgeIndex] = false;
    }
};

class PathFinder {
    const WeightedUndirectedGraph &graph;
    int source, dest;

    vector<MyEdge> prev;
    vector<bool> visited;

    // Return true if found a path.
    bool dfs(int currentNode, int dest) {
        for (auto &edge: graph.adj[currentNode]) {
            if (!visited[edge.end]) {
                visited[edge.end] = true;
                prev[edge.end] = edge;
                if (edge.end == dest) {
                    return true;
                }
                if (dfs(edge.end, dest)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    PathFinder(const WeightedUndirectedGraph &graph, int source, int dest) : graph(graph), source(source), dest(dest) {
    }

    // Return empty list if not found a path
    vector<MyEdge> findPath() {
        visited.resize(graph.nNodes);
        prev.resize(graph.nNodes);
        for (int i = 0; i < graph.nNodes; i++) {
            visited[i] = false;
        }
        visited[source] = true;
        bool result = dfs(source, dest);

        vector<MyEdge> edgesInPath;

        if (!result) {
            return edgesInPath;
        }

        int currentNode = dest;
        while (currentNode != source) {
            edgesInPath.push_back(prev[currentNode]);
            currentNode = prev[currentNode].begin;
        }

        reverse(edgesInPath.begin(), edgesInPath.end());
        return edgesInPath;
    }
};


class BridgeFinder {
    const WeightedUndirectedGraph &graph;
    int source, dest;

    vector<MyEdge> prev;
    vector<bool> visited;

    // Return true if found a path.
    bool dfs(int currentNode, int dest) {
        for (auto &edge: graph.adj[currentNode]) {
            if (!visited[edge.end]) {
                visited[edge.end] = true;
                prev[edge.end] = edge;
                if (edge.end == dest) {
                    return true;
                }
                if (dfs(edge.end, dest)) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    bool connected;
    BridgeFinder(const WeightedUndirectedGraph &graph, int source, int dest) : graph(graph), source(source), dest(dest) {
    }

    // Return empty list if not found a bridge
    vector<MyEdge> findBridge() {
        visited.resize(graph.nNodes);
        prev.resize(graph.nNodes);
        for (int i = 0; i < graph.nNodes; i++) {
            visited[i] = false;
        }
        visited[source] = true;
        bool result = dfs(source, dest);
        connected = result;

        vector<MyEdge> edgesInPath;

        if (!result) {
            return edgesInPath;
        }

        int currentNode = dest;
        while (currentNode != source) {
            edgesInPath.push_back(prev[currentNode]);
            currentNode = prev[currentNode].begin;
        }

        reverse(edgesInPath.begin(), edgesInPath.end());
        return edgesInPath;
    }
};


class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int nNodes, nEdges;
        in >> nNodes >> nEdges;

        WeightedUndirectedGraph graph(nNodes);

        int source, dest;
        in >> source >> dest;
        source--;
        dest--;

        repeat(nEdges) {
            int x, y, w;
            in >> x >> y >> w;
            x--;
            y--;
            graph.addEdge(x, y, w);
        }

        graph.finishGraph();


        PathFinder pathFinder(graph, source, dest);

        vector<MyEdge> edgesInPath = pathFinder.findPath();

        if (edgesInPath.empty()) {
            // Not connected graph

            outStream << 0;
        } else {

            Solution best;
            bool hasSolution = false;

            for (auto &edge : edgesInPath) {
                LOG(1, "Edge: " << edge.begin + 1 << " " << edge.end + 1);

                // Delete the edge and attempt to detect bridge
                graph.deleteEdge(edge.id);

                Solution current;
                current.addEdge(edge);

                BridgeFinder bridgeFinder(graph, source, dest);

                vector<MyEdge> bridges = bridgeFinder.findBridge();

                if (bridgeFinder.connected) {
                    // TODO:

                }

                if (!hasSolution || current.isBetter(best)) {
                    hasSolution = true;
                    best = current;
                }

                graph.undeleteEdge(edge.id);
            }

            out << best.weight;
            out.newline();
            out << best.edges.size();
            out.newline();
            for (auto &edge: best.edges) {
                out << edge.id + 1;
                out.newline();
            }
        }

    }
};
