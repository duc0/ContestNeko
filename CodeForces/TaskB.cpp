#include "global.hpp"
#include "Scanner.hpp"

class TaskB {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int nCases = in.nextInt();

        while (nCases --) {
            int64 n = in.nextLong();
            int64 m = in.nextLong();
            int64 k = in.nextLong();

            int64 needed = max(m, n);
            if (k < needed) {
                out.write(-1);
            } else {

            }

            out.newLine();
        }
    }
};
