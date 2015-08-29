#include "global.hpp"
#include "InputIterables.hpp"
#include "Iterator.hpp"

int getMax(int a, int b) {return max(a, b);}
class TaskB {
public:
    void solve(std::istream& in, std::ostream& out) {
        int n;
        in >> n;
        vector<int> h = collect(inputIterable<int>(in, n));
        vector<int> timeTake = h;
        timeTake[0] = 1;
        timeTake[n - 1] = 1;
        for_inc_range(i, 1, n - 1) {
            timeTake[i] = min(timeTake[i], timeTake[i - 1] + 1);
        }
        for_dec_range(i, n - 2, 0) {
            timeTake[i] = min(timeTake[i], timeTake[i + 1] + 1);
        }
        out << aggregateMax(stdIterable<int>(timeTake.begin(), timeTake.end())) << endl;
    }

};
