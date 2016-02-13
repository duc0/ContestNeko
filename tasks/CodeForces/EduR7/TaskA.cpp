#include "global.hpp"
#include "Scanner.hpp"
#include "BinarySearch.hpp"

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int64 n;
        in >> n;

        int64 p;
        function<bool(int64)> pred = [&](int64 p){return (p * (p - 1) / 2 + 1) <= n;};
        binarySearchMax(0LL, (int64)1E8L, pred, p);

        out << n - (p * (p - 1) / 2);
    }
};
