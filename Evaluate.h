#ifndef EVALUATE_H
#define EVALUATE_H

#include "Stack.h"

template <class T>
class Evaluate
{
private:
	Stack<char> Operand;
	Stack<char> Operator;
	std::string expression;
public:
	Evaluate();
	~Evaluate();

	int operatorOrder(char optr); // returns the precedence


};
#endif // !EVALUATE_H
