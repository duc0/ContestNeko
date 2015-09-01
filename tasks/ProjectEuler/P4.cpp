#include "global.hpp"
#include "Iterator.hpp"
#include "NumberTheory.hpp"

int mult(int a, int b) {return a * b;}

class P4 {
public:
    void solve(std::istream& in, std::ostream& out) {
        auto all3DigitsProduct = product(range(100, 999), range(100, 999), function<int(int, int)>(mult));
        out << aggregateMax(filter(all3DigitsProduct, predicate<int>(isPalindromic<int>)));

    }
};
