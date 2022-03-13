// 331H_P2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stack.h"
#include "Stack.cpp"

int main()
{
    Stack<int> s;

    s.push(1);
    s.push(3);
    s.push(5);
    s.print();

    std::cout << "\n COPY \n";

    /*Stack<int> p;
    p.copy(s);
    p.print();*/


}

