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

template <class T> class WeightedDirectedGraph {
  vector<vector<pair<int, T>>> nodeFrom;
  vector<vector<pair<int, T>>> nodeTo;
  vector<int> degIn, degOut;
  int _minNode, _maxNode;
public:
  void init(bool zeroBased, int n) {
    if (zeroBased) {
      _minNode = 0;
      _maxNode = n - 1;
    } else {
      _minNode = 1;
      _maxNode = n;
    }
    nodeFrom.resize(_maxNode + 1);
    nodeTo.resize(_maxNode + 1);
    degIn.resize(_maxNode + 1);
    degOut.resize(_maxNode + 1);
    for_inc_range(u, _minNode, _maxNode) {
      degIn[u] = 0;
      degOut[u] = 0;
      nodeFrom[u].clear();
      nodeTo[u].clear();
    }
  }
  
  void addEdge(int u, int v, T w) {
    nodeFrom[u].push_back(make_pair(v, w));
    degOut[u]++;
    
    nodeTo[v].push_back(make_pair(u, w));
    degIn[v]++;
  }
  
  const vector<int>& getNodeFrom(int u) const {
    return nodeFrom[u];
  }
  
  const vector<int>& getNodeTo(int u) const {
    return nodeTo[u];
  }
  
  int getDegIn(int u) const {
    return degIn[u];
  }
  
  int getDegOut(int u) const {
    return degOut[u];
  }
};

