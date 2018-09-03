#include "global.hpp"
#include "Scanner.hpp"

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        in >> n;

        int result = (int)log2(n) + 1;
        out << result;
    }
};
