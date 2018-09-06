#include "global.hpp"
#include "Scanner.hpp"
#include "UndirectedGraph.hpp"

#define MAX_COLOR 4

struct Edge {
  int u, v, count;
  int choose;

  Edge(int u, int v, int count) : u(u), v(v), count(count) {};
};

struct Result {
  int bestWeight = 0;
  int currentWeight = 0;
};

class TaskE {
    vector<int> maxWeight[MAX_COLOR + 1][MAX_COLOR + 1];

    bool hasCircuit(const vector<Edge> &edges) {
      UndirectedGraph g;
      g.init(MAX_COLOR);
      for (auto& edge : edges) {
        REPEAT(edge.choose) {
          g.addEdge(edge.u, edge.v);
        }
      }
      g.buildCC();

      unordered_set<int> allComps;
      for (auto& edge : edges) {
        if (edge.choose > 0) {
          allComps.insert(g.getComponent(edge.u));
          allComps.insert(g.getComponent(edge.v));
        }
      }

      if (allComps.size() > 1) {
        //cout << "Num comp " << numComp << " bad!";
        return false;
      }
      int countOdd = 0;
      FOR_INC_RANGE(u, 1, MAX_COLOR) {
        if (g.getDeg(u) % 2 == 1) {
          countOdd++;
        }
      }
      return countOdd == 0 || countOdd == 2;
    }

    void tryAll(vector<Edge> &edges, Result& result, int idx, int remainingWeight) {
      if (idx == -1) {

        if (result.currentWeight > result.bestWeight && hasCircuit(edges)) {
          result.bestWeight = result.currentWeight;
        }
        return;
      }
      if (result.currentWeight + remainingWeight <= result.bestWeight) {
        return;
      }

      auto& edge = edges[idx];
      for (int cnt = edge.count ; cnt >= 0; cnt--) {
        if (edge.u == edge.v && cnt > 0 && cnt < edge.count) {
          continue;
        }
        if (cnt > 0 && cnt + 2 < edge.count) {
          continue;
        }
        edge.choose = cnt;
        int wgt = maxWeight[edge.u][edge.v][cnt];;
        result.currentWeight += wgt;
        tryAll(edges, result, idx - 1, remainingWeight - wgt);
        result.currentWeight -= wgt;


      };
    }

public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int nBlocks = in.nextInt();
        vector<int> weight[MAX_COLOR + 1][MAX_COLOR + 1];
        int totalWeight = 0;
        REPEAT(nBlocks) {
          int u = in.nextInt();
          int val = in.nextInt();
          int v = in.nextInt();
          if (u > v) {
            swap(u, v);
          }
          weight[u][v].emplace_back(val);
          totalWeight += val;
        }

        int numEdges[MAX_COLOR + 1][MAX_COLOR + 1];


        vector<Edge> edges;

        FOR_INC_RANGE(u, 1, MAX_COLOR) {
          FOR_INC_RANGE(v, u, MAX_COLOR) {
            sort(weight[u][v].begin(), weight[u][v].end());
            numEdges[u][v] = weight[u][v].size();

            maxWeight[u][v].clear();
            maxWeight[u][v].push_back(0);
            int nEdges = numEdges[u][v];
            int sum = 0;
            FOR_INC(i, nEdges) {
              sum += weight[u][v][nEdges - 1 - i];
              maxWeight[u][v].push_back(sum);
            }

            edges.push_back(Edge(u, v, nEdges));
          }
        }

        Result result;
        tryAll(edges, result, edges.size() - 1, totalWeight);
        out << result.bestWeight;


    }
};
