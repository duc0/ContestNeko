// Paste me into the FileEdit configuration dialog

#include <string>
#include <vector>
using namespace std;

#define MAXN 1100
#define MAXH 12

vector<int> adj[MAXN];

int parent[MAXN];
bool visit[MAXN];

int n;

int f[4][MAXH][MAXN];

bool dfs(int depth, int u, int canIgnore) {
    auto &fv = f[canIgnore][depth][u];
    if (fv != -1) {
        return fv;
    }
    visit[u] = true;
    bool seenP = false;
    vector<int> child;
    for (auto &v: adj[u]) {
        bool shouldIgnore = false;
        if (v == u) {
            shouldIgnore = true;
        } else if (parent[u] != v) {
            child.push_back(v);
            if (visit[v]) {
                //shouldIgnore = true;
            }
        } else {
            if (seenP) {
                shouldIgnore = true;
            }
            seenP = true;
        }
        if (shouldIgnore) {
            if (canIgnore > 0) {
                canIgnore--;
            } else {
                return fv = false;
            }
        }
    }
    
    if (depth == 0) {
        return fv = (canIgnore >= child.size());
    }
    
    if (canIgnore < child.size() - 2) {
        return fv = false;
    }
    
    canIgnore -= child.size() - 2;
    for (int i = 0; i < child.size(); ++i) {
        for (int j = i + 1; j < child.size(); ++j) {
            int cl = child[i], cr = child[j];
            parent[cl] = u; parent[cr] = u;
            for (int ig = 0; ig <= canIgnore; ++ig) {
                bool dl = dfs(depth - 1, cl, ig);
                if (dl) {
                    bool dr= dfs(depth - 1, cr, canIgnore - ig);
                    if (dr) {
                        return fv = true;
                    }
                }
            }
            parent[cl] = -1; parent[cr] = -1;
        }
    }
    
    return fv = false;
}

class TheKingsRoadsDiv1 {
public:
   string getAnswer( int h, vector <int> a, vector <int> b ) {
       for (int i = 0; i < (int)a.size(); ++i) {
           adj[a[i]].push_back(b[i]);
           adj[b[i]].push_back(a[i]);
       }
       
       n = (1 << h) - 1;
       for (int root = 1; root <= n; ++root) {
           parent[root] = -1;
           memset(f, -1, sizeof(f));
           memset(visit, 0, sizeof(visit));
           if (dfs(h, root, 3)) {
               return "Correct";
           }
       }
       
       return "Incorrect";
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
	
	int verify_case(int casenum, const string &expected, const string &received, std::clock_t elapsed) { 
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
			std::cerr << "    Expected: \"" << expected << "\"" << std::endl; 
			std::cerr << "    Received: \"" << received << "\"" << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int h                     = 3;
			int a[]                   = {1, 3, 2, 2, 3, 7, 1, 5, 4};
			int b[]                   = {6, 5, 4, 7, 4, 3, 3, 1, 7};
			string expected__         = "Correct";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int h                     = 2;
			int a[]                   = {1, 2, 1, 3, 3};
			int b[]                   = {2, 1, 2, 3, 3};
			string expected__         = "Incorrect";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int h                     = 3;
			int a[]                   = {1, 3, 2, 2, 6, 6, 4, 4, 7};
			int b[]                   = {2, 1, 4, 5, 4, 4, 7, 7, 6};
			string expected__         = "Incorrect";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int h                     = 2;
			int a[]                   = {1, 2, 2, 1, 1};
			int b[]                   = {1, 2, 2, 1, 2};
			string expected__         = "Incorrect";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int h                     = 5;
			int a[]                   = {6, 15, 29, 28, 7, 13, 13, 23, 28, 13, 30, 27, 14, 4, 14, 19, 27, 20, 20, 19, 10, 15, 7, 7, 19, 29, 4, 24, 10, 23, 30, 6, 24};
			int b[]                   = {9, 22, 30, 20, 26, 25, 8, 7, 24, 21, 27, 31, 4, 28, 29, 6, 16, 1, 17, 10, 3, 12, 30, 18, 14, 23, 19, 21, 5, 13, 15, 2, 11};
			string expected__         = "Correct";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int h                     = 2;
			int a[]                   = {1,1,1,2,1};
			int b[]                   = {2,3,1,2,2};
			string expected__         = "Correct";

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int h                     = ;
			int a[]                   = ;
			int b[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int h                     = ;
			int a[]                   = ;
			int b[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int h                     = ;
			int a[]                   = ;
			int b[]                   = ;
			string expected__         = ;

			std::clock_t start__      = std::clock();
			string received__         = TheKingsRoadsDiv1().getAnswer(h, vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])));
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
