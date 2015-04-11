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

template<class T> class Matrix {
  vector<vector<T>> a;
  int nRow, nCol;
  
public:
  void init(int nRow, int nCol) {
    this->nRow = nRow;
    this->nCol = nCol;
    a.resize(nRow);
    for_inc(r, nRow) {
      a[r].resize(nCol);
      for_inc(c, nCol) {
        a[r][c] = 0;
      }
    }
  }
  
  void init(int nRow, int nCol, const vector<vector<T>> &val) {
    assert(val.size() == nRow);
    assert(val[0].size() == nCol);
    init(nRow, nCol);
    for_inc(r, nRow) {
      for_inc(c, nCol) {
        a[r][c] = val[r][c];
      }
    }
  }
  
  void init(const vector<vector<T>> &val) {
    init((int)val.size(), (int)val[0].size(), val);
  }
  
  Matrix& operator=(const vector<vector<T>> &val) {
    init(val);
    return *this;
  }
  
  Matrix operator + (const Matrix &o) const {
    assert(nRow == o.nRow);
    assert(nCol == o.nCol);
    Matrix ret;
    ret.init(nRow, nCol);
    for_inc(r, nRow) for_inc(c, nCol) ret.a[r][c] = a[r][c] + o.a[r][c];
    return ret;
  }
  
  Matrix operator * (const Matrix &o) const {
    assert(nCol == o.nRow);
    Matrix ret;
    ret.init(nRow, o.nCol);
    for_inc(r, nRow) for_inc(c2, nCol) if (a[r][c2] != 0) for_inc(c, o.nCol) {
      ret.a[r][c] += a[r][c2] * o.a[c2][c];
    }
    return ret;
  }
  
  Matrix power(int k) const {
    assert(k >= 0);
    assert(nRow == nCol);
    if (k == 0) {
      Matrix ret;
      ret.init(nRow, nRow);
      for_inc(r, nRow) ret.a[r][r] = 1;
      return ret;
    } else if (k % 2 == 0) {
      Matrix tmp = power(k / 2);
      return tmp * tmp;
    } else {
      Matrix tmp = power(k - 1);
      return *this * tmp;
    }
  }
  
  vector<T>& operator[](int r) {
    return a[r];
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const Matrix& matrix) {
    stream << "[matrix: row = " << matrix.nRow << ", col = " << matrix.nCol << endl;
    for_inc(r, matrix.nRow) {
      for_inc(c, matrix.nCol) {
        stream << matrix.a[r][c] << " ";
      }
      stream << endl;
    }
    stream << "]" << endl;
    return stream;
  }
};

template <class T> class NumberTheory {
  static void extendedEuclid(T a, T b, T &x, T &y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return;
    }
    T x2;
    extendedEuclid(b, a % b, x2, x);
    y = x2 - (a / b) * x;
  }
  
public:
  static inline T modulo(int64 a, T b) {
    T r = a % b;
    if (r < 0)
      r += b;
    return r;
  }
  static inline T modularInverse(T a, T m) {
    T x, y;
    extendedEuclid(a, m, x, y);
    return modulo(x, m);
  }
};

template <class T, T M> class ModInt {
  T x = 0;
  static inline T get(ModInt x) { return x.get(); }
  static inline T get(T x) { return x; }
  
public:
  ModInt() : ModInt(0) {}
  ModInt(int64 y) { x = NumberTheory<T>::modulo(y, M); }
  T get() const { return x; }
  template <class Q> ModInt operator+(const Q &y) const {
    return ModInt(x + get(y));
  }
  template <class Q> ModInt& operator+=(const Q &y) {
    x = NumberTheory<T>::modulo(x + get(y), M);
    return *this;
  }
  template <class Q> ModInt operator-(const Q &y) const {
    return ModInt(x - get(y));
  }
  template <class Q> bool operator!=(const Q &y) const {
    return x != get(y);
  }
  template <class Q> ModInt operator*(const Q &y) const {
    return ModInt((int64)x * get(y));
  }
  template <class Q> ModInt operator/(const Q &y) const {
    return ModInt(
                  (int64)x * NumberTheory<T>::modularInverse(get(y), MOD));
  }
  ModInt &operator=(const T &y) {
    x = NumberTheory<T>::modulo(y, M);
    return *this;
  }
  ModInt &operator=(const ModInt &y) {
    x = y.x;
    return *this;
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const ModInt& y) {
    stream << get(y);
    return stream;
  }
  
};

class Autogame {
public:
  int wayscnt( vector <int> graph, int k ) {
    Matrix<ModInt<int, MOD>> a;
    int n = (int) graph.size();
    a.init(n, n);
    for_inc(i, n) {
      a[i][graph[i] - 1] = 1;
    }
    //LOG(1, "Matrix: " << a);
    a = a.power(k);
    map<int, int> cnt;
    for_inc(i, n) {
      for_inc(j, n) {
        if (a[i][j].get()) {
          cnt[j]++;
          break;
        }
      }
    }
    int ans = 1;
    for (auto &entry : cnt) {
      ans = ((int64)ans * (entry.second + 1)) % MOD;
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
			int a[]                   = {1,2,3};
			int K                     = 5;
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {1,1,1};
			int K                     = 1;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {2,1} ;
			int K                     = 42;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {2,3,4,3};
			int K                     = 3;
			int expected__            = 9;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {4,4,3,2,1};
			int K                     = 3;
			int expected__            = 18;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int a[]                   = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int a[]                   = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int K                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Autogame().wayscnt(vector <int>(a, a + (sizeof a / sizeof a[0])), K);
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
