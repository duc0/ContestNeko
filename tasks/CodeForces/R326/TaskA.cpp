#include "global.hpp"
#include "Scanner.hpp"


#define MAX 2000000

int a[MAX];

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n;
        in >> n;

        memset(a, 0, sizeof(a));
        FOR_INC(i, n) {
            int w;
            in >> w;
            a[w]++;
        }

        int cnt = 0;
        FOR_INC(i, MAX) {
            if (a[i] > 0) {
                a[i + 1] += a[i] / 2;
                a[i] %= 2;
                if (a[i] > 0) {
                    ++cnt;
                }
            }
        }
        out << cnt;
    }
};
