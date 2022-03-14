#include "Evaluate.h"

template <class T>
Evaluate<T>::Evaluate() {
    std::cout << "\nconstructor";
}

template <class T>
Evaluate<T>::~Evaluate() {
    std::cout << "\ndestructor";
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
int Evaluate<T>::operation() {
    char optr = Operators.Top(); // get operator at the top
    int first = Operands.Top(); // get operand at the top
    Operands.pop(); // remove top item
    int second = Operands.Top(); // get new top operand to peform the operation
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
    return ((optr == '^') || (optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
}

template <class T>
void Evaluate<T>::feedStacks(std::string expression) {
    // iterate thru each chr of the expression
    for (unsigned int i = 0; i < expression.size(); i++) {
        char op = expression.at(i); // current char
        if (isOperator(op) && op != ' ') { // if current char is operator and not white spc
            std::cout << "\nCurrent op @ operator: " << op << "\n";
            Operator.push(op); // add op to Operator stack
        }
        else {
            if (op != ' ') { // skip white spc
                std::cout << "\nCurrent op @ operand: " << op;
                Operand.push(op - 48); // add op to operand stack as an int
            }
        }
    }
}