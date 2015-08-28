#include "global.hpp"
#include "RangeUpdateArray.hpp"
#include "BinarySearch.hpp"

class IOI07Sails {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        vector<pair<int, int>> a;
        in >> n;
        int maxH = 0;
        repeat(n) {
            int h, k;
            in >> h >> k;
            a.push_back(make_pair(h, k));
            maxH = max(maxH, h);
        }

        sort(a.begin(), a.end());

        int curH = 0;
        RangeUpdateArray<int> s(0, maxH - 1);
        for (auto &p: a) {
            int h = p.first, k = p.second;
            curH = h;
            int i = curH - k;
            if (i == 0 || s[i] != s[i - 1]) {
                s.add(i, curH - 1, 1);
            } else {
                int x = s[i];
                int ret;
                if (binarySearchMin<int>(i, curH - 1, [&](int midIndex) { return s[midIndex] < x; }, ret)) {
                    s.add(ret, curH - 1, 1);
                    k -= (curH - ret);
                }
                if (binarySearchMin<int>(0, i, [&](int midIndex){return s[midIndex] == x;}, ret)) {
                    s.add(ret, ret + k - 1, 1);
                }
            }
        }

        int64 ret = 0;
        for (int i = 0; i < maxH; ++i) {
            int x = s[i];
            ret += (int64) x * (x - 1) / 2;
        }

        out << ret << endl;
    }
};
