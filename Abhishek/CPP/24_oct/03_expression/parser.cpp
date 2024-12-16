#include "Parser.h"
#include <stack>
#include <cctype>
#include <stdexcept>

// Validate infix expression
bool Parser::validate(const std::string& infix) {
    int count = 0;
    for (char ch : infix) {
        if (ch == '(') count++;
        if (ch == ')') count--;
        if (!isdigit(ch) && !isspace(ch) && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '(' && ch != ')') {
            return false;
        }
        if (count < 0) return false;
    }
    return count == 0;
}

// Convert infix to postfix
std::string Parser::infixToPostfix(const std::string& infix) {
    std::stack<char> st;
    std::string postfix = "";

    for (char ch : infix) {
        if (isspace(ch)) continue;
        if (isdigit(ch)) {
            postfix += ch;
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

// Build expression tree from postfix
std::shared_ptr<Expression> Parser::buildExpressionTree(const std::string& postfix) {
    std::stack<std::shared_ptr<Expression>> stack;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            stack.push(std::make_shared<Constant>(ch - '0'));
        }
        else if (ch == '+') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(std::make_shared<Addition>(left, right));
        }
        else if (ch == '-') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(std::make_shared<Subtraction>(left, right));
        }
        else if (ch == '*') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(std::make_shared<Multiplication>(left, right));
        }
        else if (ch == '/') {
            auto right = stack.top(); stack.pop();
            auto left = stack.top(); stack.pop();
            stack.push(std::make_shared<Division>(left, right));
        }
    }
    return stack.top();
}

// Operator precedence
int Parser::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::shared_ptr<Expression> Parser::parse(const std::string& infix) {
    std::string postfix = infixToPostfix(infix);
    return buildExpressionTree(postfix);
}
