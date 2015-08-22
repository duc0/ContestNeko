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


#define MAXN 2520
bool is[MAXN][MAXN];

class BalancedSubstrings {
public:
  int countSubstrings( string s ) {
    memset(is, 0, sizeof(is));
    
    int n = (int) s.length();
    
    for_inc(mid, n) {
      int lw = 0;
      int rw = 0;
      int l = mid, r = mid;
      while (true) {
        if (lw == rw) {
          is[l][r] = true;
        }
        if (lw <= rw) {
          --l;
          if (l == -1) {
            break;
          }
          lw += (s[l] - '0') * (mid - l);
        } else {
          ++r;
          if (r == n) {
            break;
          }
          rw += (s[r] - '0') * (r - mid);
        }
      }
    }
    
    for_inc(mid, n) {
      int lw = 0;
      int rw = 0;
      int l = mid, r = mid;
      while (true) {
        if (lw == rw) {
          is[l][r] = true;
        }
        if (lw < rw) {
          --l;
          if (l == -1) {
            break;
          }
          lw += (s[l] - '0') * (mid - l);
        } else {
          ++r;
          if (r == n) {
            break;
          }
          rw += (s[r] - '0') * (r - mid);
        }
      }
    }
    
    for_inc_range(len, 2, n) {
      for_inc(l, n) {
        int r = l + len - 1;
        if (r >= n) break;
        
        if (s[l] == '0' && is[l + 1][r]) {
          is[l][r] = true;
        }
        if (s[r] == '0' && is[l][r - 1]) {
          is[l][r] = true;
        }
      }
    }

    int ret = 0;
    for_inc(r, n) {
      for_inc_range(l, 0, r) {
        if (is[l][r]) {
          //LOG(1, s.substr(l, r - l + 1));
          ++ret;
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
			string s                  = "011";
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "10111";
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "00000";
			int expected__            = 15;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "0000001000000";
			int expected__            = 91;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s                  = "100110001001";
			int expected__            = 49;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = BalancedSubstrings().countSubstrings(s);
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
