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

bool tryBuild(const vector<int> &a, int i, vector<pair<int, int>> &groups) {
  int n = (int) a.size();
  if (!groups.empty()) {
    pair<int, int> g = groups.back();
    if (g.first + g.second - 1 >= i) {
      if (g.second != a[i]) {
        return false;
      }
      
      for_inc_range(j, i + 1, n - 1) {
        if (a[j] > 0) {
          if (!tryBuild(a, j, groups)) {
            return false;
          }
          break;
        }
      }
    }
  }
  
  for_inc_range(start, i - a[i] + 1, i) {
    if (start < 0) continue;
    if (start + a[i] - 1 >= n) continue;
    
    groups.push_back(make_pair(start, a[i]));
    
    for_inc_range(j, i + 1, n - 1) {
      if (a[j] > 0) {
        if (!tryBuild(a, j, groups)) {
          return false;
        }
        break;
      }
    }
  }
  
  return true;
}

class CountryGroupHard {
public:
   string solve( vector <int> a ) {
     int n = (int) a.size();
     vector<pair<int, int>> groups;
     for_inc(i, n) {
       if (a[i] != 0){
         if (!tryBuild(a, i, groups)) {
           return "Insufficient";
         }
         break;
       }
     }
     return "Sufficient";
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
			int a[]                   = {0,2,3,0,0};
			string expected__         = "Sufficient";

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {0,2,0};
			string expected__         = "Insufficient";

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0,3,0,0,3,0};
			string expected__         = "Sufficient";

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0,0,3,3,0,0};
			string expected__         = "Insufficient";

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {2,2,0,2,2};
			string expected__         = "Sufficient";

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = CountryGroupHard().solve(vector <int>(a, a + (sizeof a / sizeof a[0])));
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
