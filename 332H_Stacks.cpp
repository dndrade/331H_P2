/*
    Program: Stack Project
    Class: CSC 331H Spring 2022
    Student: Thamires L Andrade
    Professor: Anna Salvati
    Description:  Simple expression evaluation program using stacks with 
    precedence evaluation (parenthesis included) and negative numbers
*/

#include <iostream>
#include <string>
#include <stack>

/*
    Status:
        -2+3 [pass]     |   2-4 [pass]      |   2*10 [pass]     |   2+4/3 [pass]
        10/2 [pass]     |   2+3*2 [pass]    |   2+4*2/2 [pass]  |   22*3 [pass]
        -(2+3) [pass]   |   2+(7+5) [pass]  |   2+3+-2 [pass]   |   3+4--5 [pass]
        2*-4 [pass]
*/

bool isOperator(char optr);
int priority(char operation);
int operations(std::stack<char> &operators, std::stack<int> &operands);
void evaluateExpression(std::string &expr);

int main()
{

    std::string input;

    std::cout << "\nEnter Expression or enter Q to Quit.\n ";

    do
    {
        std::cout << "\n\nEnter Expression: ";
        std::getline(std::cin, input);

        evaluateExpression(input);

    } while (input != "q" && input != "Q");
    

    return 0;
}

/*
 * Returns true if operator
 */
bool isOperator(char optr)
{
    return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
}

/*
 * Precedence of operators
 */
int priority(char operation)
{
    // priority goes from least to greatest
    if (operation == '+' || operation == '-')
        return 1;
    else if (operation == '*' || operation == '/')
        return 2;
    else
        return 3;
} // END PRIORITY()

/*
 * Peforms arithmetic operations
 */
int operations(std::stack<char> &operators, std::stack<int> &operands)
{
    std::cout << "\n\n[line 70] Operations about to start.\n"; // dbg
    int y = operands.top();
    std::cout << "\ny = " << y << "\n"; // dbg
    operands.pop();

    int x = operands.top();
    std::cout << "\nx = " << x << "\n"; // dbg
    operands.pop();

    char optr = operators.top();
    std::cout << "\n[line 67] Current Operation = " << optr << "\n"; // dbg
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
    std::cout << "\n\n[line 141] Finished one operation, will return result (operand.top())\n";
    return operands.top();
} // END OPERATIONS()

/*
 * Expression Evaluation, prints the final result
 */
void evaluateExpression(std::string &expr)
{
    std::stack<char> Operator;   // + - * /
    std::stack<int> Operand;     // numbers
    bool lastWasOperator = true; // will help with negative numbers cases

    // iterate through each char of expression
    for (int i = 0; i < expr.length(); i++)
    {
        // isDIGIT CHECK
        if (isdigit(expr.at(i)))
        {
            int number = 0;
            // loop allows multidigit numbers e.g. 22
            while (i <= expr.length() - 1 && isdigit(expr.at(i)))
            {
                number = number * 10 + (expr.at(i) - 48); // convert into int
                i++;
            }

            if (i <= expr.length() - 1)
            {
                i--;
            }

            Operand.push(number); // add operand

            // PRECEDENCE EVALUATION
            if (!Operator.empty() && priority(Operator.top()) == 2)
            {
                operations(Operator, Operand);          // peform operation [line 55]
            }// END OF PRECEDENCE EVALUATION
                
            lastWasOperator = false;
        }

        // Parenthesis check when pushing item into stack
        else if (expr.at(i) == '(')
        {
            if (!lastWasOperator)
            {
                Operator.push('*');
            }

            Operator.push('(');
            lastWasOperator = true;
            // No calculation is done yet, program must keep pushing items
        }
        // PARENTHESIS OPERATION
        else if (expr.at(i) == ')')
        {
            while (Operator.top() != '(')
            {
                operations(Operator, Operand);          // peform operation [line 55]
            }

            Operator.pop();
            lastWasOperator = false;
        }

        // OPERATOR CHECK
        else if (isOperator(expr.at(i)))
        {
            if (expr.at(i) == '-')
            {
                // Negative number case
                if (expr.at(i + 1) == '(')              // peek the next char for a (
                { 
                    Operand.push(-1);
                    lastWasOperator = false;
                }

                else if (lastWasOperator)
                {
                    // It's a negative number
                    int number = 0;
                    i++;
                    while (i <= expr.length() - 1 && isdigit(expr.at(i)))
                    {
                        number = number * 10 + (expr.at(i) - 48);           // convert into int
                        i++;
                    }

                    if (i <= expr.length() - 1)
                        i--;

                    number *= -1;
                    Operand.push(number);

                    if (!Operator.empty() && priority(Operator.top()) == 2)
                    {
                        operations(Operator, Operand);                     // peform operation [line 55]
                    }

                    lastWasOperator = false;
                }
                // If its not a negative number, then its subtraction
                else
                {
                    Operator.push('-');
                    lastWasOperator = true;
                }
            }
            // if it's not a special case, add to operator
            else
            {
                Operator.push(expr.at(i));
                lastWasOperator = true;
            }
        }
        else
        {
            std::cout << "\nYou've quit successfully.\n";
        }
    }

    // handle the remaining operands
    while (!Operator.empty())
    {
        operations(Operator, Operand);
    }

    // print the calculation result
    if (!Operand.empty()) {
        std::cout << "\nFinal result: " << Operand.top() << "\n";
    }
} // END evaluateExpression
