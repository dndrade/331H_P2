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

template <class T>
int Evaluate<T>::operation(int first, int second, char optr) {
    if (optr == '^') {
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
        return first + second;
    }
    else if (optr == '-') {
        return first - second;
    }
}