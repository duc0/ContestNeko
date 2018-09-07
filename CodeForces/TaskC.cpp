#include "global.hpp"
#include "Scanner.hpp"

#define MAXL 30
#define MAXD 5

class TaskC {
    int64 f[MAXL + 1][MAXD + 1];

    int64 solve(int n, int k) {
        if (k > 3) {
            return 0;
        } else if (n == 0) {
            return 1;
        }
        if (f[n][k] != -1) {
            return f[n][k];
        }
        f[n][k] = (k + 1) * solve(n - 1, k) + (9 - k) * (solve(n - 1, k + 1));
        //cout << "Solve " << n << " " << k << " " << f[n][k] << endl;
        return f[n][k];
    }

    int64 solve(string num, int pos, map<int, int>& used, int countUsed) {
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
            used[digit] ++;

            if (digit != 0 && used[digit] == 1) {
                countUsed++;
            }

            if (countUsed <= 3) {
                int64 rest = solve( len - (pos + 1), countUsed); 
                result += rest;
                //cout << "To solve " << (len - (pos + 1)) << " " << countUsed << " " << rest << endl;
            }

            used[digit] --;
            if (digit != 0 && used[digit] == 0) {
                countUsed--;
            }
        }
        used[curDigit]++;
        if (curDigit != 0 && used[curDigit] == 1) {
            countUsed++;
        }
        result += solve(num, pos + 1, used, countUsed);
        return result;
    }

    int64 solve(int64 upper) {
        if (upper == 0) {
            return 0;
        }
        stringstream ss;
        ss << upper;
        string num = ss.str();
        map<int, int> used;
        return solve(num, 0, used, 0) - 1;
    }

public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        FOR_INC_RANGE(n, 0, MAXL) {
            FOR_INC_RANGE(k, 0, MAXD) {
                f[n][k] = -1;
            }
        }

        Scanner in(inStream);
        Writer out(outStream);

        //cout << "MEO " << solve(3, 0) << endl;
        //cout << "MEO " << solve(2, 1) << endl;
        int cases = in.nextInt();
        while (cases--) {
            int64 l = in.nextLong();
            int64 r = in.nextLong();
            cout << "Res " << r << " " << solve(r) << endl;
            cout << "Res " << l-1 << " " << solve(l-1) << endl;
            out.write(solve(r) - solve(l - 1));
            out.newLine();
        }
    }
};
