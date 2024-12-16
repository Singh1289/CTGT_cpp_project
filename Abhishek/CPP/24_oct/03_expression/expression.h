#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <string>

// Base class
class Expression {
public:
    virtual ~Expression() = default;
    virtual double evaluate() const = 0;
};

// Derived constants class
class Constant : public Expression {
    double value;
public:
    explicit Constant(double value);
    double evaluate() const override;
};

// Derived class for addition
class Addition : public Expression {
    std::shared_ptr<Expression> left, right;
public:
    Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    double evaluate() const override;
};

// Derived class for subtraction
class Subtraction : public Expression {
    std::shared_ptr<Expression> left, right;
public:
    Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    double evaluate() const override;
};

// Derived class for multiplication
class Multiplication : public Expression {
    std::shared_ptr<Expression> left, right;
public:
    Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    double evaluate() const override;
};

// Derived class for division
class Division : public Expression {
    std::shared_ptr<Expression> left, right;
public:
    Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    double evaluate() const override;
};

#endif
