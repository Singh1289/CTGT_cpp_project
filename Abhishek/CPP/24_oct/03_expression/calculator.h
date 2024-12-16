#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Expression.h"
#include <memory>

class Calculator {
public:
    // Takes the root of the expression tree and evaluates it
    static double evaluate(const std::shared_ptr<Expression>& root);
};

#endif
