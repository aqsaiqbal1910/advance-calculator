#include <iostream>
#include <string>
#include <stack>

double calculate(double a, double b, char op) {
    switch(op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                std::cout << "Error: division by zero." << std::endl;
                exit(1);
            }
            return a / b;
        default:
            std::cout << "Error: invalid operator." << std::endl;
            exit(1);
    }
}

int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

double evaluateExpression(std::string expression) {
    std::stack<double> operandStack;
    std::stack<char> operatorStack;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            double num = c - '0';
            while (i + 1 < expression.length() && isdigit(expression[i+1])) {
                num = num * 10 + (expression[i+1] - '0');
                i++;
            }
            operandStack.push(num);
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();
                double b = operandStack.top();
                operandStack.pop();
                double a = operandStack.top();
                operandStack.pop();
                operandStack.push(calculate(a, b, op));
            }
            operatorStack.pop(); // pop the '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!operatorStack.empty() && operatorStack.top() != '(' && getPrecedence(c) <= getPrecedence(operatorStack.top())) {
                char op = operatorStack.top();
                operatorStack.pop();
                double b = operandStack.top();
                operandStack.pop();
                double a = operandStack.top();
                operandStack.pop();
                operandStack.push(calculate(a, b, op));
            }
            operatorStack.push(c);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();
        double b = operandStack.top();
        operandStack.pop();
        double a = operandStack.top();
        operandStack.pop();
        operandStack.push(calculate(a, b, op));
    }

    return operandStack.top();
}

int main() {
    std::string expression;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expression);
    double result = evaluateExpression(expression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}