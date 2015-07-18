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

#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)

#define MAXN 220
#define MAXV 110

int f[MAXN][MAXV];

bool in[2][MAXV];

class YetAnotherCardGame {
public:
  int maxCards( vector <int> first, vector <int> second ) {
    memset(f, 0, sizeof(f));
    int n = 2 * ((int) first.size());
    
    memset(in, 0, sizeof(in));
    
    for (int x : first) {
      in[0][x] = true;
    }
    
    for (int x : second) {
      in[1][x] = true;
    }
    
    int ret = 1;
    for_inc_range(i, 1, n) {
      for_inc_range(x, 1, 100) {
        int par = (i + 1) % 2;
        if (in[par][x]) {
          int best = 1;
          for_inc_range(prev, 1, i - 1) {
            for_inc_range(prevX, 1, x - 1) {
              best = max(best, 1 + f[prev][prevX]);
            }
          }
          f[i][x] = best;
          ret = max(ret, best);
        }
      }
    }
    
    return ret;
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
			int petr[]                = {2, 5};
			int snuke[]               = {3, 1};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int petr[]                = {1, 1, 1, 1, 1};
			int snuke[]               = {1, 1, 1, 1, 1};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int petr[]                = {1, 4, 6, 7, 3};
			int snuke[]               = {1, 7, 1, 5, 7};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int petr[]                = {19, 99, 86, 30, 98, 68, 73, 92, 37, 69, 93, 28, 58, 36, 86, 32, 46, 34, 71, 29};
			int snuke[]               = {28, 29, 22, 75, 78, 75, 39, 41, 5, 14, 100, 28, 51, 42, 9, 25, 12, 59, 98, 83};
			int expected__            = 28;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int petr[]                = ;
			int snuke[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int petr[]                = ;
			int snuke[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int petr[]                = ;
			int snuke[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
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