class MaliciousPath {
public:
   long long minPath( int n, int k, vector <int> from, vector <int> to, vector <int> cost ) {
     WeightedDirectedGraph<int> graph;
     graph.init(true, n);
     int m = (int)from.size();
     for_inc(i, m) {
       graph.addEdge(from[i], to[i], cost[i]);
     }
     
     vector<vector<int64>> f;
     f.resize(k + 1);
     for_inc_range(i, 1, k) {
       f[i].resize(n);
     }
     
     for_inc_range(nToken, 0, k) {
       
       
       
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
			int N                     = 3;
			int K                     = 1000;
			int from[]                = {0,1,1,2};
			int to[]                  = {1,0,2,2};
			int cost[]                = {3,2,1,1};
			long long expected__      = 5004;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 4;
			int K                     = 1;
			int from[]                = {0,0,1,1,1,2,2,3};
			int to[]                  = {1,3,0,2,3,2,1,3};
			int cost[]                = {0,100,103,0,0,34,102,33};
			long long expected__      = 100;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 10;
			int K                     = 5;
			int from[]                = {0,0,1,1,2,2,3,3,4,4,4,5,5,6,6,7,7,8,8,9,9};
			int to[]                  = {1,1,2,2,3,3,4,4,5,5,4,6,6,7,7,8,8,9,9,9,9};
			int cost[]                = {2,10,10,1,2,10,10,1,2,10,100,10,2,1,10,10,2,1,10,10,1};
			long long expected__      = 514;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 50;
			int K                     = 200;
			int from[]                = {0,13,8,17,3,8,4,21,11,20,2,18,21,2,4,9,17,0,14,10,15,18,1,22,10,14, 19,24,5,5,12,7,7,16,19,13,20,15,23,6,23,9,3,6,16,11,22,24,12,1,25,25, 26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37, 37,38,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48, 49,49,37,9,14,0,33,20,46,26,12,11,2,7,34,19,37,5,2,17,41,16,34,13,18, 35,6,14,16,25,9,10,5,10,7,36,45,3,6,22,32,28,45,40,16,36,28,16,34,1, 9,19,18,6,15,29,12,5,44,33,49,14,40,1,30,21,37,49,1,44,42,6,38,1,31, 40,37,34,35,6,43,29,41,48,17,4,38,26,4,46,43,6,27,30,0,16,40,33,0,42, 41,10,33,47,11,37,49,25,36,20,47,12,28,17,11,17,26,26,37,34,27,17,8, 2,13,43,36,28,1,23,29,40,18,22,0,7,30,23,3,39,5,23,28,38,44,19,43,15, 16,43,5,27,24,25,7,16,38,33,33,1,9,25,47,0,31,30,29,4,36,49,26,6,39, 40,28,39,48,26,2,15,41,42,32,0,35,34,28,30,40,3,33,16,15,41,45,12,33, 35,16,47,34,23};
			int to[]                  = {41,42,17,0,2,7,28,32,31,33,6,42,11,13,7,40,47,21,4,6,19,15,4,18,30,25, 2,10,30,34,1,47,35,23,3,0,9,25,42,21,4,6,47,32,5,40,5,0,8,49,16,29,8, 11,42,33,35,26,27,43,35,6,14,13,44,25,13,42,2,26,17,3,40,31,18,12,24, 37,0,37,15,44,35,40,10,1,35,47,36,33,2,39,23,28,32,0,6,21,33,41,0,19, 16,29,35,16,44,6,18,17,2,46,41,11,27,5,44,1,48,15,43,8,41,33,16,11,45, 47,19,41,14,41,8,24,13,3,44,41,42,30,31,44,21,14,43,48,0,6,25,38,36,14, 36,22,43,15,20,19,37,25,17,44,17,46,8,25,33,19,42,40,42,24,15,31,34,8, 41,25,20,29,2,5,43,28,33,40,31,27,6,21,9,35,8,8,26,13,11,31,4,4,30,34, 35,1,15,11,10,24,15,24,23,16,24,32,9,1,6,17,48,6,35,19,12,5,21,23,25,9, 17,47,19,23,22,35,19,5,1,10,9,41,11,45,0,23,0,11,39,0,17,2,18,4,17,24,0, 10,19,4,36,22,42,18,13,48,27,11,19,28,31,39,32,48,2,26,38,43,38,49,34, 37,11,9,11,14,12,9,37,0,22,14,15,0,8,23,7,43,5,8,16,47};
			int cost[]                = {494,848305,3326,6008,223,2,6,673,152335,25,713909,42842,122,9941,361853, 35,20157,1098,41,83693,365851,43843,622,591230,7722,2489,7,861622,21272, 169,1153,3,7,3,577031,24522,5,241,757900,11036,8892,199,7,2,1,453031,115, 13,125,67,35,91,33427,14,106,203749,5,1804,4543,23,1,281,441212,18,3, 11629,233,388188,10,701,76170,763,875,11606,44972,6449,37409,83516,5912, 6,705899,26759,253,580531,14215,21916,884775,30,678,5940,17,480830,8, 61,218613,683352,4,557589,2619,3658,221515,15825,163577,25,9,1,4,13,2,88, 147,110163,18118,2,15429,211872,24,1,188382,12500,2348,190,4279,40,8428, 56325,933152,231523,9454,21,4855,96168,1722,329515,77,1,3,3518,10926, 12172,4,71,181976,1318,9,5086,905,108490,80164,2,10236,197,1880,17420, 614650,372457,13918,36,17,167,6,254127,512,15,341436,1,186,96,7,3,42,4, 3,4,492598,18523,172302,1,421535,390382,2952,6228,871,505372,131266,5, 743902,11,34,657,4717,3196,259,192504,229,6786,28,44364,21123,8,166781, 885021,2,828,497,376,24707,52,1,1659,19402,27261,82,473,443,1089,586,20, 7,239277,27132,4681,761,10644,17798,1,820306,13330,19,293167,2,4,89279, 14,1,9,18023,1165,495221,32304,538,178613,1,4764,32767,114,103,1,302,428, 92,927352,22270,2646,3599,6,16362,3,4,280286,338,652,2,347022,23,323084, 3338,46,58,1263,93,46992,19112,1,19499,33,807600,20296,16803,911294,3151, 1,793,1,1,504,62209,1397,52726,3650,54,3630,358480,178,394,28,137436,52764, 1209,1599};
			long long expected__      = 121213509;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 20;
			int K                     = 1000;
			int from[]                = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,18};
			int to[]                  = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,0};
			int cost[]                = {1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000, 1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000, 1000000};
			long long expected__      = 19019000000LL;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 2;
			int K                     = 0;
			int from[]                = {0,1};
			int to[]                  = {0,1};
			int cost[]                = {5,4};
			long long expected__      = -1;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int K                     = ;
			int from[]                = ;
			int to[]                  = ;
			int cost[]                = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int K                     = ;
			int from[]                = ;
			int to[]                  = ;
			int cost[]                = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int K                     = ;
			int from[]                = ;
			int to[]                  = ;
			int cost[]                = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MaliciousPath().minPath(N, K, vector <int>(from, from + (sizeof from / sizeof from[0])), vector <int>(to, to + (sizeof to / sizeof to[0])), vector <int>(cost, cost + (sizeof cost / sizeof cost[0])));
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
