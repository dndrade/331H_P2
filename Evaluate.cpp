#include "Evaluate.h"

template <class T>
Evaluate<T>::Evaluate() {
    std::cout << "constructor";
}

template <class T>
Evaluate<T>::~Evaluate() {
    std::cout << "destructor";
}


template <class T>
void Evaluate<T>::setExpression(std::string expr) {
    expression = expr;
}


template <class T>
int Evaluate<T>::operatorOrder(char optr) {
    // exponents
    if (optr == '^') {
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
    first = operands.pop(); // get operand at the top
    second = operands.pop(); // get following operand to peform the operation
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