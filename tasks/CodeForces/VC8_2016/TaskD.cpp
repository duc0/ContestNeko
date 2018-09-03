#include "global.hpp"
#include "Scanner.hpp"

#define MAX 10100
int64 cnt[MAX];
int64 cntSum[MAX];

class TaskD {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        in >> n;

        vector<int> a;

        REPEAT(n) {
            int x;
            in >> x;
            a.push_back(x);
        }


        memset(cnt, 0, sizeof(cnt));
        int maxDiff = 0;
        FOR_INC_RANGE(i, 0, n - 1) {
            FOR_INC_RANGE(j, i + 1, n - 1) {
                int diff = abs(a[i] - a[j]);
                cnt[diff]++;
                maxDiff = max(maxDiff, diff);
            }
        }

        LOG(1, "Max diff " << maxDiff);
        memset(cntSum, 0, sizeof(cntSum));
        FOR_INC_RANGE(val1, 0, maxDiff) {
            FOR_INC_RANGE(val2, 0, maxDiff) {
                cntSum[val1 + val2] += cnt[val1] * cnt[val2];
                //if (cntSum[val1 + val2] > 0) {
                    //LOG(1, "Sum " << (val1 + val2) << " " << cntSum[val1 + val2]);
                //}
            }
        }

        int64 cntRes = 0;
        FOR_INC_RANGE(val3, 0, maxDiff) {
            if (cnt[val3] > 0) {
                //LOG(1, "Val3 " << val3 << " " << cnt[val3]);
                FOR_INC_RANGE(c, 0, val3 - 1) {
                    //LOG(1, "Val3 " << val3 << " " << cnt[val3] << " " << c << " " << cntSum[c]);
                    cntRes += cntSum[c] * cnt[val3];
                }
            }
        }

        int64 sz = n * (n - 1) / 2;
        //LOG(1, "Cnt " << cntRes);
        outStream << setprecision(9) << cntRes * 1.0 / (sz * sz *sz);
    }
};
