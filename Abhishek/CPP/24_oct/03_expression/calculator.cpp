#include "Calculator.h"

double Calculator::evaluate(const std::shared_ptr<Expression>& root) {
    if (!root) {
        throw std::runtime_error("Expression tree is empty.");
    }
    return root->evaluate();
}
