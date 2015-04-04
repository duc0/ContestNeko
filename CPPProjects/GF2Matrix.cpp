//#define SUBMIT

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#define LOGLEVEL 1
#endif

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
#include <bitset>

using namespace std;

#define LOG(l, x) if (l <= LOGLEVEL) cout << "[LOG " << LOGLEVEL << "] " << x << endl

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
int MODP(int64 x) {
  int r = x % MOD;
  if (r < 0) r += MOD;
  return r;
}

class AbstractGF2MatrixRecorder
{
public:
  // record row[r1] = row[r1] ^ row[r2]
  virtual void record(int r1, int r2) {}
  
  // record swap(row[r1], row[r2])
  virtual void recordSwap(int r1, int r2) {}
};

class GF2MatrixRecorder : public AbstractGF2MatrixRecorder
{
  vector<pair<int, int>> op;
public:
  void record(int r1, int r2) {
    op.emplace_back(r1, r2);
  }
  
  void recordSwap(int r1, int r2) {
    if (r1 == r2) return;
    op.emplace_back(r1, r2);
    op.emplace_back(r2, r1);
    op.emplace_back(r1, r2);
  }
  
  const vector<pair<int, int>>& getOperations() {
    return op;
  }
};



// 0-based
// Note that columns are numbered from (NCOL - 1) to 0, left ro right
template<int NCOL> class GF2Matrix {
  vector<bitset<NCOL>> row;
  int nRow;
  vector<int> order;
  vector<size_t> length;
  bool isLock;
  int rank;
  bool gaussianEliminationCalled;
  vector<int> first1;
  AbstractGF2MatrixRecorder noRecorder;
  AbstractGF2MatrixRecorder &recorder;
  
public:
  GF2Matrix(int nRow): recorder(noRecorder) {
    init(nRow);
  }
  
  GF2Matrix(int nRow, AbstractGF2MatrixRecorder &recorder): recorder(recorder) {
    init(nRow);
  }
  
  int numRow() const {
    return nRow;
  }
  
  int numCol() const {
    return NCOL;
  }
  
  void init(int nRow) {
    this->nRow = nRow;
    row.resize(nRow);
    order.resize(nRow);
    for_inc(r, nRow) {
      order[r] = r;
    }
    length.resize(nRow);
    isLock = false;
    gaussianEliminationCalled = false;
  }
  
  void setRow(int r, const bitset<NCOL> &rV) {
    row[r] = rV;
  }
  
  void lock() {
    isLock = true;
    for_inc(r, nRow) {
      for_dec(c, NCOL) {
        if (row[r].test(c)) {
          length[r] = c;
          break;
        }
      }
    }
  }
  
  // O(NROW * NCOL)
  void gaussianElimination() {
    assert(isLock);
    first1.resize(nRow);
    rank = 0;
    for (int c = NCOL - 1, r = 0; c >=0; c--) {
      int i = r;
      while (i < nRow && !getRow(i).test(c)) {
        ++i;
      }
      if (i >= nRow) {
        continue;
      }
      first1[r] = c;
      swap(order[r], order[i]);
      recorder.recordSwap(r, i);
      for_inc(j, nRow){
        if (j != r && getRow(j).test(c)) {
          recorder.record(j, r);
          row[order[j]] ^= getRow(r);
        }
      }
      r++;
      rank++;
    }
    gaussianEliminationCalled = true;
  }
  
  // Return the first 1 on the row (after gaussian elimination).
  int getFirst1(int row) const {
    assert(gaussianEliminationCalled);
    assert(row < rank);
    return first1[row];
  }
  
  // Transform to another matrix in row echelon form
  void transform(const GF2Matrix<NCOL> &t) {
    assert(t.isGaussianEliminationCalled());
    for_inc(r, rank) {
      int c = getFirst1(r);
      for_inc(r2, rank) {
        if (getRow(r2).test(c) != t.getRow(r2).test(c)) {
          row[order[r2]] ^= getRow(r);
          recorder.record(r2, r);
        }
      }
    }
  }
  
  bool isGaussianEliminationCalled() const {
    return gaussianEliminationCalled;
  }
  
  int getRank() const {
    assert(gaussianEliminationCalled);
    return rank;
  }
  
  inline const bitset<NCOL> & getRow(int r) const {
    return row[order[r]];
  }
  
  bool operator ==(const GF2Matrix<NCOL> &y) const {
    if (y.numRow() != numRow()) return false;
    for_inc(r, nRow) {
      if (getRow(r) != y.getRow(r)) return false;
    }
    return true;
  }
  
  friend std::ostream& operator<< (std::ostream& stream, const GF2Matrix<NCOL>& matrix) {
    stream << "[matrix: row = " << matrix.nRow << ", col = " << NCOL << endl;
    for_inc(r, matrix.nRow) {
      for_dec(c, NCOL) {
        stream << matrix.getRow(r).test(c) << " ";
      }
      stream << endl;
    }
    stream << "]" << endl;
    return stream;
  }
  
};

void testGen() {
  freopen("biginput1.txt", "w", stdout);
  fclose(stdout);
}

void output(const GF2Matrix<32> &a) {
  ostringstream ss;
  for_inc(r, a.numRow()) {
    ss << a.getRow(r).to_ullong() << " ";
  }
  LOG(1, ss.str());
}

// CF 270 - F

int main() {
  ios::sync_with_stdio(false);
#ifndef SUBMIT
  freopen("input3.txt", "r", stdin);
#endif
  
  int n;
  cin >> n;
  
  vector<int> initial;
  GF2MatrixRecorder recordA, recordT;
  GF2Matrix<32> a(n, recordA);
  for_inc(r, n) {
    int x;
    cin >> x;
    initial.push_back(x);
    a.setRow(r, x);
  }
  a.lock();
  a.gaussianElimination();
  
  vector<int> target;
  repeat(n) {
    int x;
    cin >> x;
    target.push_back(x);
  }
  
  GF2Matrix<32> b(2 * n);
  for_inc(r, n) {
    b.setRow(r, a.getRow(r));
  }
  int r = n;
  for (int x: target) {
    b.setRow(r, x);
    r++;
  }
  
  b.lock();
  b.gaussianElimination();
  
  if (b.getRank() != a.getRank()) {
    cout << -1 << endl;
  } else {
    GF2Matrix<32> t(n, recordT);
    for_inc(r, n) {
      t.setRow(r, target[r]);
    }
    t.lock();
    t.gaussianElimination();
    
    a.transform(t);
    
    vector<pair<int, int>> ret;
    for (auto p: recordA.getOperations()) {
      ret.push_back(p);
    }
    
    for (auto it = recordT.getOperations().rbegin(); it != recordT.getOperations().rend(); ++it) {
      ret.push_back(*it);
    }
    
    cout << ret.size() << endl;
    for (auto p: ret) {
      cout << p.first + 1 << " " << p.second + 1 << " " << endl;
      initial[p.first] ^= initial[p.second];
    }
    
    // Just verify
    for_inc(i, n) {
      LOG(1, initial[i]);
    }
  }
  
  return 0;
}
