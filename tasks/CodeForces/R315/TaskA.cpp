#include "../../../library/Number/PrimeGenerator.hpp"

char d[10];
bool isPalin(int x) {
	int n = x;
	int rev = 0;
	while (n > 0)
	{
		int d = n % 10;
		rev = rev * 10 + d;
		n /= 10;
	}
	return x == rev;
}

class TaskA {
public:
	void solve(std::istream& in, std::ostream& out) {
		const int BOUND = 2000000;
		PrimeGenerator pg(BOUND);

		int p, q;
		in >> p >> q;

		int nPrime = 0;
		int nPalin = 0;
		vector<double> ratio(BOUND + 1);
        for (int x = 1; x <= BOUND; x++) {
			if (pg.isPrime(x)) {
				nPrime++;
			}
			if (isPalin(x)) {
				nPalin++;
			}
			ratio[x] = (double) (nPrime * 1.0) / nPalin;
		}
        for (int x = BOUND; x >= 1; x--) {
			if (ratio[x] * q <= p) {
				out << x << endl;
				return;
			}
		}
		return;
	}
};
