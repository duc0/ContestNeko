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


int computeSwitch(const vector<int> &pitch, const vector<int> &assign) {
  int nPitch = (int) pitch.size();
  int sw = 0;
  for_inc(i, nPitch) {
    if (i > 0 && assign[pitch[i]] != assign[pitch[i - 1]]) {
      sw++;
    }
  }
  return sw;
}

vector<pair<int, int>> buildGroup(const vector<int> &pitch, const vector<int> &assign) {
  vector<pair<int, int>> ret;
  int nPitch = (int) pitch.size();
  
  int cur = assign[pitch[0]];
  int start = 0;
  for_inc(i, nPitch) {
    if (i > 0 && assign[pitch[i]] != assign[pitch[i - 1]]) {
      if (cur == 1) {
        ret.push_back(make_pair(start, i - 1));
      }
      start = i;
      cur = assign[pitch[i]];
    }
  }
  if (cur == 1) {
    ret.push_back(make_pair(start, nPitch - 1));
  }
  return ret;

}

class Singing {
public:
   int solve( int n, int low, int high, vector <int> pitch ) {
     int nPitch = (int) pitch.size();
     
     vector<pair<int, int>> group;
     vector<int> assign(n + 1);
     
     for_inc_range(i, 1, high) {
       assign[i] = 1;
     }
     
     int best = computeSwitch(pitch, assign);
     
     while (1) {
       group = buildGroup(pitch, assign);
       bool found = false;
       for (auto &g: group) {
         int l = g.first, r = g.second;
         
         bool cannot = false;
         for_inc_range(j, l, r) {
           if (pitch[j] < low) {
             cannot = true;
             break;
           }
         }
         if (cannot) {
           continue;
         }
         
         for_inc_range(j, l, r) {
           assign[pitch[j]] = 0;
         }
         
         int ans = computeSwitch(pitch, assign);
         if (ans < best) {
           found = true;
           best = ans;
           break;
         }

         for_inc_range(j, l, r) {
           assign[pitch[j]] = 1;
         }

       }
       
       if (!found) {
         break;
       }
     }
     
     return best;
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
			int low                   = 2;
			int high                  = 2;
			int pitch[]               = {1,2,3,2,1,2};
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 10;
			int low                   = 3;
			int high                  = 7;
			int pitch[]               = {4,4,5,5,6,5,3,6};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 6;
			int low                   = 2;
			int high                  = 5;
			int pitch[]               = {5,3,1,6,4,2};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 10;
			int low                   = 4;
			int high                  = 5;
			int pitch[]               = {1,4,3,5,2,5,7,5,9};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 100;
			int low                   = 20;
			int high                  = 80;
			int pitch[]               = {2,27,3,53,53,52,52,60,85,89,100,53,60,2,3,53,100,89,40,42,2,53,2,85};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int low                   = ;
			int high                  = ;
			int pitch[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int low                   = ;
			int high                  = ;
			int pitch[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int low                   = ;
			int high                  = ;
			int pitch[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Singing().solve(N, low, high, vector <int>(pitch, pitch + (sizeof pitch / sizeof pitch[0])));
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
