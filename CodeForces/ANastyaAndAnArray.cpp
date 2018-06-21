#include "global.hpp"
#include "Scanner.hpp"

class ANastyaAndAnArray {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);
      int n;
      in >> n;
      unordered_set<int> s;
      for (int i = 0; i < n; i++) {
        int val;
        in >> val;
        if (val != 0) {
          s.insert(val);
        }
      }
      out << (int) s.size();
    }
};
