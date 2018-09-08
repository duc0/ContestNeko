#include "global.hpp"
#include "Scanner.hpp"
#include "NDArray.hpp"

auto f = cl::NDArray<int64>({30, 5}, -1);

class TaskC {
    int64 solve(int n, int k) {
        if (k > 3) {
            return 0;
        } else if (n == 0) {
            return 1;
        }
        if (f(n, k) != -1) {
            return f(n, k);
        }
        f(n, k) = solve(n - 1, k) + 9 * solve(n - 1, k + 1);
        //cout << "Solve " << n << " " << k << " " << f[n][k] << endl;
        return f(n, k);
    }

    int64 solve(string num, int pos, int countUsed) {
        //cout << "Solve " << num << " " << pos << endl;
        if (countUsed > 3) {
            return 0;
        }
        int len = num.length();
        if (pos == len) {
            return 1;
        }

        int curDigit = num[pos] - '0';
        int64 result = 0;
        for (int digit = 0; digit < curDigit; digit++) {
            if (digit != 0) {
                countUsed++;
            }

            if (countUsed <= 3) {
                int64 rest = solve( len - (pos + 1), countUsed);
                result += rest;
                //cout << "To solve " << (len - (pos + 1)) << " " << countUsed << " " << rest << endl;
            }

            if (digit != 0) {
                countUsed--;
            }
        }
        if (curDigit != 0) {
            countUsed++;
        }
        result += solve(num, pos + 1, countUsed);
        return result;
    }

    int64 solve(int64 upper) {
        if (upper == 0) {
            return 0;
        }
        stringstream ss;
        ss << upper;
        string num = ss.str();
        return solve(num, 0, 0) - 1;
    }
    
    bool good(int n) {
        int countDigit = 0;
        while (n > 0) {
            int d = n % 10;
            if (d > 0) {
                countDigit++;
            }
            n /= 10;
        }
        return countDigit <= 3; 
    }
    
    int solveNaive(int l, int r) {
        int count = 0;
        FOR_INC_RANGE(k, l, r) {
            if (good(k)) {
                count++;
            }
        }
        return count;
    }

public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        //cout << "MEO " << solve(3, 0) << endl;
        //cout << "MEO " << solve(2, 1) << endl;
        int cases = in.nextInt();
        while (cases--) {
            int64 l = in.nextLong();
            int64 r = in.nextLong();
            //cout << "Res " << r << " " << solve(r) << endl;
            //cout << "Res " << l-1 << " " << solve(l-1) << endl;
            //cout << "My " << solveNaive(l, r) << endl;
            out.write(solve(r) - solve(l - 1));
            out.newLine();
        }
    }
};
