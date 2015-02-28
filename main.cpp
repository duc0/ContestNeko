// Paste me into the FileEdit configuration dialog

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

using namespace std;

// BEGIN CUT HERE
#define LOG(l, x)                                                              \
if (l <= LOGLEVEL)                                                           \
cout << x << endl
// END CUT HERE

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

class RobotOnMoon {
public:
   int longestSafeCommand(vector <string> board ) {
     int nRow = (int) board.size();
     int nCol = (int) board[0].length();
     int startR = 0, startC = 0;
     for_inc(r, nRow) for_inc(c, nCol) if (board[r][c] == 'S') {
       startR = r;
       startC = c;
     }
     for_inc_range(c, 0, startC - 1) {
       if (board[startR][c] != '.') {
         return -1;
       }
     }
     for_inc_range(c, startC + 1, nCol - 1) {
       if (board[startR][c] != '.') {
         return -1;
       }
     }
     for_inc_range(r, 0, startR - 1) {
       if (board[r][startC] != '.') {
         return -1;
       }
     }
     for_inc_range(r, startR + 1, nRow - 1) {
       if (board[r][startC] != '.') {
         return -1;
       }
     }
     return startR + startC + (nRow - 1 - startR) + (nCol - 1 - startC);
     
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
			string board[]            = {"#####",
 "#...#",
 "#.S.#",
 "#...#",
 "#####"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string board[]            = {"S......"};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string board[]            = {"#.######",
 "#.#..S.#",
 "#.#.##.#",
 "#......#",
 "########"};
			int expected__            = -1;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string board[]            = {"S"};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string board[]            = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = RobotOnMoon().longestSafeCommand(vector <string>(board, board + (sizeof board / sizeof board[0])));
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
