#include "global.hpp"
#include "Matrix.hpp"
#define NO_WAY -1E9L

class TaskB {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n, nRepeat;
        in >> n >> nRepeat;
        vector<int> a ( n + 1);
        int maxVal = 0;

        for_inc_range(i, 1, n) {
            in >> a[i];
            maxVal = max(maxVal, a[i]);
        }

        Matrix<int> base;
        base.init(maxVal, maxVal);

        for_inc_range(lower, 1, maxVal) {
            for_inc_range(upper, 1, maxVal) {
                if (lower > upper) {
                    base[lower - 1][upper - 1] = NO_WAY;
                } else {
                    base[lower - 1][upper - 1] = 0;
                }
            }
        }

        for_inc_range(lower, 1, maxVal) {
            vector<int> longestEnd(n + 1);

            for_inc_range(i, 1, n) if (a[i] >= lower) {
                longestEnd[i] = 1;
                for_inc_range(j, 1, i - 1) {
                    if (a[j] >= lower && a[j] <= a[i]) {
                        longestEnd[i] = max(longestEnd[i], longestEnd[j] + 1);
                    }
                }
            }

            for_inc_range(i, 1, n) if (a[i] >= lower) {
                for_inc_range(upper, a[i], maxVal) {
                    base[lower - 1][upper - 1] = max(base[lower - 1][upper - 1], longestEnd[i]);
                }
            }

        }

        base = base.power(nRepeat);

        int best = 0;
        for_inc_range(lower, 1, maxVal) {
            for_inc_range(upper, 1, maxVal) {
                best = max(best, base[lower - 1][upper - 1]);
            }
        }

        out << best << endl;
    }
};
