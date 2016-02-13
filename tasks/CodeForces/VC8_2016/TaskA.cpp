#include "global.hpp"
#include "Scanner.hpp"

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        string s;
        int n;
        inStream >> n;
        inStream >> s;

        int cnt = 0;

        for_inc_range(lh, 0, n - 1) {
            int dr = 0, dc = 0;
            for_inc_range(rh, lh, n - 1) {
                switch (s[rh]) {
                    case 'U':
                        dr++;
                        break;
                    case 'D':
                        dr--;
                        break;
                    case 'R':
                        dc++;
                        break;
                    case 'L':
                        dc--;
                        break;
                }
                if (dr == 0 && dc == 0) {
                    cnt++;
                }

            }
        }

        outStream << cnt << endl;
    }
};
