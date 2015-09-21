#include "global.hpp"
#include "Iterator.hpp"
#include "Sequence.hpp"
#include "BinarySearch.hpp"

int n;
vector<double> a;

function<double(double)> addFunction(double x) {
    return [x](double v) {
        return v + x;
    };
}

double increasing(double x) {
    double result;
    maximumSumContiguousSubsequence(mapIterable(stdIterable<double>(a.begin(), a.end()), addFunction(x)), result);
    return result;
}

double decreasing(double x) {
    double result;
    minimumSumContiguousSubsequence(mapIterable(stdIterable<double>(a.begin(), a.end()), addFunction(x)), result);
    return -result;
}

class TaskC {
public:
    void solve(std::istream& in, std::ostream& out) {
        in >> n;
        a.resize(n);
        for_inc(i, n) {
            in >> a[i];
        }
        double ret;
        binarySearchIntersection(-3e4, 3e4, 1e-7, increasing, decreasing, ret);
        out << setiosflags(ios::fixed) << std::setprecision(12) << min(increasing(ret), decreasing(ret)) << endl;
    }
};
