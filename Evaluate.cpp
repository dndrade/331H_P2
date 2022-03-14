#include "Evaluate.h"

template <class T>
Evaluate<T>::Evaluate() {
    std::cout << "\nconstructor";
}

template <class T>
Evaluate<T>::~Evaluate() {
    std::cout << "\ndestructor\n";
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
    int result;                         // final result
    std::cout << "\nOperator top: " << Operator.Top();
    // while the stacks have items
    for (unsigned int i = 0; i <= Operand.size(); i++) {
        char optr = Operator.Top();     // get operator at the top
        if (!Operator.isEmpty()) {
            Operator.pop();                 // remove Top operator
        }
        int first = Operand.Top();      // get operand at the top
        Operand.pop();                  // remove top operand
        int second = Operand.Top();     // get new top operand to peform the operation
        Operand.pop();                  // remove new top operand
        if (optr == '^') {              // exponent
            result = first;
            for (int i = 1; i <= second; i++) {
                result = first * result;
            }
            Operand.push(result);
        }
        else if (optr == '/') {
            result = first / second;
            Operand.push(result);
        }
        else if (optr == '*') {
            result = first * second;
            Operand.push(result);
        }
        else if (optr == '+') {
            result = first + second;
            Operand.push(result);
        }
        else if (optr == '-') {
            result = first - second;
            Operand.push(result);
        }
    }
    std::cout << "\n result: " << result;
    return result; 
}

template <class T>
bool Evaluate<T>::isOperator(char optr) {
    return ((optr == '^') || (optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
}

template <class T>
void Evaluate<T>::feedStacks(std::string expression) {
    // iterate thru each chr of the expression
    for (unsigned int i = 0; i < expression.size(); i++) {
        char op = expression.at(i);         // current char
        if (op != ' ') {                    // if current char is not white space
            if (isOperator(op)) {           // if current char is an operator
                std::cout << "\nCurrent op @ operator: " << op << "\n";
                Operator.push(op);          // add curr char to Operator stack
            }
            else {
                std::cout << "\nCurrent op @ operand: " << op;
                Operand.push(op - 48);      // add op to operand stack as an int
            }
        }
    }
}