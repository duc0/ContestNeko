#include "global.hpp"
#include "Scanner.hpp"

class TaskB {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int len;
        in >> len;

        int halfLen = len / 2;

        int median;
        in >> median;

        vector<int> smaller, larger;
        REPEAT(len) {
            int x;
            in >> x;
            if (x < median) {
                smaller.emplace_back(x);
            } else if (x > median) {
                larger.emplace_back(x);
            }
        }

        int nSmall = smaller.size();
        int nLarge = larger.size();

        int64 result = 0;
        if (nSmall > halfLen) {
            sort(smaller.begin(), smaller.end());
            for (int need = 1; need <= (nSmall - halfLen); need++) {
                result += (median - smaller[nSmall - need]);
            }

        } else if (nLarge > halfLen) {
            sort(larger.begin(), larger.end());
            for (int need = 1; need <= (nLarge - halfLen); need++) {
                result += (larger[need - 1] - median);
            }
        }

        out << result;
    }
};
