#include "testing.h"

void TestFramework::addTest(const std::string& testName, const std::function<void()>& testFunction) {
    testCases.push_back({testName, testFunction, false});
}

void TestFramework::runTests() {
    for (auto& testCase : testCases) {
        executeTest(testCase);
    }
}

void TestFramework::executeTest(TestCase& testCase) {
    try {
        testCase.testFunction();
        testCase.result = true;
        passedTests++;
    } catch (const std::exception& e) {
        std::cerr << "Test \"" << testCase.name << "\" failed: " << e.what() << std::endl;
        failedTests++;
    } catch (...) {
        std::cerr << "Test \"" << testCase.name << "\" failed: Unknown error" << std::endl;
        failedTests++;
    }
}

void TestFramework::report() const {
    std::cout << "\nTest Report:\n";
    std::cout << "Total Tests: " << testCases.size() << " : ";
    std::cout << "Passed: " << passedTests << " : ";
    std::cout << "Failed: " << failedTests << "\n";
}
