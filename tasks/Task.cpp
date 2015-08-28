#include <iostream>
#include "../library/lib.hpp"

class Task {
public:
	void solve(std::istream& in, std::ostream& out) {
		int x;
		in >> x;
		out << x + getTheAnswer() << "\n";
	}
};
