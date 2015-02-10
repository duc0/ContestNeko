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

class Decipherability {
public:
   string check( string s, int k ) {
     int n = (int) s.length();
     k = n - k;
     if (k == 0) {
       return "Certain";
     }
     for (int i = 0; i < n; ++i) {
       for (int j = i + 1; j < n; ++j) {
         if (s[i] == s[j]) {
           if (i + n - 1 - j >= k - 1) {
             return "Uncertain";
           }
         }
       }
     }
     return "Certain";
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string s                  = "snuke";
			int K                     = 2;
			string expected__         = "Certain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "aba";
			int K                     = 1;
			string expected__         = "Certain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "aba";
			int K                     = 2;
			string expected__         = "Uncertain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "abcdabcd";
			int K                     = 3;
			string expected__         = "Certain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s                  = "koukyoukoukokukikou";
			int K                     = 2;
			string expected__         = "Uncertain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string s                  = "wolfsothe";
			int K                     = 8;
			string expected__         = "Uncertain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string s                  = "aa";
			int K                     = 2;
			string expected__         = "Certain";

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = Decipherability().check(s, K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
moj_harness::run_test(6);
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
