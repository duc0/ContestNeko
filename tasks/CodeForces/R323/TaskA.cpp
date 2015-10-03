#include "global.hpp"

class TaskA {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;

        map<int, int> cnt;

        for_inc(i, n) {
            for_inc(j, n) {
                int x;
                in >> x;
                cnt[x]++;
            }
        }

        vector<int> ret;

        while (ret.size() < n) {
            while (cnt.rbegin()->second == 0) {
                cnt.erase(cnt.rbegin()->first);
            }
            int largest = cnt.rbegin()->first;


            for (int x : ret) {
                int g = __gcd(x, largest);
                cnt[g] -= 2;
            }
            ret.push_back(largest);
            cnt[largest]--;
        }

        for (int x : ret ) {
            out << x << " ";
        }
    }
};
