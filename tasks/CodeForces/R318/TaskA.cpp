#include "global.hpp"
#include "Iterator.hpp"
#include "InputIterables.hpp"

int mapNumber(int x) {
    while (x % 2 == 0) x /= 2;
    while (x % 3 == 0) x /= 3;
    return x;
}

class TaskA {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        if (unique(mapIterable(inputIterable<int>(in, n), (function<int(int)>) mapNumber))) {
            out << "Yes";
        } else {
            out << "No";
        }
    }
};
