#include "global.hpp"
#include "Collections.hpp"

class TaskA {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        collections::Map<int, int> cnt;

        repeat(n * n) {
            int x;
            in >> x;
            cnt[x]++;
        }

        collections::Array<int> ret;

        while (ret.size() < n) {
            while (cnt.lastValue() == 0) {
                cnt.removeLast();
            }
            int largest = cnt.lastKey();
            for (int x : ret) {
                int g = __gcd(x, largest);
                cnt[g] -= 2;
            }
            ret.add(largest);
            cnt[largest]--;
        }

        for (int x : ret) {
            out << x << " ";
        }
    }
};
