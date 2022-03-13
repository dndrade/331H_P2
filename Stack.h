#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

template <class T>
class Stack
{
private:
    std::vector<T> items;     // 
public:
    Stack();
    Stack(const Stack<T>&); // copy constructor
    ~Stack();               // destructor

    //methods
    void push(T item);      // add item into stack
    void pop();             // remove item from stack
    void Top();           // item at the top
    void copy(const Stack<T>& other); // copy stack
    const Stack<T>& operator=(const Stack<T>& other); // assignment operator
    void print();           // prints the stack

    bool isEmpty();         // returns true if empty
};
#endif // !STACK_H

