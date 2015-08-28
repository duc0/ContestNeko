#include "global.hpp"

class TaskB {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		map<string, string> m;
		repeat(n) {
            string old, new_;
            in >> old >> new_;

            if (!m.count(old)) {
                m[new_] = old;
            } else {
                m[new_] = m[old];
                m.erase(old);
            }
		}

        out << m.size() << endl;
        for (auto &e : m) {
            out << e.second << " " << e.first << endl;
        }
	}
};
