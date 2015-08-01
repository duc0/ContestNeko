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

class BearPlays {  
public:
  int pileSize( int a, int b, int k ) {
    if (a > b) {
      swap(a, b);
    }
    unordered_map<int, int> pos;
    pos[a] = 0;
    int i = 1;
    while (i <= k) {
      while (i <= k && a <= b) {
        b -= a;
        a += a;
        i++;
      }
      i--;
      swap(a, b);
      //LOG(1, a);
      if (pos.count(a)) {
        int l = i - pos[a];
        int x = (k - i) / l;
        i = i + l * x;
        i++;
        break;
      }
      pos[a] = i;
      i++;
    }
    
    while (i <= k) {
      b -= a;
      a += a;
      if (a > b) {
        swap(a, b);
      }
      i++;
    }
    
    return a;
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
	void run_test(int casenum = 5, bool quiet = false) {
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
			int A                     = 4;
			int B                     = 7;
			int K                     = 2;
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int A                     = 5;
			int B                     = 5;
			int K                     = 3;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int A                     = 2;
			int B                     = 6;
			int K                     = 1;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int A                     = 2;
			int B                     = 8;
			int K                     = 2000000000;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int A                     = 900000000;
			int B                     = 350000000;
			int K                     = 3;
			int expected__            = 300000000;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
        int A                     = 433234427;
        int B                     = 934233244;
        int K                     = 1990000004;
        int expected__            = 501577480;
        
        std::clock_t start__      = std::clock();
        int received__            = BearPlays().pileSize(A, B, K);
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 6: {
        int A                     = 33234427;
        int B                     = 934233249;
        int K                     = 1090002004;
        int expected__            = 92445112;
        
        std::clock_t start__      = std::clock();
        int received__            = BearPlays().pileSize(A, B, K);
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }

		// custom cases

/*      case 5: {
			int A                     = ;
			int B                     = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int A                     = ;
			int B                     = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int A                     = ;
			int B                     = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BearPlays().pileSize(A, B, K);
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
