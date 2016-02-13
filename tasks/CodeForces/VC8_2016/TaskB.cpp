#include "global.hpp"
#include "Scanner.hpp"

struct GVertex {
  int r = 0, g = 0, b = 0;
  int length() const {
      return r + g + b;
  }

    bool operator==(const GVertex &y) const {
        return r == y.r && g == y.g && b == y.b;
    }

  GVertex(int r, int g, int b) : r(r), g(g), b(b) {}

    GVertex() {}


  vector<GVertex> adjacent() const {
      vector<GVertex> result;
      if (r > 0) {
          result.emplace_back(r - 1, g + 1, b + 1);
          result.emplace_back(r + 1, g, b);
      }
      if (g > 0) {
          result.emplace_back(r + 1, g - 1, b + 1);
          result.emplace_back(r, g + 1, b);
      }
      if (b > 0) {
          result.emplace_back(r + 1, g + 1, b - 1);
          result.emplace_back(r, g, b + 1);
      }
      return result;
  }

    friend std::ostream &operator<<(std::ostream &stream, const GVertex &val) {
        for_inc(i, val.r) stream << "R";
        for_inc(i, val.g) stream << "G";
        for_inc(i, val.b) stream << "B";
        stream << " Length: " << val.length();
        return stream;
    }
};

#define MAXC 205

struct VertexSet {
  bool s[MAXC][MAXC][MAXC];

  void reset() {
      memset(s, false, sizeof(s));
  }

  bool inSet(const GVertex &v) const {
      return s[v.r][v.g][v.b];
  }

  void put(const GVertex &v) {
      s[v.r][v.g][v.b] = true;
  }
};

VertexSet visited;

class TaskB {
public:
    GVertex dest;
    bool bfs(const GVertex &start) {
        LOG(1, "Start with " << start);
        if (start == dest) {
            return true;
        }
        visited.reset();
        deque<GVertex> q;

        q.push_back(start);
        visited.put(start);

        while (!q.empty()) {
            GVertex v = q.front();
            q.pop_front();

            for (GVertex adj : v.adjacent()) {
                LOG(1, "Visit " << adj);
                LOG(1, "Is in set " << visited.inSet(adj));
                if ((adj.length() <= dest.length()) && !visited.inSet(adj)) {
                    visited.put(adj);
                    q.push_back(adj);
                    LOG(1, "Will Visit " << adj);
                    if (adj == dest) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        string s;
        inStream >> n;
        inStream >> s;

        int r = 0, g = 0, b = 0;
        for (char c : s) {
            if (c == 'R') r++;
            else if (c == 'G') g++;
            else if (c == 'B') b++;
        }

        dest = GVertex(r, g, b);
        LOG(1, "Dest " << dest);

        if (bfs(GVertex{0, 0, 1})) {
            outStream << "B";
        }
        if (bfs(GVertex{0, 1, 0})) {
            outStream << "G";
        }
        if (bfs(GVertex{1, 0, 0})) {
            outStream << "R";
        }
    }
};
