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

class ApplesAndOrangesEasy {
public:
  int maximumApples( int n, int k, vector <int> info ) {
    vector<int> a(n + 2 * k, 0);
    for (auto i: info) {
      a[i + k - 1] = 1;
    }
    for (int tic = k; tic < n + k; ++tic) {
      bool fail = false;
      if (a[tic] == 1) {
        continue;
      }
      int acc = 0;
      for (int i = tic - k; i < tic; ++i) {
        acc += a[i];
      }
      for (int i = tic - k + 1; i < tic + 1 && !fail ; ++i) {
        acc += a[i + k - 1] - a[i - 1];
        fail = (k / 2) < acc + 1;
      }
      a[tic] = !fail ? 1 : 0;
    }
    return accumulate(a.begin(), a.end(), 0);
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
			int N                     = 3;
			int K                     = 2;
			int info[]                = {};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 10;
			int K                     = 3;
			int info[]                = {3, 8};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 9;
			int K                     = 4;
			int info[]                = {1, 4};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 9;
			int K                     = 4;
			int info[]                = {2, 4};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 23;
			int K                     = 7;
			int info[]                = {3, 2, 9, 1, 15, 23, 20, 19};
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int N                     = 2000;
			int K                     = 1999;
        int info[]                = {};
			int expected__            = 1000;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
			int N                     = 2000;
			int K                     = 997;
      int info[]                = {};
			int expected__            = 1002;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 7: {
			int N                     = 2000;
			int K                     = 1505;
        int info[]                = {1, 25, 7, 887, 907, 908, 909, 24, 23, 2, 3, 4, 5, 6, 8, 10};
			int expected__            = 1247;

			std::clock_t start__      = std::clock();
			int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 8: {
        int N                     = 2000;
        int K                     = 3;
        int info[]                = {1, 4, 1998, 1995};
        int expected__            = 666;
        
        std::clock_t start__      = std::clock();
        int received__            = ApplesAndOrangesEasy().maximumApples(N, K, vector <int>(info, info + (sizeof info / sizeof info[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }

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
