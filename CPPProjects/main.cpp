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

vector<pair<int ,int>> factor(int n) {
  int i = 2;
  vector<pair<int, int>> ans;
  while (i * i <= n) {
    if (n % i == 0) {
      int c = 0;
      while (n % i == 0) {
        n /= i;
        c++;
      }
      ans.push_back(make_pair(i, c));
    }
    i++;
  }
  if (n > 1) {
    ans.push_back(make_pair(n, 1));
  }
  return ans;
}

vector<pair<int ,int>> merge(const vector<pair<int ,int>>&a, const vector<pair<int ,int>> &b) {
  vector<pair<int ,int>> ans;
  int i = 0, j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i].first == b[j].first) {
      ans.push_back(make_pair(a[i].first, a[i].second + b[j].second));
      ++i;
      ++j;
    } else if (a[i].first < b[j].first) {
      ans.push_back(a[i]);
      ++i;
    } else {
      ans.push_back(b[j]);
      ++j;
    }
  }
  
  while (i < a.size()) {
    ans.push_back(a[i]);
    ++i;
  }
  
  while (j < b.size()) {
    ans.push_back(b[j]);
    ++j;
  }
  
  return ans;
}

vector<pair<int ,int>> getGcd(const vector<pair<int ,int>>&a, const vector<pair<int ,int>> &b) {
  vector<pair<int ,int>> ans;
  int i = 0, j = 0;
  while (i < a.size() && j < b.size()) {
    if (a[i].first == b[j].first) {
      ans.push_back(make_pair(a[i].first, min(a[i].second, b[j].second)));
      ++i;
      ++j;
    } else if (a[i].first < b[j].first) {
      ++i;
    } else {
      ++j;
    }
  }
  return ans;
}

int64 powerMod(int a, int b) {
  int64 ans = 1;
  for_inc_range (i, 1, b) {
    ans = (ans * a) % MOD;
  }
  return ans;
}

class PolynomialGCD {
public:
  int gcd( string s ) {
    int l = (int) s.length();
    int val = 30000;
    int cnt = 100;
    
    vector<pair<int, int>> ans;
    bool first = true;
    for_inc_range(x, val, val + cnt) {
      vector<pair<int, int>> g;
      for_inc(i, l) {
        int y = x - i;
        
        vector<pair<int ,int>> f = factor(y);
        for_inc(t, f.size()) {
          f[t].second *= s[i] - '0';
        }
        g = merge(g, f);
      }
      if (first) {
        ans = g;
        first = false;
      } else {
        ans = getGcd(ans, g);
      }
    }
    
    int64 ret = 1;
    for (auto &p : ans) {
      ret = (ret * (powerMod(p.first, p.second))) % MOD;
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
			string s                  = "111";
			int expected__            = 6;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "00000";
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "2014";
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "31415926535";
			int expected__            = 659897170;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 4: {
        ostringstream ss;
        string s                  = "";
        for_inc(i, 10000) ss << "9";
        s = ss.str();
        int expected__            = 562564034;
        
        std::clock_t start__      = std::clock();
        int received__            = PolynomialGCD().gcd(s);
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }

		// custom cases

/*      case 4: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s                  = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = PolynomialGCD().gcd(s);
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
