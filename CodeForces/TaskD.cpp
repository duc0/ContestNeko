#include "global.hpp"
#include "Scanner.hpp"
#include "Collections.hpp"

class TaskD {
    int64 getSum(const cl::Array<int64>&sum, int l, int r) {
        return sum[r] - sum[l - 1];
    }

    int getResult(const cl::Array<int64>& sum1, const cl::Array<int64>& sum2, int pos1, int pos2) {
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

        int len1 = in.nextInt();
        cl::Array1<int> array1(len1);
        FOR_INC_RANGE(i, 1, len1) {
            array1[i] = in.nextInt();
        }

        int len2 = in.nextInt();
        cl::Array1<int> array2(len2);
        FOR_INC_RANGE(i, 1, len2) {
            array2[i] = in.nextInt();
        }

        cl::Array<int64> sum1(len1 + 1);
        sum1[0] = 0;
        FOR_INC_RANGE(i, 1, len1) {
            sum1[i] = sum1[i - 1] + array1[i];
        }

        cl::Array<int64> sum2(len2 + 1);
        sum2[0] = 0;
        FOR_INC_RANGE(i, 1, len2) {
            sum2[i] = sum2[i - 1] + array2[i];
        }

        out.write(getResult(sum1, sum2, len1, len2));
    }
};
