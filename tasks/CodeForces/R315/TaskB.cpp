#include "ModInt.hpp"
#include "ComboUtils.hpp"

class TaskB {
public:
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		n++;
		vector<ModInt<int, MOD>> bell(n + 1);
		bell[0] = 1;
		ComboUtils<ModInt<int, MOD>> combo(n);
		FOR_INC_RANGE(i, 0, n - 1) {
			bell[i + 1] = 0;
			vector<ModInt<int, MOD>> c = combo.getCombByN(i);
			FOR_INC_RANGE(k, 0, i) {
				bell[i + 1] = bell[i + 1] + c[k] * bell[k];
			}
		}
		out << bell[n] - bell[n - 1] << endl;
	}
};
