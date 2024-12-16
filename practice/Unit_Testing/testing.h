#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <functional>
#include <vector>
#include <string>

class TestFramework {
public:
    struct TestCase {
        std::string name;
        std::function<void()> testFunction;
        bool result;
    };

    void addTest(const std::string& testName, const std::function<void()>& testFunction);
    void runTests();
    void report() const;

private:
    std::vector<TestCase> testCases;
    int passedTests = 0;
    int failedTests = 0;

    void executeTest(TestCase& testCase);
};

#endif // TEST_FRAMEWORK_H
