#include "NumberTheory.hpp"

bool isLucky(int n) {
    while (n > 0) {
        int d = n % 10;
        if (d != 4 && d != 7) {
            return false;
        }
        n /= 10;
    }
    return true;
}

class TaskA {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

        if (any(DivisorIterable<int>(n), isLucky)) {
            out << "YES";
        } else {
            out << "NO";
        }

	}
};
