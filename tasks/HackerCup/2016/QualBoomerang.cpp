#include "global.hpp"
#include "Scanner.hpp"

class QualBoomerang {
public:
    int testNumber = 0;
    void solve(std::istream& inStream, std::ostream& outStream) {
        testNumber++;
        Scanner in(inStream);
        Writer out(outStream);
        int n;
        in >> n;
        vector<pair<int, int>> points;
        repeat(n) {
            int x, y;
            in >> x >> y;
            points.push_back(make_pair(x, y));
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            auto &p = points[i];
            vector<int> dst;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    auto &p2 = points[j];
                    dst.push_back((p2.second - p.second) * (p2.second - p.second) + (p2.first - p.first) * (p2.first - p.first));
                }
            }
            sort(dst.begin(), dst.end());
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (j == (n - 1) || (dst[j] != dst[j - 1])) {
                    ans = ans + (cnt * (cnt - 1) / 2);
                    cnt = 0;
                }
                cnt++;

            }
        }

        out << "Case #" << testNumber << ": " << ans;
        out.newline();
    }
};
