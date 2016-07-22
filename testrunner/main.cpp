#include "/Users/Popan/Dropbox/CPPProjects/CPPProjects/tasks/CodeForces/R364/TaskC.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>

#define IO_USE_CSTDIO

namespace jhelper {

struct Test {
    std::string input;
    std::string output;
    bool active;
};

bool check(std::string expected, std::string actual) {
    while(!expected.empty() && isspace(*--expected.end()))
        expected.erase(--expected.end());
    while(!actual.empty() && isspace(*--actual.end()))
        actual.erase(--actual.end());
    return expected == actual;
}

} // namespace jhelper

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
    std::vector<jhelper::Test> tests = {
        {"6 7\n1 6\n2 1 6\n2 3 5\n3 4 9\n4 6 4\n4 6 5\n4 5 1\n3 1 3\n", "8\n2\n2 7\n", true},{"6 7\n1 6\n2 3 1\n1 2 2\n1 3 3\n4 5 4\n3 6 5\n4 6 6\n1 5 7\n", "9\n2\n4 5\n", true},{"5 4\n1 5\n2 1 3\n3 2 1\n3 4 4\n4 5 2\n", "1\n1\n2\n", true},{"2 3\n1 2\n1 2 734458840\n1 2 817380027\n1 2 304764803\n", "-1\n", true},{"1000 0\n4 997", "0", true},{"1000 2\n4 997\n3 994 2\n997 2 1\n", "0", true},{"1000 2\n4 997\n4 5 3 \n5 997 1", "1\n1\n2", true},
    };
    bool allOK = true;
    int testID = 0;
    std::cout << std::fixed;
    double maxTime = 0.0;
    for(const jhelper::Test& test: tests ) {
        std::cout << "Test #" << ++testID << std::endl;
        std::cout << "Input: \n" << test.input << std::endl;
        std::cout << "Expected output: \n" << test.output << std::endl;
        if (test.active) {
            std::stringstream in(test.input);
            std::ostringstream out;
            std::clock_t start = std::clock();
            TaskC solver;
            solver.solve(in, out);
            std::clock_t finish = std::clock();
            double currentTime = double(finish - start) / CLOCKS_PER_SEC;
            maxTime = std::max(currentTime, maxTime);
            std::cout << "Actual output: \n" << out.str() << std::endl;
            bool result = jhelper::check(test.output, out.str());
            allOK = allOK && result;
            std::cout << "Result: " << (result ? "OK" : "Wrong answer") << std::endl;
            std::cout << "Time: " << currentTime << std::endl;
        }
        else {
            std::cout << "SKIPPED\n";
        }

        std::cout << std::endl;

    }
    if(allOK) {
        std::cout << "All OK" << std::endl;
    }
    else {
        std::cout << "Some cases failed" << std::endl;
    }
    std::cout << "Maximal time: " << maxTime << "s." << std::endl;
    return 0;
}
