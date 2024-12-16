#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include "Expression.h"

class Parser {
public:
    // function to parse a input string
    static std::shared_ptr<Expression> parse(const std::string& infix);
    // function to validate the input string
    static bool validate(const std::string& infix);

private:
    // helper function to convert infix expression to postfix expression
    static std::string infixToPostfix(const std::string& infix);
    // helper function to build expression tree from postfix expression
    static std::shared_ptr<Expression> buildExpressionTree(const std::string& postfix);
    // helper function to evaluate postfix expression
    static int precedence(char op);
};

#endif
