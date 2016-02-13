#include "/Users/Popan/Dropbox/CPPProjects/CPPProjects/tasks/CodeForces/VC8_2016/TaskB.cpp"

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
        {"2\nRB\n", "G\n", true},{"3\nGRG\n", "BR\n", true},{"5\nBBBBB\n", "B\n", true},{"3\nRGR", "BG", true},{"1 G", "G", true},
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
            TaskB solver;
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
