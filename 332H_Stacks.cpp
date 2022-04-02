#include <iostream>
#include <string>
#include <stack>

/*
    Status:
        -2+3 [pass]     |   2-4 [pass]      |   2*10 [pass]     |   2+4/3 [pass]
        10/2 [pass]     |   2+3*2 [pass]    |   2+4*2/2 [pass]  |   22*3 [pass]
        -(2+3) [fail]   |   2+(7+5) [fail]  |   2+3+-2 [fail]   |   3+4--5 [fail]
        2*-4 [fail]
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
    // return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
    return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-') || (optr == '(') || (optr == ')'));
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
        return 1;
        break;
    case '-':
        return 1;
        break;
    // * and / have same precedence
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    // maybe add () here [review isdigit @ evaluateExpression]
    case ')':
        return 3;
        break;
    }
    return -1;
} // END PRIORITY()

/*
 * Peforms arithmetic operations
 */
int operations(std::stack<char> &operators, std::stack<int> &operands)
{
    std::cout << "\n\n[line 70] Operations about to start.\n";      //dbg
    int y = operands.top();
    std::cout << "\ny = " << y << "\n"; // dbg
    operands.pop();
    int x;
    if (!operands.empty()) {
        x = operands.top();
    }
    else {
        if (operators.top() == '-' || operators.top() == '+')
        x = 0;
        else if (operators.top() == '*' || operators.top() == '/') {
            x = 1;
        }
    }
    
    std::cout << "\nx = " << x << "\n"; // dbg
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
    std::cout << "\n\n[line 141] Finished one operation, will return result (operand.top())\n";
    return operands.top();
} // END OPERATIONS()

/*
 * Expression Evaluation, prints the final result
 */
void evaluateExpression(std::string &expr)
{
    std::stack<char> Operator;     // + - * /
    std::stack<int> Operand;       // numbers
    bool isOpenParenthesis = true; // will identify negative numbers
    //bool isNum = false;            // if current expr is a number, then its true
    //char previousChar;             // holds the value of previous char/i

    // iterate through each char of expression
    for (int i = 0; i < expr.length(); i++)
    {
        std::cout << "\nBegin Loop element: " << expr.at(i) << "\n"; // dbug

        // isDIGIT CHECK
        if (isdigit(expr.at(i)))
        {
            //isNum = true;
            std::cout << "\nElement isDIGIT: " << expr.at(i) << "\n"; // dbug
            int number = 0;
            while (i <= expr.length() - 1 && isdigit(expr.at(i)))
            {
                number = number * 10 + (expr.at(i) - 48); // convert into int
                i++;
            }
            if (i <= expr.length() - 1)
            {
                i--;
            }
            std::cout << "\nop added to <operand>: " << number; // dbg

            Operand.push(number); // add operand
        } // END isDIGIT CHECK

        // OPERATOR CHECK
        else if (isOperator(expr.at(i)))
        {
            std::cout << "\n\nElement isOPERATOR: " << expr.at(i) << "\n";

            // OPERATIONS WITH OPERATORS
            // Swap [+ for -] OR [- for +]
            if ((!Operator.empty() && (expr.at(i) == '-' && Operator.top() == '+')) ||
                (!Operator.empty() && (expr.at(i) == '+' && Operator.top() == '-')))
            {
                Operator.pop();            // remove '+'
                Operator.push(expr.at(i)); // add '-'
                std::cout << "\n[line 190] + and - equals - ";

            }
            // Swap [- for +]
            else if (!Operator.empty() && (expr.at(i) == '-' && Operator.top() == '-'))
            {
                Operator.pop();     // remove '-'
                Operator.push('+'); // add '+'
                std::cout << "\n[line 198] - and - equals + ";
            }
            // Swap [+ for -]
            else if (!Operator.empty() && (expr.at(i) == '+' && Operator.top() == '+'))
            {
                Operator.pop();     // remove '+'
                Operator.push('-'); // add '-'
                std::cout << "\n[line 190] + and + equals - ";
            }
            // END OPERATIONS WITH OPERATORS

            // Parenthesis check when pushing item into stack
            if (expr.at(i) == '(')
            {
                // No calculation is done, program must keep pushing items
                isOpenParenthesis = true; // Parenthesis is open, expression to follow

                // check if Operator top is negative sign before pushing '('
                if (!Operator.empty() && Operator.top() == '-')
                {
                    // If true, then it must be replaced (multiby by -1)
                    Operator.pop(); // remove '-'
                    Operator.push('*');
                    Operand.push(-1);
                } // this turns the result of parenthesis operation into a NEGATIVE RESULT

                /* [OPTIONAL: Multiplication without *] : a flag (or variable) would tell if the previous
                element added was an operand. If true, then it's and expression that looks like 2(3+).
                So, before pushing the parenthesis, a * must be pushed.
                */
                // finally, add '(' to Operand
                Operand.push(expr.at(i));
            } // END Parenthesis Update

            // NEGATIVE CASE (-2+3) and -2+3
            if ((!Operator.empty() && (expr.at(i) == '-' && Operator.top() == '(')) || (Operand.empty() && expr.at(i) == '-') )
                {
                    // If - is to be inserted into stack after an open parenthesis
                    // then the next Operand to be inserted is a negative number.
                    Operand.push(-1);
                    Operator.push('*');
                    // OR if there are no operands and - is the next operator to be added
                    // then the next Operand to be inserted is a negative number.
                    // DO NOT add expr.at(i)
                } // END of CASE

            // PRECEDENCE EVALUATION
            while (!Operator.empty() && (priority(expr.at(i)) < priority(Operator.top())))
            {
                std::cout << "\n[line 235] Top <operator> current char: " << expr.at(i); // dbug
                std::cout << "\n[line 236] Top <operator> priority: " << Operator.top(); // dbug
                // Only calculate if there are numbers in Operand
                //if (!Operand.empty()) {
                    int result = operations(Operator, Operand);                          // perform parenthesis operation
                    Operand.push(result);                                               // add result to Operand
                //}
            }
            // END OF PRECEDENCE EVALUATION

            // PARENTHESIS OPERATION
            if (expr.at(i) == ')')
            {
                // dont even add ')'
                while (expr.at(i) != '(')
                {
                    std::cout << "\n[line 172] About to start evaluating parenthesis expression"; // dbug
                    // PRECEDENCE EVALUATION
                    while (!Operator.empty() && (priority(expr.at(i)) <= priority(Operator.top())))
                    {
                        std::cout << "\n[line 252] Evaluating parenthesis expression";           // dbug
                        std::cout << "\n[line 253] Top <operator> current char: " << expr.at(i); // dbug
                        std::cout << "\n[line 254] Top <operator> priority: " << Operator.top(); // dbug
                        int result = operations(Operator, Operand);                              // perform parenthesis operation
                        Operand.push(result);                                                    // add result to Operand
                    }                                                                            // END while loop
                    // END OF PRECEDENCE EVALUATION
                }
                Operator.pop();                                                           // remove '('
                isOpenParenthesis = false;                                               // open parenthesis from procedure has been removed
            }
            else {
                Operator.push(expr.at(i));          // add operator, not sure if this is handled properly
            }
        } // END OPERATOR CHECK
    }// END FOR LOOP (finished placing elements into stacks)
        std::cout << "\nOut of main loop. All op have been placed into stacks."; // dbg

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
