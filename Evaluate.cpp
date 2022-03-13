#include "Evaluate.h"

template <class T>
Evaluate<T>::Evaluate() {

}

template <class T>
Evaluate<T>::~Evaluate() {

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