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

class SquareScores {
public:
  double calcexpectation( vector <int> p, string s ) {
    int n = (int) s.length();
    double ans = 0;
    
    while (p.size() < 26) p.push_back(0);
    
    for_inc(i, n) {
      for_inc_range(c, 'a', 'z') {
        double prob = 1.0;
        for_inc_range(j, i, n - 1) {
          if (s[j] == '?') {
            prob *= p[c - 'a'] * 1.0 / 100;
          } else {
            if (s[j] != c) {
              break;
            }
          }
          ans += prob;
        }
      }
    }
    
    return ans;
  }
};

// BEGIN CUT HERE
#include <algorithm>
#include <cmath>
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
	
	static const double MAX_DOUBLE_ERROR = 1e-9;
	static bool topcoder_fequ(double expected, double result) {
		if (std::isnan(expected)) {
			return std::isnan(result);
		} else if (std::isinf(expected)) {
			if (expected > 0) {
				return result > 0 && std::isinf(result);
			} else {
				return result < 0 && std::isinf(result);
			}
		} else if (std::isnan(result) || std::isinf(result)) {
			return false;
		} else if (std::fabs(result - expected) < MAX_DOUBLE_ERROR) {
			return true;
		} else {
			double mmin = std::min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			double mmax = std::max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR));
			return result > mmin && result < mmax;
		}
	}
	double moj_relative_error(double expected, double result) {
		if (std::isnan(expected) || std::isinf(expected) || std::isnan(result) || std::isinf(result) || expected == 0) {
			return 0;
		}
		return std::fabs(result-expected) / std::fabs(expected);
	}
	
	int verify_case(int casenum, const double &expected, const double &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received); 
			if (rerr > 0) {
				std::sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			int p[]                   = {1, 99};
			string s                  = "aaaba";
			double expected__         = 8.0;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int p[]                   = {10, 20, 70};
			string s                  = "aa?bbbb";
			double expected__         = 15.0;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int p[]                   = {10, 20, 30, 40};
			string s                  = "a??c?dc?b";
			double expected__         = 11.117;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int p[]                   = {25, 25, 21, 2, 2, 25};
			string s                  = "a??b???????ff??e";
			double expected__         = 21.68512690712425;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int p[]                   = {4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4};
			string s                  = "??????????????????????????????";
			double expected__         = 31.16931963781721;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int p[]                   = {4, 3, 4, 3, 8, 2, 4, 3, 4, 4, 3, 2, 4, 4, 3, 4, 2, 4, 7, 6, 4, 4, 3, 4, 4, 3};
			string s                  = "makigotapresentfromniko";
			double expected__         = 23.0;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int p[]                   = ;
			string s                  = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int p[]                   = ;
			string s                  = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int p[]                   = ;
			string s                  = ;
			double expected__         = ;

			std::clock_t start__      = std::clock();
			double received__         = SquareScores().calcexpectation(vector <int>(p, p + (sizeof p / sizeof p[0])), s);
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
