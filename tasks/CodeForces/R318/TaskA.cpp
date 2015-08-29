#include "global.hpp"

class TaskA {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        int x = -1;
        repeat(n) {
            int a;
            in >> a;
            while (a % 2 == 0) a /= 2;
            while (a % 3 == 0) a /= 3;
            if (x == -1) x = a;
            else if (x != a) {
                out << "No";
                return;
            }
        }
        out << "Yes";
    }
};
