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

class ProblemSets {
public:
  bool ok(int64 E, int64 EM, int64 M, int64 MH, int64 H , int64 target) {
    int64 e = E, em = EM, m = M, mh = MH, h = H;
    if (e < target) {
      em -= (target - e);
      if (em < 0) return false;
      e = target;
    }
    
    m += em;
    
    if (m < target) {
      mh -= (target - m);
      if (mh < 0) return false;
      m = target;
    }
    
    h += mh;
    if (h < target) {
      return false;
    }
    return true;
  }
  
  int64 maxSets( int64 E, int64 EM, int64 M, int64 MH, int64 H ) {
    int64 best = min(min(E + EM, EM + M + MH), MH + H);
    int64 l = 0, r = best, mid;
    int64 ans = 0;
    while (l <= r) {
      mid = l + (r - l) / 2;
      
      if (ok(E, EM, M, MH, H, mid)) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return ans;
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
	
	int verify_case(int casenum, const int64 &expected, const int64 &received, std::clock_t elapsed) { 
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
			int64 E               = 2;
			int64 EM              = 2;
			int64 M               = 1;
			int64 MH              = 2;
			int64 H               = 2;
			int64 expected__      = 3;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int64 E               = 100;
			int64 EM              = 100;
			int64 M               = 100;
			int64 MH              = 0;
			int64 H               = 0;
			int64 expected__      = 0;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int64 E               = 657;
			int64 EM              = 657;
			int64 M               = 657;
			int64 MH              = 657;
			int64 H               = 657;
			int64 expected__      = 1095;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int64 E               = 1;
			int64 EM              = 2;
			int64 M               = 3;
			int64 MH              = 4;
			int64 H               = 5;
			int64 expected__      = 3;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int64 E               = 1000000000000000000LL;
			int64 EM              = 1000000000000000000LL;
			int64 M               = 1000000000000000000LL;
			int64 MH              = 1000000000000000000LL;
			int64 H               = 1000000000000000000LL;
			int64 expected__      = 1666666666666666666LL;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int64 E               = ;
			int64 EM              = ;
			int64 M               = ;
			int64 MH              = ;
			int64 H               = ;
			int64 expected__      = ;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int64 E               = ;
			int64 EM              = ;
			int64 M               = ;
			int64 MH              = ;
			int64 H               = ;
			int64 expected__      = ;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int64 E               = ;
			int64 EM              = ;
			int64 M               = ;
			int64 MH              = ;
			int64 H               = ;
			int64 expected__      = ;

			std::clock_t start__      = std::clock();
			int64 received__      = ProblemSets().maxSets(E, EM, M, MH, H);
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
