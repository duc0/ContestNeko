#include "global.hpp"
#include "Scanner.hpp"

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n, m, a;
        in >> n >> m >> a;
        int64 need1 = n / a;
        if (n % a != 0) {
            need1++;
        }
        int64 need2 = m / a;
        if (m % a != 0) {
            need2++;
        }
        int64 result = need1 * need2;
        out << result;
    }
};
