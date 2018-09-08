#include "global.hpp"
#include "Scanner.hpp"
#include "NDArray.hpp"
#include "ArrayUtils.hpp"

using AL = cl::NDArray<int64>;
using AI = cl::NDArray<int>;

class TaskD {
    int64 getSum(const AL& sum, int l, int r) {
        return sum[r] - sum[l - 1];
    }

    int getResult(const AL& sum1, const AL& sum2, int pos1, int pos2) {
        if (pos1 == 0 && pos2 == 0) {
            return 0;
        } else if (pos1 == 0 || pos2 == 0) {
            return -1;
        } else if (sum1[pos1] != sum2[pos2]) {
            return -1;
        }

        int left2 = pos2;
        for (int left1 = pos1; left1 >= 1; left1--) {
            int64 part1 = getSum(sum1, left1, pos1);

            while (left2 >= 1) {
                int64 part2 = getSum(sum2, left2, pos2);
                if (part2 == part1) {
                    //cout << part1 << " " << part2 << endl;
                    int recResult = getResult(sum1, sum2, left1 - 1, left2 - 1);
                    if (recResult == -1) {
                        return -1;
                    }
                    return recResult + 1;
                }
                if (part2 < part1 && left2 > 1 && getSum(sum2, left2 - 1, pos2) <= part1) {
                    left2--;
                } else {
                    break;
                }
            }
        }
    }

public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        auto len1 = in.next<int>();
        auto array1 = in.nextArray<int64>(len1, 1);

        auto len2 = in.next<int>();
        auto array2 = in.nextArray<int64>(len2, 1);

        auto sum1 = utils::getSumArray(array1);
        auto sum2 = utils::getSumArray(array2);

        out.write(getResult(sum1, sum2, len1, len2));
    }
};
