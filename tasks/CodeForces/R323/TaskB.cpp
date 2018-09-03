#include "global.hpp"
#include "Matrix.hpp"
#include "Collections.hpp"

class MyCalc {
public:
    static inline int zero() {
        return -1E9L;
    }

    static inline int plus(const int &a, const int &b) {
        return max(a, b);
    }
    static inline int multiply(const int &a, const int &b) {
        return a + b;
    }
};

class TaskB {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n, nRepeat;
        in >> n >> nRepeat;
        cl::Array1<int> a(n);
        int maxVal = 0;

        FOR_INC_RANGE(i, 1, n) {
            in >> a[i];
            maxVal = max(maxVal, a[i]);
        }

        UpperTriMatrix<int, MyCalc> base;
        base.init(maxVal);

        FOR_INC_RANGE(lower, 1, maxVal)
            FOR_INC_RANGE(upper, lower, maxVal) {
                base[lower][upper] = 0;
            }

        FOR_INC_RANGE(lower, 1, maxVal) {
            cl::Array1<int> longestEnd(n);

            FOR_INC_RANGE(i, 1, n) if (a[i] >= lower) {
                longestEnd[i] = 1;
                FOR_INC_RANGE(j, 1, i - 1) {
                    if (a[j] >= lower && a[j] <= a[i]) {
                        longestEnd[i] = max(longestEnd[i], longestEnd[j] + 1);
                    }
                }
            }

            FOR_INC_RANGE(i, 1, n) if (a[i] >= lower) {
                FOR_INC_RANGE(upper, a[i], maxVal) {
                    base[lower][upper] = MyCalc::plus(base[lower][upper], longestEnd[i]);
                }
            }
        }

        base = base.power(nRepeat);

        int best = 0;
        FOR_INC_RANGE(lower, 1, maxVal) {
            FOR_INC_RANGE(upper, lower, maxVal) {
                best = MyCalc::plus(best, base[lower][upper]);
            }
        }

        out << best << endl;
    }
};
