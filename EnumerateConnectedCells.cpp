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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int n;
vector<pair<int, int>> origPoints;
int64 best = INT64_INF;

int64 dist(pair<int, int> a, pair<int, int> b) {
  return abs((int64)a.first - b.first) + abs((int64)a.second - b.second);
}

void updateBest(const vector<pair<int, int>> &points) {
  vector<pair<int, int>> translatedPoints(n);
  for (int rootx = 0; rootx < n; ++rootx) for (int rooty = 0; rooty < n; ++rooty) {
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        translatedPoints[i] = make_pair(
                                        origPoints[rootx].first + (points[i].first - points[k].first),
                                        origPoints[rooty].second + (points[i].second - points[k].second)
                                        );
      }
      
      vector<int> perm(n);
      for (int i = 0; i < n; ++i) {
        perm[i] = i;
      }
      do {
        int64 ret = 0;
        for (int i = 0; i < n; ++i) {
          ret += dist(origPoints[i], translatedPoints[perm[i]]);
        }
        best = min(best, ret);
      } while (next_permutation(perm.begin(), perm.end()));
    }
  }
}

// Enumerate all the set of possible connected cells (in a grid)
// The origin is picked at (0, 0). No other cells (x, y) should have
// x < 0 or (x == 0 and y < 0).
// Usage EnumerateConnectedCells(n, callBack): set n and the callback function
// that get calls when each connected set is found

class EnumerateConnectedCells {
  vector<pair<int, int>> points;
  vector<vector<bool>> visit;
  function<void(const vector<pair<int, int>>&)> callback;
  set<vector<pair<int, int>>> seen;
  
  void tryBuild(int k) {
    if (k == n + 1) {
      vector<pair<int, int>> state = points;
      sort(state.begin(), state.end());
      if (seen.count(state)) {
        return;
      }
      seen.insert(state);
      callback(points);
      return;
    }
    for (int t = 0; t < (int) points.size(); ++t) {
      int x = points[t].first;
      int y = points[t].second;
      for (int i = 0; i < 4; ++i) {
        int x2 = x + dx[i];
        int y2 = y + dy[i];
        if (!(x2 < 0 || (x2 == 0 && y2 < 0)) && !visit[x2][10 + y2]) {
          points.push_back(make_pair(x2, y2));
          visit[x2][10 + y2] = true;
          tryBuild(k + 1);
          points.pop_back();
          visit[x2][10 + y2] = false;
        }
      }
    }
  }
public:
  EnumerateConnectedCells(int numCells, function<void(const vector<pair<int, int>>&)> callback) {
    this->callback = callback;
    points.clear();
    points.push_back(make_pair(0, 0));
    visit.resize(numCells);
    for (auto &v: visit) {
      v.resize(numCells * 2);
    }
    seen.clear();
    tryBuild(2);
  }
};

// Sample: SRM 651, P2
class FoxConnection3 {
public:
  long long minimalSteps( vector <int> x, vector <int> y ) {
    n = (int) x.size();
    
    origPoints.clear();
    for_inc(i, n) {
      origPoints.push_back(make_pair(x[i], y[i]));
    }
    best = INT64_INF;
    EnumerateConnectedCells e(n, updateBest);
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
  
  int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
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
        int x[]                   = {0,0,1,-2};
        int y[]                   = {1,-1,0,0};
        long long expected__      = 2;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 1: {
        int x[]                   = {0,0,0,0,0,0};
        int y[]                   = {1,2,3,4,5,6};
        long long expected__      = 0;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 2: {
        int x[]                   = {-123456789,-58585858,-47474747,123,456,789012345};
        int y[]                   = {0,0,0,0,0,0};
        long long expected__      = 1018530309;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 3: {
        int x[]                   = {1,7,3,5,2};
        int y[]                   = {2,7,5,3,7};
        long long expected__      = 12;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 4: {
        int x[]                   = {-3,0,1,-2,3,2};
        int y[]                   = {2,-3,0,1,-1,-1};
        long long expected__      = 10;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 5: {
        int x[]                   = {-96277832,507856257,-86306299,-806700273,-775932643,-273209838};
        int y[]                   = {-955536464,-599634138,399850429,-165706338,-537800480,738983556};
        long long expected__      = 5247213600LL;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
      case 6: {
        int x[]                   = {0};
        int y[]                   = {0};
        long long expected__      = 0;
        
        std::clock_t start__      = std::clock();
        long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
        return verify_case(casenum__, expected__, received__, clock()-start__);
      }
        
        // custom cases
        
        /*      case 7: {
         int x[]                   = ;
         int y[]                   = ;
         long long expected__      = ;
         
         std::clock_t start__      = std::clock();
         long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
         return verify_case(casenum__, expected__, received__, clock()-start__);
         }*/
        /*      case 8: {
         int x[]                   = ;
         int y[]                   = ;
         long long expected__      = ;
         
         std::clock_t start__      = std::clock();
         long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
         return verify_case(casenum__, expected__, received__, clock()-start__);
         }*/
        /*      case 9: {
         int x[]                   = ;
         int y[]                   = ;
         long long expected__      = ;
         
         std::clock_t start__      = std::clock();
         long long received__      = FoxConnection3().minimalSteps(vector <int>(x, x + (sizeof x / sizeof x[0])), vector <int>(y, y + (sizeof y / sizeof y[0])));
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
