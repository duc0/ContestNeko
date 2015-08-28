#include "NumberTheory.hpp"

bool isLuckyDigit(int d) {
    return d == 4 || d == 7;
}
bool isLucky(int n) {
    return all(digits(n), isLuckyDigit);
}

class TaskA {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
        in >> n;
        out << toYesNo(any(divisors(n), isLucky));
	}
};
