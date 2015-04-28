#define LOGLEVEL 0
#define NDEBUG

// BEGIN CUT HERE
#define LOGLEVEL 1
// END CUT HERE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <array>
#include <type_traits>
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <climits>
#include <cfloat>
#include <random>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << x << endl

#define int64 long long
#define repeat(x) for (auto repeat_var = 0; repeat_var < x; ++repeat_var)

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF ((int)2E9L)
#define INT64_INF ((int64)1E18L)
#define MOD 1000000007

bool isPrime(int p) {
  if (p <= 1) return false;
  for (int i = 2; i * i <= p; ++i) {
    if (p % i == 0) return false;
  }
  return true;
}

// Solve for all x = r (MOD m)  ; for m = p ^ k
int solve(const vector<int> &cnt, int p, int r, int m) {
  int n = (int) cnt.size();
  
  if (r + m * (p - 1) >= n) {
    return 0;
  }

  int newM = m * p;
  int res = INT_INF;
  for (int newR = r; newR < newM; newR += m) {
    int sub = 0;
    for (int i = newR; i < n; i += newM) {
      sub += cnt[i];
    }
    sub += solve(cnt, p, newR, newM);
    res = min(res, sub);
  }
  
  return res;
}

int solve(const vector<int> &cnt, int p) {
  return solve(cnt, p, 0, 1);
}

class PolynomialGCD {
public:
  int gcd( string s ) {
    int n = (int) s.length();
    vector<int> cnt(n);
    for_inc(i, n) cnt[i] = (int) (s[i] - '0');
    int64 res = 1;
    for_inc_range(p, 2, n) {
      if (isPrime(p)) {
        int k = solve(cnt, p);
        repeat(k) {
          res = (res * p) % MOD;
        }
      }
    }
    return (int)res;
  }
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string s                  = "111";
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "00000";
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "2014";
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "31415926535";
			int expected__            = 659897170;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
