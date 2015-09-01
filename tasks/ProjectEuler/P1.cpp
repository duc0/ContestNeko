#include "global.hpp"
#include "Iterator.hpp"
#include "NumberTheory.hpp"

bool mult35(int x) {return x % 3 == 0 || x % 5 == 0;}

class P1 {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        out << aggregateSum(filter(range(1, n), predicate<int>(mult35)));
    }
};
