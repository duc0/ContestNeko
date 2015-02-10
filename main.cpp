#include <cstdio>
#include <algorithm>
#include <cstring>

//#define NDEBUG
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

using namespace std;

#define int64 long long
#define repeat(x) for(auto repeat_var=0;repeat_var<x;++repeat_var)
#define fill0(x) memset(x, 0, sizeof(x))
#define INT_INF 2E9L

#define ntype int
#define N_INF INT_INF

struct Network {
  struct Edge {int u, v; ntype f, c;};
  vector<Edge> edgeList;
  vector<vector<int> > adj;
  void addEdge(int u, int v, ntype c) {
    Edge e={u,v,0,c};
    adj[u].push_back((int)edgeList.size());
    adj[v].push_back((int)edgeList.size());
    edgeList.push_back(e);
  }
  int n(){return (int)adj.size();}
  void resetFlow() {
    for (auto &pe : edgeList) pe.f=0;
  }
  void init(int n) {
    edgeList.clear();
    adj.resize(n);
    for (auto &au : adj) au.clear();
  }
  Network(int n){init(n);}
};

class Dinic {
  Network &g;
  int s, t;
  vector<ntype> dist;
  vector<bool> block;
  bool computeDist() {
    queue<int> q;
    q.push(t);
    fill(dist.begin(),dist.end(),-1);
    dist[t]=0;
    while (!q.empty()) {
      int u=q.front();
      q.pop();
      for (auto pi : g.adj[u]) {
        Network::Edge &e=g.edgeList[pi];
#define CONSIDER(v) {if (dist[v]==-1) {dist[v]=dist[u]+1; q.push(v); if (v==s) return true;}}
        if (e.v==u && e.f<e.c) CONSIDER(e.u) else if (e.u==u && e.f>0) CONSIDER(e.v)
#undef CONSIDER
          }
    }
    return dist[s]!=-1;
  }
  ntype findAugmentingPath(int u, ntype delta) {
    if (u==t) return delta;
    ntype inc;
    for (auto pi : g.adj[u]){
      Network::Edge &e=g.edgeList[pi];
#define CONSIDER(v,i,d) {if (!block[v] && dist[u]==dist[v]+1 && (inc=findAugmentingPath(v,min(delta,d)))) {e.f+=i*inc; return inc;}}
      if (e.u==u && e.f<e.c) CONSIDER(e.v,1,e.c-e.f) else if (e.v==u && e.f>0) CONSIDER(e.u,-1,e.f)
#undef CONSIDER
        }
    block[u]=true;
    return 0;
  }
public:
  ntype totalFlow;
  Dinic(Network &g, int s, int t):g(g),s(s),t(t){
    g.resetFlow();
    totalFlow=0;
    dist.resize(g.n());
    block.resize(g.n());
  }
  ntype run () {
    while (computeDist()) {
		    fill(block.begin(), block.end(), false);
		    while (ntype inc = findAugmentingPath(s, N_INF)) totalFlow += inc;
    }
    return totalFlow;
  }
};

class DoubleTree {
  int n;
  vector<int> p1, p2;
  
  vector< vector<int >> next1, next2;
  vector<bool> visit;
  
  void dfs1(int u) {
    visit[u] = true;
    for (auto &v: next1[u]) {
      if (!visit[v]) {
        p1[v] = u;
        dfs1(v);
      }
    }
  }
  
  void dfs2(int u) {
    visit[u] = true;
    for (auto &v: next2[u]) {
      if (!visit[v]) {
        p2[v] = u;
        dfs2(v);
      }
    }
  }
  
  void makeRoot(int root) {
    fill(visit.begin(), visit.end(), false);
    dfs1(root);
    fill(visit.begin(), visit.end(), false);
    dfs2(root);
  }
  
public:
  int maximalScore( vector <int> a, vector <int> b, vector <int> c, vector <int> d, vector <int> score ) {
    n = (int) a.size() + 1;
    
    assert((int)a.size() == n-1);
    assert((int)b.size() == n-1);
    
    p1.resize(n);
    p2.resize(n);
    visit.resize(n);
    
    next1.resize(n);
    next2.resize(n);
    
    for (int i = 0; i < n - 1; ++i) {
      next1[a[i]].push_back(b[i]);
      next2[a[i]].push_back(b[i]);
    }
    
    int best = -INT_INF;
    int MVAL = 1001;
    for (int i = 0; i < n; ++i) {
      makeRoot(i);
      
      Network g(2 * n + 2);
      
      int s = 2 * n;
      int t = 2 * n + 1;
      for (int u = 0; u < n; ++u) {
        g.addEdge(s, u, 0 + MVAL);
        g.addEdge(u, t, score[u] + MVAL);
        if (u != i) {
          g.addEdge(u, p1[u], INT_INF);
          g.addEdge(u, p2[u], INT_INF);
        }
      }
      int maxFlow = Dinic(g, s, t).run();
      int ret = maxFlow  / n;
      if (ret > best) {
        best = ret;
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
			int a[]                   = {0,0,1};
			int b[]                   = {1,3,2};
			int c[]                   = {0,0,3};
			int d[]                   = {1,3,2};
			int score[]               = {1000,24,100,-200};
			int expected__            = 1024;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {0,0,1};
			int b[]                   = {1,3,2};
			int c[]                   = {0,0,3};
			int d[]                   = {1,3,2};
			int score[]               = {1000,24,100,200};
			int expected__            = 1324;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0,0,1};
			int b[]                   = {1,3,2};
			int c[]                   = {0,0,3};
			int d[]                   = {1,3,2};
			int score[]               = {-1000,-24,-100,-200};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0,0,1};
			int b[]                   = {1,3,2};
			int c[]                   = {0,0,3};
			int d[]                   = {1,3,2};
			int score[]               = {-1000,24,100,200};
			int expected__            = 200;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {0,0,1,1,2,2};
			int b[]                   = {1,2,3,4,5,6};
			int c[]                   = {0,0,1,1,2,2};
			int d[]                   = {1,2,3,4,5,6};
			int score[]               = {-3,2,2,-1,2,2,-1};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int a[]                   = {0,0,1,1,2,2};
			int b[]                   = {1,2,3,4,5,6};
			int c[]                   = {0,0,0,0,0,0};
			int d[]                   = {1,2,3,4,5,6};
			int score[]               = {-3,2,2,-1,2,2,-1};
			int expected__            = 5;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int d[]                   = ;
			int score[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int d[]                   = ;
			int score[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int a[]                   = ;
			int b[]                   = ;
			int c[]                   = ;
			int d[]                   = ;
			int score[]               = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = DoubleTree().maximalScore(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(c, c + (sizeof c / sizeof c[0])), vector <int>(d, d + (sizeof d / sizeof d[0])), vector <int>(score, score + (sizeof score / sizeof score[0])));
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
