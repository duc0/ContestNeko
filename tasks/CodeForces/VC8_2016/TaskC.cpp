#include "global.hpp"
#include "Scanner.hpp"
#include "BinarySearch.hpp"

class TaskC {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n2, n3;
        in >> n2 >> n3;

        int LIM = 20000000;

        function<bool(int)> pred = [&](int x) {
            int d2 = x / 2;
            int d3 = x / 3;
            int d6 = x / 6;

            d2 -= d6;
            d3 -= d6;

            int need2 = 0;
            if (d2 <= n2) {
                need2 = n2 - d2;
            }
            if (need2 <= d6 && d3 + (d6 - need2) >= n3) {
                return true;
            }
            int need3 = 0;
            if (d3 <= n3) {
                need3 = n3 - d3;
            }
            if (need3 <= d6 && d2 + (d6 - need3) >= n2) {
                return true;
            }
            return false;
        };

        int res;
        binarySearchMin(0, LIM, pred, res);
        out << res;
    }
};
