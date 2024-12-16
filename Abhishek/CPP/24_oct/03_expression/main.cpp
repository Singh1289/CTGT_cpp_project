#include "Parser.h"
#include "Calculator.h"
#include <iostream>
using namespace std;

int main() {
    //string input = "3 + 2 * (8 - 2)/3";
    string input ;
    cout << "Enter an expression: ";
    getline(cin, input);

    // Validate the expression
    if (!Parser::validate(input)) {
        cerr << "Invalid expression!" << endl;
        return 1;
    }

    try {
        // Parse the expression and build the expression tree
        auto expression = Parser::parse(input);

        // Use Calculator to evaluate the expression tree
        double result = Calculator::evaluate(expression);

        // Output the result
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}


// cd .\CPP_Assessment\24-Nov\expression
// g++ *.h *.cpp -o a.exe

