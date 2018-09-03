#include "global.hpp"
#include "Scanner.hpp"

class TaskC {
public:
    static const int MAX = 1000100;
    string s1, s2;
    int f[MAX];

    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);


        int len;
        in >> len;
        in >> s1;
        in >> s2;

        f[0] = 0;
        for (int i = 1; i <= len; i++) {
            char b1 = s1[i - 1];
            char b2 = s2[i - 1];
            if (b1 == b2) {
                f[i] = f[i - 1];
            } else {
                f[i] = 1 + f[i - 1];
                if (i > 1) {
                    if (s1[i - 2] == b2 && s2[i - 2] == b1) {
                        f[i] = min(f[i], 1 + f[i - 2]);
                    }
                }
            }
        }

        out << f[len];
    }
};
