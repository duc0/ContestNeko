#include "global.hpp"

class TaskB {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        vector<int> h;
        repeat(n) {
            int x;
            in >> x;
            h.push_back(x);
        }

        vector<int> timeTake(n);
        for_inc(i, n) {
            timeTake[i] = h[i];
        }
        timeTake[0] = 1;
        timeTake[n - 1] = 1;
        for_inc_range(i, 1, n - 1) {
            timeTake[i] = min(timeTake[i], timeTake[i - 1] + 1);
        }
        for_dec_range(i, n - 2, 0) {
            timeTake[i] = min(timeTake[i], timeTake[i + 1] + 1);
        }

        int require = 0;
        for_inc(i, n) {
            require = max(require, timeTake[i]);
        }

        out << require << endl;
    }

};
