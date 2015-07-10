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

vector<pair<int, int>> a;
int calcD(const vector<int> &s) {
  int n = (int) s.size();
  int d = abs(a[s[0]].first - a[s[n - 1]].first);
  for_inc_range(i, 1, n - 1) {
    d = max(d, abs(a[s[i]].first - a[s[i - 1]].first));
  }
  return d;
}

class FoxesOfTheRoundTable {
public:
  vector <int> minimalDifference( vector <int> h ) {
    a.clear();
    int n = (int) h.size();
    a.resize(n);
    for_inc(i, n) {
      a[i] = make_pair(h[i], i);
    }
    sort(a.begin(), a.end());
    
    vector<int> b(n);
    b[0] = 0;
    int bestD = INT_INF;
    vector<int> bestRet;
    for_inc_range(i, 1, n - 1) {
      b[n - 1] = i;
      int posBegin = 1;
      for_inc_range(j, 0, n - 1) {
        if (j != i && j != 0) {
          b[posBegin] = j;
          ++posBegin;
        }
      }
      int d = calcD(b);
      if (d < bestD) {
        bestD = d;
        bestRet = b;
      }
    }
    vector<int> ret(n);
    for_inc(i, n) {
      ret[i] = a[bestRet[i]].second;
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
	void run_test(int casenum = 3, bool quiet = false) {
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
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, std::clock_t elapsed) { 
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
			int h[]                   = {1,99,50,50};
			int expected__[]          = {0, 3, 1, 2 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int h[]                   = {123,456,789};
			int expected__[]          = {0, 1, 2 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int h[]                   = {10,30,40,50,60};
			int expected__[]          = {0, 1, 4, 3, 2 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int h[]                   = {1,2,3,4,8,12,13,14 };
			int expected__[]          = {0, 1, 2, 3, 5, 6, 7, 4 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int h[]                   = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
			int expected__[]          = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int h[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int h[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int h[]                   = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FoxesOfTheRoundTable().minimalDifference(vector <int>(h, h + (sizeof h / sizeof h[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
