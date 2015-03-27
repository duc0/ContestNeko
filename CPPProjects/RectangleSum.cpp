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

template <class T> class RectangleSum {
  vector<vector<T>> sum;
  vector<vector<T>> a;
  bool built;
  int nRow, nCol;
public:
  RectangleSum(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;
    
    sum.resize(nRow + 1);
    for_inc_range(i, 0, nRow) sum[i].resize(nCol + 1);
    
    a.resize(nRow + 1);
    for_inc_range(i, 0, nRow) a[i].resize(nCol + 1);
    
    built = false;
  }
  
  void set(int r, int c, T v) {
    a[r][c] = v;
    built = false;
  }
  
  void build() {
    for_inc_range(r, 1, nRow) for_inc_range(c, 1, nCol) {
      sum[r][c] = sum[r][c - 1] + sum[r - 1][c] - sum[r - 1][c - 1] + a[r][c];
    }
    built = true;
  }
  
  T getSum(int r1, int c1, int r2, int c2) const {
    assert(built);
    return sum[r2][c2] - sum[r1 -1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
  }
};


// SRM636 - P1
class ChocolateDividingEasy {
public:
  int findBest( vector <string> a ) {
    int nRow = (int) a.size();
    int nCol = (int) a[0].size();
    
    RectangleSum<int> sum(nRow, nCol);
    for_inc_range(r, 1, nRow) for_inc_range(c, 1, nCol) sum.set(r, c, a[r - 1][c - 1] - '0');
    sum.build();
    
    int best = 0;
    for_inc_range(cutR1, 1, nRow - 1) {
      for_inc_range(cutR2, cutR1 + 1, nRow - 1) {
        for_inc_range(cutC1, 1, nCol - 1) {
          for_inc_range(cutC2, cutC1 + 1, nCol - 1) {
            vector<int> r1s = {1, cutR1 + 1, cutR2 + 1};
            vector<int> r2s = {cutR1, cutR2, nRow};
            vector<int> c1s = {1, cutC1 + 1, cutC2 + 1};
            vector<int> c2s = {cutC1, cutC2, nCol};
            
            int ans = INT_INF;
            for_inc(id1, 3) {
              for_inc(id2, 3) {
                int cur = sum.getSum(r1s[id1], c1s[id2], r2s[id1], c2s[id2]);
                ans = min(ans, cur);
              }
            }
            best = max(best, ans);
          }
        }
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
        string chocolate[]        = {
          "9768",
          "6767",
          "5313"
        };
        int expected__            = 3;
        
        std::clock_t start__      = std::clock();
        int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 1: {
        string chocolate[]        = {
          "36753562",
          "91270936",
          "06261879",
          "20237592",
          "28973612",
          "93194784"
        };
        int expected__            = 15;
        
        std::clock_t start__      = std::clock();
        int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 2: {
        string chocolate[]        = {
          "012",
          "345",
          "678"
        };
        int expected__            = 0;
        
        std::clock_t start__      = std::clock();
        int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
        
        // custom cases
        
        /*      case 3: {
         string chocolate[]        = ;
         int expected__            = ;
         
         std::clock_t start__      = std::clock();
         int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
         return verify_case(casenum__, expected__, received__, clock()-start__);
         }*/
        /*      case 4: {
         string chocolate[]        = ;
         int expected__            = ;
         
         std::clock_t start__      = std::clock();
         int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
         return verify_case(casenum__, expected__, received__, clock()-start__);
         }*/
        /*      case 5: {
         string chocolate[]        = ;
         int expected__            = ;
         
         std::clock_t start__      = std::clock();
         int received__            = ChocolateDividingEasy().findBest(vector <string>(chocolate, chocolate + (sizeof chocolate / sizeof chocolate[0])));
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
