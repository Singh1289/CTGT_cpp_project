#include "testing.h"


std::string trimString(std::string &str) {
    int start = 0;
    int end = str.size() - 1;
    while (start <= end && (isspace(str[start]) || str[start] == '"' || str[start] == '\'')) start++;
    while (start <= end && (isspace(str[end]) || str[end] == '"' || str[end] == '\'')) end--;
    if (start > end) return "";
    return str.substr(start, end - start + 1);
}


void testTrim1() {
    std::string input = "    ";
    std::string res= trimString(input);
    if (res!= "") {
        throw std::logic_error("Trim1 test failed");
    }
}
void testTrim2() {
    std::string input = "  Abc  ";
    std::string res= trimString(input);
    if (res!= "Abc") {
        throw std::logic_error("Trim2 test failed");
    }
}
void testTrim3() {
    std::string input = "xxxx    ";
    std::string res= trimString(input);
    if (res!= "xxxx") {
        throw std::logic_error("Trim3 test failed");
    }
}
void testTrim4() {
    std::string input = "" "";
    std::string res= trimString(input);
    if (res!= "" "") {
        throw std::logic_error("Trim4 test failed");
    }
}
void testTrim5() {
    std::string input = "   abhi";
    std::string res= trimString(input);
    if (res!= "   abhi") {
        throw std::logic_error("Trim5 test failed");
    }
}
void testTrim6() {
    std::string input = "   good      test     ";
    std::string res= trimString(input);
    if (res!= "good      test") {
        throw std::logic_error("Trim6 test failed");
    }
}

int main() {
    TestFramework framework;
    framework.addTest("Trim1", testTrim1);
    framework.addTest("Trim2", testTrim2);
    framework.addTest("Trim3", testTrim3);
    framework.addTest("Trim4", testTrim4);
    framework.addTest("Trim5", testTrim5);
    framework.addTest("Trim6", testTrim6);
   

    framework.runTests();
    framework.report();

    return 0;

    // g++ main.cpp testing.cpp -o a
    // ./a


}
