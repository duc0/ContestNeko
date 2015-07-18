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

#define for_inc(i, x) for (auto i = 0; i < x; ++i)
#define for_dec(i, x) for (auto i = x - 1; i >= 0; --i)
#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)
#define for_dec_range(i, x, y) for (auto i = x; i >= y; --i)

#define pb push_back

#define MAXN 220
#define MAXV 110

template<class T> T binarySearchMax(const T &minIndex, const T &maxIndex, const function<bool(T)> &predicate) {
  T leftIndex = minIndex, rightIndex = maxIndex, midIndex, ret = minIndex - 1;
  while (leftIndex <= rightIndex) {
    midIndex = leftIndex + (rightIndex - leftIndex) / 2;
    if (predicate(midIndex)) {
      ret = midIndex;
      leftIndex = midIndex + 1;
    } else {
      rightIndex = midIndex - 1;
    }
  }
  return ret;
}

// Find LIS in O(nlogn)
// Usage: construct with iterators
// Then query the LIS
// O(nlogn)

template <class T> class LongestIncreasingSubsequence {
  int n, longest;
  vector<int> minVal; // minVal[k] = min{a[i], lis(i) = k}
  
public:
  template<class Iterator> LongestIncreasingSubsequence(Iterator begin, Iterator end) {
    vector<T> seq(begin, end);
    
    n = (int) seq.size();
    
    minVal.resize(n + 1);
    minVal[1] = seq[0];
    
    longest = 1;
    for_inc_range(i, 1, n - 1) {
      int k = binarySearchMax<int>(1, longest, [&](int l) {return minVal[l] < seq[i];});
      if (k == longest) {
        longest++;
        minVal[longest] = seq[i];
      } else {
        minVal[k + 1] = min(minVal[k + 1], seq[i]);
      }
    }
  }
  
  int getLength() {
    return longest;
  }
};

int f[MAXN][MAXV];

bool in[2][MAXV];

int ra[105], rb[105];

class YetAnotherCardGame {
public:
  int maxCards( vector <int> a, vector <int> b ) {
    vector<int> p, s;
    
    for_inc(i, a.size()) {
      p.pb(a[i]);
    }
    
    
    for_inc(i, b.size()) {
      s.pb(b[i]);
    }
    
    int p1 = p.size(), s1 = s.size(), mo;
    
    if (s1 < p1) {
      mo = s1 + s1 + 1;
    } else {
      mo = p1 + p1;
    }
    
    int dp[mo + 5][140];
    
    memset(dp, 0, sizeof(dp));
    
    for_inc_range(i, 1, mo) {
      if (i % 2 == 1) {
        for_inc(j, p1) {
          for_dec_range(k, p[j] - 1, 0) {
            dp[i][p[j]] = max(dp[i - 1][k] + 1, dp[i][p[j]]);
          }
        }
      } else {
        for_inc(j, s1) {
          for_dec_range(k, s[j] - 1, 0) {
            dp[i][s[j]] = max(dp[i - 1][k] + 1, dp[i][s[j]]);
          }
        }
      }
      for_inc_range(j, 1, 100) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j]);
      }
    }
    int ans = 0;
    for_inc_range(i, 1, 100) {
      ans = max(dp[mo][i], ans);
    }
    return ans;
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
			int petr[]                = {2, 5};
			int snuke[]               = {3, 1};
			int expected__            = 3;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int petr[]                = {1, 1, 1, 1, 1};
			int snuke[]               = {1, 1, 1, 1, 1};
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int petr[]                = {1, 4, 6, 7, 3};
			int snuke[]               = {1, 7, 1, 5, 7};
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int petr[]                = {19, 99, 86, 30, 98, 68, 73, 92, 37, 69, 93, 28, 58, 36, 86, 32, 46, 34, 71, 29};
			int snuke[]               = {28, 29, 22, 75, 78, 75, 39, 41, 5, 14, 100, 28, 51, 42, 9, 25, 12, 59, 98, 83};
			int expected__            = 28;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
        int petr[]                = {50, 27, 64, 25, 48, 98, 9, 32, 68, 9, 16, 83, 98, 32, 19, 98, 33, 61, 61, 64, 92, 97, 70, 83, 80, 65, 44, 23, 27, 94, 71, 11, 92, 28, 70, 46, 27, 21, 58, 42, 63, 70, 82, 86, 63, 97, 50, 89, 82, 82};
        int snuke[]               = {13, 58, 52, 10, 37, 52, 1, 1, 59, 42, 98, 86, 83, 81, 23, 73, 10, 14, 38, 25, 4, 52, 97, 8, 24, 93, 53, 47, 42, 83, 48, 41, 37, 78, 2, 45, 64, 1, 32, 35, 65, 52, 50, 31, 43, 93, 12, 9, 16, 6};
			int expected__            = 58;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 5: {
        int petr[]                = {17, 22, 25, 47, 32, 40, 18, 33, 45, 33, 49, 46, 28, 15, 42, 19, 15, 41, 45, 45, 49, 22, 17, 19, 50, 19, 20, 15, 16, 16, 27, 20, 26, 48, 21, 44, 41, 35, 35, 42, 36, 23, 26, 23, 29, 50, 30, 17, 32, 44};
        int snuke[]               = {31, 40, 18, 17, 38, 16, 25, 28, 21, 16, 15, 49, 39, 49, 32, 49, 46, 37, 33, 33, 23, 28, 41, 22, 45, 33, 36, 44, 38, 19, 23, 15, 15, 49, 36, 49, 43, 26, 49, 48, 31, 17, 26, 20, 28, 17, 40, 50, 22, 43};
			int expected__            = 34;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
        int petr[]                = {49, 56, 61, 95, 72, 85, 50, 73, 92, 74, 97, 94, 65, 45, 87, 52, 45, 85, 92, 91, 98, 56, 49, 51, 99, 51, 53, 46, 47, 47, 64, 54, 62, 97, 54, 90, 86, 76, 77, 88, 77, 57, 63, 58, 67, 100, 68, 48, 71, 90};
        int snuke[]               = {25, 39, 5, 4, 37, 3, 17, 22, 11, 3, 1, 53, 38, 53, 28, 53, 48, 34, 29, 28, 13, 21, 40, 11, 47, 29, 34, 46, 36, 8, 14, 1, 2, 53, 33, 54, 43, 18, 54, 51, 26, 5, 18, 10, 21, 5, 40, 54, 12, 43};
			int expected__            = 54;

			std::clock_t start__      = std::clock();
			int received__            = YetAnotherCardGame().maxCards(vector <int>(petr, petr + (sizeof petr / sizeof petr[0])), vector <int>(snuke, snuke + (sizeof snuke / sizeof snuke[0])));
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
