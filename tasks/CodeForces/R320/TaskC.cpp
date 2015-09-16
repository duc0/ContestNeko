#include "global.hpp"
#include "BinarySearch.hpp"

#define MAXN 200200

int n;
int a[MAXN];
pair<int, int> p[MAXN];

#define INF 1E18
bool ok(double ret) {
    double bMin = INF, bMax = -INF;
    LOG(1, "Ret " << ret);
    for_inc_range(i, 0, n - 1) {
        pair<int, int> p1 = p[i];
        pair<int, int> p2 = p[i + 1];
        if (p1.second < p2.second) {
            swap(p1, p2);
        }
        double l = p1.second - p2.second;
        double slope = (p2.first - p1.first) / l;
        bMin = min(bMin, slope + ret / l);
        bMax = max(bMax, slope - ret / l);
        LOG(1, "Slope " << i << " " << slope);
    }
    LOG(1, "Bmax " << bMax << " bMin " << bMin);
    return bMax <= bMin;
}

class TaskC {
public:
    void solve(std::istream& in, std::ostream& out) {
        in >> n;
        for_inc_range(i, 1, n) {
            in >> a[i];
        }
        a[0] = 0;
        p[0] = make_pair(0, 0);
        for_inc_range(i, 1, n) {
            a[i] = a[i - 1] + a[i];
            p[i] = make_pair(a[i], i);
        }
        sort(p, p + n + 1);

        double ret;
        binarySearchMinReal(0, 3e4, 1e-7, (function<bool(double)>) ok, ret);

        out << setiosflags(ios::fixed) << std::setprecision(12) << ret << endl;
    }
};
