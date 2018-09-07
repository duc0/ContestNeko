#include "global.hpp"
#include "Scanner.hpp"
#include "Collections.hpp"

class TaskA {
public:
    void solve(std::istream &inStream, std::ostream &outStream) {
        Scanner in(inStream);
        Writer out(outStream);

        int n = in.nextInt();
        int k = in.nextInt();

        string s = in.nextString();

        cl::Array<int> cnt(k);
        for (char c : s) {
            cnt[c - 'A']++;
        }
        int minVal = INT_INF;
        FOR_INC(i, k) {
            minVal = min(minVal, cnt[i]);
        }
        out.write(minVal * k);
    }
};
