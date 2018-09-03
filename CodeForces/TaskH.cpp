#include "global.hpp"
#include "Scanner.hpp"

class TaskH {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        in >> n;

        int result = lg2(n) + 1;
        out << result;
    }
};
