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

#define MOD 1000000007

int64 lcm(int64 a, int64 b) {
  return (int64) ( a * b) / __gcd(a, b);
}

void factor(int n, vector<int> &factor, vector<int> &power) {
  factor.clear();
  power.clear();
  for (int i=2; i*i<=n; ++i) {
    if (n%i == 0) {
      factor.push_back(i);
      int p;
      for (p=0; n%i==0; n/=i, ++p);
      power.push_back(p);
    }
  }
  if (n>1) {
    factor.push_back(n);
    power.push_back(1);
  }
}

map<int, int> cnt;

class ThePermutationGame {
public:
   int findMin( int n ) {
     cnt.clear();
     for (int i = 1; i <= n; ++i) {
       vector<int> f, p;
       factor(i, f, p);
       for (int k = 0; k < f.size(); ++k) {
         if (cnt.count(f[k])) {
           cnt[f[k]] = max(cnt[f[k]], p[k]);
         } else {
           cnt[f[k]] = p[k];
         }
       }
     }
     int64 ret = 1;
     for (auto &e: cnt) {
       int64 p = 1;
       repeat(e.second) {
         p = (p * (e.first)) % MOD;
       }
       ret = (ret * p) % MOD;
     }
     return (int)ret;
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
			int N                     = 2;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 11;
			int expected__            = 27720;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 102;
			int expected__            = 53580071;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 9999;
			int expected__            = 927702802;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = ThePermutationGame().findMin(N);
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
