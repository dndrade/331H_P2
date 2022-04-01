#include <iostream>
#include <string>
#include <stack>

/*
    Status:
        -2+3 [pass]
        2+4/3 [pass]
        -(2+3) [fail]
        -2+5*5 [fail]
        2+(7+5) [pass]
        2+3+-2 [fail]
        3+4--5 [fail]
*/


bool isOperator(char optr);
int priority(char operation);
int operations(std::stack<char> &operators, std::stack<int> &operands);
void evaluateExpression(std::string &expr);

int main()
{

    std::string input;
    std::cout << "\nEnter Expression: ";
    std::getline(std::cin, input);

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
    // maybe add () here [review isdigit @ evaluateExpression]
    }
    return -1;
} // END PRIORITY()

/*
 * Peforms arithmetic operations
 */
int operations(std::stack<char> &operators, std::stack<int> &operands)
{
    std::cout << "\n\n[line 70] Operations about to start.\n";
    int y = operands.top();
    std::cout << "\nx = " << y << "\n"; // dbg
    operands.pop();
    int x = operands.top();
    std::cout << "\ny = " << x << "\n"; // dbg
    operands.pop();

    char optr = operators.top();
    std::cout << "\n[line 79] Current Operation = " << optr << "\n"; // dbg
    operators.pop();

    switch (optr)
    {
    case '+':
    {
        std::cout << "\n"
                  << x << "+" << y << " = " << x + y; // dbg
        operands.push(x + y);
        std::cout << "\n[line 89] Top @ Operand after pushing addition [im inside operations()]: " << operands.top(); // dbg
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
            std::cout << "\n [line 112] Undefined: cannot divide by 0.\n";
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

    return operands.top();
} // END OPERATIONS()

/*
 * Expression Evaluation, prints the final result
 */
void evaluateExpression(std::string &expr)
{
    std::stack<char> Operator;     // + - * /
    std::stack<int> Operand;       // numbers
    bool prevIsParenthesis = true; // will identify negative numbers

    // iterate through each char of expression
    for (int i = 0; i < expr.length(); i++)
    {
        std::cout << "\nBegin Loop element: " << expr.at(i) << "\n"; // dbug

            // isDIGIT CHECK
            if (isdigit(expr.at(i)))
            {
                // does not support multidigit numbers yet
                prevIsParenthesis = false;
                std::cout << "\nElement isDIGIT: " << expr.at(i) << "\n"; // dbug
                int number = 0;
                while ( i <= expr.length() - 1 && isdigit(expr.at(i)))
                {
                    number = number * 10 + (expr.at(i) - 48); // convert into int
                    i++;
                }
                if (i <= expr.length() - 1)
                {
                    i--;
                }
                std::cout << "\nop added to <operand>: " << number; // dbg
                Operand.push(number);                               // add operand
            }                                                                                  // // END isDIGIT CHECK

            // OPERATOR CHECK
            else if (isOperator(expr.at(i)))
            {
                std::cout << "\n\nElement isOPERATOR: " << expr.at(i) << "\n";
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
                        std::cout << "\n[line 191] Top <operator> current char: " << expr.at(i); // dbug
                        std::cout << "\n[line 132] Top <operator> priority: " << Operator.top(); // dbug
                        int result = operations(Operator, Operand);                              // perform parenthesis operation
                        Operand.push(result);                                                    // add result to Operand
                    } // END while loop
                    // END OF PRECEDENCE EVALUATION
                    Operator.push(expr.at(i));                                                  // add Operator
                    std::cout << "\n[line 199] <operator> adding: " << expr.at(i); // dbug 
                    if (expr.at(i) == '-' && prevIsParenthesis)
                    {
                        Operator.pop();                                         // remove -
                        Operand.push(-1);                                      // add -1 to Operand
                        std::cout << "\n[line 204] op added to <operand>: -1"; // dbug
                        Operator.push('*');                                    // add * to Operator
                        std::cout << "\n[line 206] op added to <operator>: *"; // dbug
                    }
                }  // end of case 2
            }  // END OPERATOR CHECK
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
} // END expression EVALUATION
