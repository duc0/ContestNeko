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
    vector<int> timeStamp;
    vector<int> low;
    int currentTime;

    void dfs(int currentNode) {
        //LOG(1, "Visit: " << currentNode + 1);
        currentTime++;
        timeStamp[currentNode] = currentTime;
        low[currentNode] = currentTime;

        for (auto &edge: graph.adj[currentNode]) {
            if (graph.deletedEdges[edge.id]) {
                continue;
            }
            //LOG(1, "Visit Edge: " << edge.begin + 1 << " " << edge.end + 1);
            if (!visited[edge.end]) {
                visited[edge.end] = true;
                prev[edge.end] = edge;
                dfs(edge.end);
                low[currentNode] = min(low[currentNode], low[edge.end]);
            } else if (prev[currentNode].id != edge.id){
                low[currentNode] = min(low[currentNode], timeStamp[edge.end]);
            }
        }
    }

public:
    bool connected;
    BridgeFinder(const WeightedUndirectedGraph &graph, int source, int dest) : graph(graph), source(source), dest(dest) {
    }

    // Return empty list if not found a bridge
    vector<MyEdge> findBridge() {
        visited.resize(graph.nNodes);
        prev.resize(graph.nNodes);
        timeStamp.resize(graph.nNodes);
        low.resize(graph.nNodes);
        for (int i = 0; i < graph.nNodes; i++) {
            visited[i] = false;
            timeStamp[i] = 0;
            low[i] = 0;
        }
        currentTime = 0;
        visited[source] = true;
        // A special value
        prev[source].id = -2;

        dfs(source);

        vector<MyEdge> edgesInPath;

        connected = visited[dest];
        if (!connected) {
            return edgesInPath;
        }

        int currentNode = dest;
        while (currentNode != source) {
            edgesInPath.push_back(prev[currentNode]);
            currentNode = prev[currentNode].begin;
        }

        reverse(edgesInPath.begin(), edgesInPath.end());

        vector<MyEdge> bridges;

        for (auto &edge : edgesInPath) {
            //LOG(1, "Path Edge: " << edge.begin + 1 << " " << edge.end + 1);
            //LOG(1, "Low End: " << low[edge.end] << " " << timeStamp[edge.end]);
            if (low[edge.end] >= timeStamp[edge.end]) {
                bridges.push_back(edge);
            }
        }

        return bridges;
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

            out << 0;
            out.newline();
            out << 0;
        } else {

            Solution best;
            bool hasSolution = false;

            for (auto &edge : edgesInPath) {
                // Delete the edge and attempt to detect bridge
                graph.deleteEdge(edge.id);

                //LOG(1, "Delete Edge: " << edge.begin + 1 << " " << edge.end + 1);

                Solution current;
                current.addEdge(edge);

                BridgeFinder bridgeFinder(graph, source, dest);

                vector<MyEdge> bridges = bridgeFinder.findBridge();

                if (bridgeFinder.connected) {
                    //LOG(1, "Connected");

                    // TODO:
                    if (bridges.empty()) {
                        //LOG(1, "No Bridges");
                        // No bridges
                        graph.undeleteEdge(edge.id);
                        continue;
                    } else {
                        //LOG(1, "Has Bridges");
                        int minWeight = bridges[0].weight;
                        for (auto &edge: bridges) {
                            minWeight = min(minWeight, edge.weight);
                        }
                        for (auto &edge: bridges) {
                            if (edge.weight == minWeight) {
                                current.addEdge(edge);
                                break;
                            }
                        }
                    }
                } else {
                    //LOG(1, "Not Connected");
                }

                if (!hasSolution || current.isBetter(best)) {
                    hasSolution = true;
                    best = current;
                }

                graph.undeleteEdge(edge.id);
            }

            if (!hasSolution) {
                out << -1;
            } else {
                out << best.weight;
                out.newline();
                out << (int) best.edges.size();
                out.newline();
                vector<int> edgeIds;

                for (auto &edge: best.edges) {
                    edgeIds.push_back(edge.id);
                }

                sort(edgeIds.begin(), edgeIds.end());
                for (int id : edgeIds) {
                    out << id + 1 << " ";
                }
            }
        }

    }
};
