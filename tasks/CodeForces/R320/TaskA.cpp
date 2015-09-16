#include "global.hpp"

class TaskA {
public:
    void solve(std::istream& in, std::ostream& out) {
        int64 a, b;
        in >> a >> b;

        bool has1 = false;
        double x1;
        if (a > b) {
            int64 d = (a - b) / (2 * b);
            if (d > 0) {
                has1 = true;
                x1 = (double) (a - b) / (2 * d);
            }
        }

        bool has2 = false;
        double x2;
        {
            int64 d = (a + b) / (2 * b);
            if (d > 0) {
                has2 = true;
                x2 = (double) ( a + b) / ( 2 * d);
            }
        }

        double x = 1e18;
        if (has1) {
            x = min(x, x1);
        }
        if (has2) {
            x = min(x, x2);
        }
        if (x == 1e18) {
            out << -1;
        } else {
            out << setiosflags(ios::fixed) << std::setprecision(12) << x << endl;
        }
    }
};
