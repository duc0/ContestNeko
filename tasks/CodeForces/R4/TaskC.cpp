#include "global.hpp"

class TaskC {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
        map<string, int> m;
		repeat(n) {
            string s;
            in >> s;
            if (m.count(s)) {
                out << s << m[s] + 1 << endl;
                m[s]++;
            } else {
                out << "OK" << endl;
                m[s] = 0;
            }
        }
	}
};
