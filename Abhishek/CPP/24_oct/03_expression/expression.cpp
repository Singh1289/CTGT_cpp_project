#include "Expression.h"
#include <stdexcept>

// Constant class methods
Constant::Constant(double value) : value(value) {}
double Constant::evaluate() const {
    return value;
}

// Addition class methods
Addition::Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : left(left), right(right) {}
double Addition::evaluate() const {
    return left->evaluate() + right->evaluate();
}

// Subtraction class methods
Subtraction::Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : left(left), right(right) {}
double Subtraction::evaluate() const {
    return left->evaluate() - right->evaluate();
}

// Multiplication class methods
Multiplication::Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : left(left), right(right) {}
double Multiplication::evaluate() const {
    return left->evaluate() * right->evaluate();
}

// Division class methods
Division::Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
    : left(left), right(right) {}
double Division::evaluate() const {
    double rightValue = right->evaluate();
    if (rightValue == 0) {
        throw std::runtime_error("Division by zero");
    }
    return left->evaluate() / rightValue;
}
