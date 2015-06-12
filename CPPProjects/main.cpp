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

class PrimeGenerator {
  vector<bool> prime;
  vector<int> primeList;
  int upper;
public:
  // Generate all primes between 2 and upper
  PrimeGenerator(int upper) {
    assert(upper >= 2);
    this->upper = upper;
    
    prime.resize(upper + 1);
    for_inc_range(i, 0, upper) {
      prime[i] = true;
    }
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= upper; ++i) {
      if (prime[i]) {
        for (int j = i * i; j <= upper; j += i) {
          prime[j] = false;
        }
      }
    }
    
    for_inc_range(i, 2, upper) {
      if (prime[i]) {
        primeList.push_back(i);
      }
    }
  }
  const vector<int> &getPrimeList() const {
    return primeList;
  }
};


#define MAXP 10000000
//#define MAXP 100
PrimeGenerator generator(MAXP);

int m1[MAXP];
int m2[MAXP];


vector<pair<int, int>> factorize(int n, const vector<int> &prime) {
  vector<pair<int, int>> ret;
  for (int p: prime) {
    if (p * p > n) {
      break;
    }
    if (n % p == 0) {
      int k = 0;
      while (n % p == 0) {
        n /= p;
        k++;
      }
      ret.push_back(make_pair(p, k));
    }
  }
  if (n > 1) {
    ret.push_back(make_pair(n, 1));
  }
  return ret;
}

class MissingLCM {
public:
  int getMin( int N ) {
    memset(m1, 0, sizeof(m1));
    memset(m2, 0, sizeof(m2));
    const vector<int> &primeList = generator.getPrimeList();
    int count = 0;
    for (int i = 1; i <= N ; ++i) {
      vector<pair<int, int>> factor = factorize(i, primeList);
      for (auto &e: factor) {
        if (m1[e.first] == 0) {
          ++count;
        }
        m1[e.first] = max(m1[e.first], e.second);
      }
    }
    for (int M = N + 1; ; ++M) {
      vector<pair<int, int>> factor = factorize(M, primeList);
      for (auto &e: factor) {
        if (m2[e.first] < m1[e.first] && e.second >= m1[e.first]) {
          --count;
        }
        m2[e.first] = max(m2[e.first], e.second);
      }
      if (count == 0) {
        return M;
      }
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
			int N                     = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 2;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 4;
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 5;
			int expected__            = 10;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 42;
			int expected__            = 82;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int N                     = 999999;
			int expected__            = 1999966;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int N                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MissingLCM().getMin(N);
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
