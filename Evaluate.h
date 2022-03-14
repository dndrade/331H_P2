#ifndef EVALUATE_H
#define EVALUATE_H

#include "Stack.h"

template <class T>
class Evaluate
{
private:
	Stack<int> Operand;
	Stack<char> Operator;
	std::string expression;
public:
	Evaluate();
	~Evaluate();

	void setExpression(std::string expr); // user's expression to be evaluated
	int operatorOrder(char optr); // returns the precedence
	int operation(Stack<char> operators, Stack<int> operands); // performs arithmetic operations


};
#endif // !EVALUATE_H
