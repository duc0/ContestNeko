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
            timeTake[i] = min(timeTake[i], i + 1);
            timeTake[i] = min(timeTake[i], n - i);
        }

        while (true) {
            bool found = false;
            for_inc(i, n) {
                if (i > 0 && i < n - 1) {
                    int neigh = min(timeTake[i - 1], timeTake[i + 1]);
                    if (neigh + 1 < timeTake[i]) {
                        found = true;
                        timeTake[i] = neigh + 1;
                    }
                }
            }
            if (!found) break;
        }

        int require = 0;
        for_inc(i, n) {
            require = max(require, timeTake[i]);
        }

        out << require << endl;
    }

};
