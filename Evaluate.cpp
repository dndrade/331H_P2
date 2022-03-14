#include "Evaluate.h"

template <class T>
Evaluate<T>::Evaluate() {
    std::cout << "constructor";
}

template <class T>
Evaluate<T>::~Evaluate() {
    std::cout << "destructor";
}


//template <class T>
//void Evaluate<T>::setExpression(std::string expr) {
//    expression = expr;
//}


template <class T>
int Evaluate<T>::operatorOrder(char optr) {
    if (optr == '(' || ')') {
        return 0;
    }
    // exponents
    else if (optr == '^') {
        return 3;
    }
    // division and multiplication are the same level
    else if (optr == '/' || optr == '*') { 
        return 2;
    } 
    // addition and subtraction are the same level
    else if (optr == '+' || optr == '-') {
        return 1;
    }
    else {
        return -1;
    }
}

template <class T>
int Evaluate<T>::operation(Stack<char> operators, Stack<int> operands) {
    char optr = operators.pop(); // get operator at the top
    int first = operands.pop(); // get operand at the top
    int second = operands.pop(); // get following operand to peform the operation
    if (optr == '^') { // exponent
        int result = first;
        for (int i = 1; i <= second; i++) {
            result = first * result;
        }
        return result;
    }
    else if (optr == '/') {
        return first / second;
    }
    else if (optr == '*') {
        return first * second;
    }
    else if (optr == '+') {
        std::cout << first + second;
        return first + second;
    }
    else if (optr == '-') {
        return first - second;
    }
}

template <class T>
bool Evaluate<T>::isOperator(char optr) {
    return (optr == '^' || optr == '*' || optr == '/' || optr == '+' || optr == '-' || );
}

template <class T>
void Evaluate<T>::feedStacks(std::string expression) {
    for (int i = 0; i < expression.size(); i++) { // iterate thru expression
        char op = expression.at(i); // current char
        if (isOperator(op)) { // if current char is operator
            std::cout << "Current op @ operator: " << op;
            Operator.push(op); // add op to Operator stack
        }
        else {
            std::cout << "Current op @ operand: " << op;
            Operand.push(stoi(op)); // add op to operand stack as an int
        }
    }
}