#include "global.hpp"
#include "Scanner.hpp"

class TaskA {
public:
    void solve(std::istream& inStream, std::ostream& outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int64 n = in.nextLong();
        int64 k = in.nextLong();

        
        int64 result = k / n;
        if (k % n != 0) {
            result++;
        }
        out.write(result);        
    }
};
