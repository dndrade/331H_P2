#include <iostream>
#include <string>
#include <stack>

bool isOperator(char optr);
int priority(char operation);
int operations(std::stack<char> &operators, std::stack<int> &operands);
void evaluateExpression(std::string &expr);

int main()
{

    std::string input;
    std::cout << "\nEnter Expression: ";
    std::cin >> input;

    evaluateExpression(input);

    return 0;
}

/*
 * Returns true if operator
 */
bool isOperator(char optr)
{
    return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
    //return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-') || (optr == '(') || (optr == ')'));
}

/*
 * Precedence of operators
 */
int priority(char operation)
{
    switch (operation)
    {
    // + and - have same precedence
    case '+':
    case '-':
        return 1;
        break;
    // * and / have same precedence
    case '*':
    case '/':
        return 2;
        break;
    }
    return -1;
}

/*
 * Peforms arithmetic operations
 */
int operations(std::stack<char> &operators, std::stack<int> &operands)
{
    std::cout << "\n\nOperations about to start.\n";
    int y = operands.top();
    std::cout << "\nx = " << y << "\n"; // dbg
    operands.pop();
    int x = operands.top();
    std::cout << "\ny = " << x << "\n"; // dbg
    operands.pop();

    char optr = operators.top();
    std::cout << "\nCurrent Operation = " << optr << "\n"; // dbg
    operators.pop();

    switch (optr)
    {
    case '+':
    {
        std::cout << "\n"
                  << x << "+" << y << " = " << x + y; // dbg
        operands.push(x + y);
        std::cout << "\n Top @ Operand after pushing addition [im inside operations()]: " << operands.top(); // dbg
    }
    break;
    case '-':
    {
        std::cout << "\n"
                  << x << "-" << y << " = " << x - y; // dbg
        operands.push(x - y);
        std::cout << "\n Top @ Operand after pushing subtraction [im inside operations()]: " << operands.top(); // dbg
    }
    break;
    case '*':
    {
        std::cout << "\n"
                  << x << "*" << y << " = " << x * y; // dbg
        operands.push(x * y);
        std::cout << "\n Top @ Operand after pushing multiplication [im inside operations()]: " << operands.top(); // dbg
    }
    break;
    case '/':
    {
        if (y == 0)
        {
            std::cout << "\nUndefined: cannot divide by 0.\n";
        }
        else
        {
            std::cout << "\n"
                      << x << "/" << y << " = " << x / y; // dbg
            operands.push(x / y);
            std::cout << "\n Top @ Operand after pushing division [im inside operations()]: " << operands.top(); // dbg
        }
    }
    break;
    } // end switch

    // operators.pop();
    // std::cout << "\n Top @ Operator after operation and pop() [im inside operations()]: " << operators.top(); //dbg
    return operands.top();
}

/*
 * Expression Evaluation, prints the final result
 */
void evaluateExpression(std::string &expr)
{
    std::stack<char> Operator;     // + - * /
    std::stack<int> Operand;       // numbers
    bool prevIsParenthesis = true; // will identify negative numbers

    // iterate through each char of expression
    for (int i = 0; i <= expr.length() - 1; i++)
    {
        std::cout << "\nBegin Loop element: " << expr.at(i) << "\n"; // dbug
        // char current = expr.at(i);

        if (expr.at(i) != ' ' && expr.at(i) != '\n')
        {
            // isDIGIT CHECK
            if (isdigit(expr.at(i)))
            {
                // does not support multidigit numbers yet
                prevIsParenthesis = false;
                std::cout << "\nElement isDIGIT: " << expr.at(i) << "\n"; // dbug
                Operand.push(expr.at(i) - 48);
                std::cout << "\n[line 132] Push element to <operand>: " << expr.at(i) << "\n"; // dbug
            }                                                                                  // // END isDIGIT CHECK

            // OPERATOR CHECK
            else if (isOperator(expr.at(i)))
            {
                std::cout << "\n\nElement isOPERATOR: " << expr.at(i) << "\n";
                // Case 1: Its a negative number
                // if (expr.at(i) == '-' & prevIsParenthesis)
                // {
                //     Operand.push(-1);                                      // add -1 to Operand
                //     std::cout << "\n[line 142] op added to <operand>: -1"; // dbug
                //     Operator.push('*');                                    // add * to Operator
                //     std::cout << "\n[line 144] op added to <operator>: *"; // dbug
                // }
                // PARENTHESIS OPERATION
                if (expr.at(i) == ')')
                {
                    Operator.pop();                                        // remove ')'
                    while (expr.at(i) != '(')
                    {
                        int result = operations(Operator, Operand);        // peform parenthesis operation
                        Operand.push(result);                              // add result to Operand
                    }
                    Operator.pop();                                         // remove '('
                }  // END PARENTHESIS OPERATION
                // Case 2: remaining operators and ('-' subtraction)
                else
                {

                    // Update parenthesis bool
                    if (expr.at(i) == '(')
                    {
                        Operand.push(expr.at(i));
                        prevIsParenthesis = true;
                    }
                    // PRECEDENCE EVALUATION
                    while (!Operator.empty() && (priority(expr.at(i)) <= priority(Operator.top())))
                    {
            
                        std::cout << "\n[line 181] Top <operator> current char: " << expr.at(i); // dbug
                        std::cout << "\n[line 182] Top <operator> priority: " << Operator.top(); // dbug
                        int result = operations(Operator, Operand);                              // perform parenthesis operation
                        Operand.push(result);                                                    // add result to Operand
                    }
                    Operator.push(expr.at(i));
                    std::cout << "\n[line 187] <operator> adding: " << expr.at(i); // dbug 
                    if (expr.at(i) == '-' & prevIsParenthesis)
                    {
                        Operator.pop();                                         // remove -
                        Operand.push(-1);                                      // add -1 to Operand
                        std::cout << "\n[line 192] op added to <operand>: -1"; // dbug
                        Operator.push('*');                                    // add * to Operator
                        std::cout << "\n[line 194] op added to <operator>: *"; // dbug
                    }
                                                                                          // END OF PRECEDENCE EVALUATION
                }  // end of case 2
            }  // END OPERATOR CHECK

        } // end of space if
    }  // END FOR LOOP (finished placing elements into stacks)
    std::cout << "\nAll op have been placed into stacks."; // dbg

    // Print stacks
    std::cout << "\n\nOPERAND STACK"; // dbg
    for (std::stack<int> temp = Operand; !temp.empty(); temp.pop())
    {
        std::cout << "\n      " << temp.top();
    }
    std::cout << "\n\nOPERATOR STACK";
    for (std::stack<char> temp2 = Operator; !temp2.empty(); temp2.pop())
    {
        std::cout << "\n      " << temp2.top();
    }
    // end of print stacks

    // Handle remainder operands
    int result;
    while (!Operator.empty())
    {
        result = operations(Operator, Operand);
    }

    std::cout << "\n Final result: " << result;
}