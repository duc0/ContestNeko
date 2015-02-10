#include <cstdio>
#include <algorithm>
#include <cstring>

#define NDEBUG
#include <cassert>

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <array>
#include <type_traits>

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(x, 0, sizeof(x))

class CartInSupermarket {
  int g(int n, int i) {
    if (i == 0) return n;
    if (n % 2 == 0) return g(n / 2, (i - 1) / 2) + 1;
    return g(n - 1, i) + 1;
  }
public:
   int calcmin( vector <int> a, int b ) {
     for (int i = 0; i <= 100; ++i) {
       cout << i << " " << g(123495, i) << endl;
     }
     return 0;
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
			int a[]                   = {8};
			int b                     = 3;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {6,6,5};
			int b                     = 3;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {12,5,6,2,6,8};
			int b                     = 4;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {15,20,11,13,18,24,25,21,22,10,15,14,19};
			int b                     = 0;
			int expected__            = 25;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {671122748,846444748,84701624,608579554,672060899,967957440,31438849,734849843,376589643,904285209 ,80693344,211737743,85405464,444633541,293184188,935462519,146753109,972886045,496631016,601669536 ,257574086,958464570,6294570,546189534,668105964,601197313,784337929,921840143,70408284,722040626 ,253400894,56411549,811940644,152086353,122638884,776352066,118932182,177589709,538122558,127914469 ,523761221,290027568,734517444,819458123,699130727,784698122,810265337,283326309,593596316,368671876};
			int b                     = 6478;
			int expected__            = 3805054;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int b                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int b                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = CartInSupermarket().calcmin(vector <int>(a, a + (sizeof a / sizeof a[0])), b);
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
