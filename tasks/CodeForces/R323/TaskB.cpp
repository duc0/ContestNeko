#include "global.hpp"
#include "Matrix.hpp"
#include "Collections.hpp"

#define ZERO -1E9L

struct Num {
    int x;

    Num() : x(0) {}
    Num(int x) : x(x) {}

    Num operator + (const Num &other) const {
        return max(x, other.x);
    }

    Num operator * (const Num &other) const {
        if (x == ZERO || other.x == ZERO) {
            return ZERO;
        }
        return x + other.x;
    }

    bool operator!=(const Num &other) const {
        return x != other.x;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Num &val) {
        stream << val.x;
        return stream;
    }

};

template <> Num zero() {
    return ZERO;
}

class TaskB {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n, nRepeat;
        in >> n >> nRepeat;
        cl::Array1<int> a(n);
        int maxVal = 0;

        for_inc_range(i, 1, n) {
            in >> a[i];
            maxVal = max(maxVal, a[i]);
        }

        UpperTriMatrix<Num> base;
        base.init(maxVal);

        for_inc_range(lower, 1, maxVal)
            for_inc_range(upper, lower, maxVal) {
                base[lower][upper] = 0;
            }

        for_inc_range(lower, 1, maxVal) {
            cl::Array1<int> longestEnd(n);

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
                    base[lower][upper] = base[lower][upper] + longestEnd[i];
                }
            }
        }

        base = base.power(nRepeat);

        Num best = 0;
        for_inc_range(lower, 1, maxVal) {
            for_inc_range(upper, lower, maxVal) {
                best = best + base[lower][upper];
            }
        }

        out << best.x << endl;
    }
};
