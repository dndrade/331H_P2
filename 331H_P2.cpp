// 331H_P2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>

using namespace std;

bool isOperator(char);
int main(){
    stack<double> operands;
    stack<char> operators;
    
    bool previousIsOperator = false;
    
    cout << "Please enter an equation: ";
    // 88 + 9\n
     double number;
     while(cin.peek() != '\n'){
      cout << "Current character " << (char)cin.peek() << "\n";
      
      if(isdigit(cin.peek()) || (cin.peek() == '-' && previousIsOperator)) {
          cin >> number;
          operands.push(number);
          // 8 * 9 + 1
          //  72 + 1 
          if(!operators.empty() && (operators.top() == '*' || operators.top() == '/')){
              double num1 = operands.top();
            operands.pop();
            double num2 = operands.top();
            operands.pop();

            char operation = operators.top();
            operators.pop();


            if(operation == '+'){
            operands.push(num2 + num1);
            }
            else if(operation == '-'){
            operands.push(num2 - num1);
            }
            else if(operation == '*'){
            operands.push(num2 * num1);
            }
            else if(operation == '/'){
            operands.push(num2 / num1);
            }
        }
    }else if(isOperator(cin.peek())){
      // It's an operator do something
      operators.push(cin.get());
    }else{
      // If current character is not a number or an operator, ignore it
      cin.ignore();
    }
  }

  while(!operators.empty()){
    double num1 = operands.top();
    operands.pop();
    double num2 = operands.top();
    operands.pop();

    char operation = operators.top();
    operators.pop();

    if (operation == '+'){
      operands.push(num2 + num1);
    }
    else if (operation == '-'){
      operands.push(num2 - num1);
    }
    else if(operation == '*'){
      operands.push(num2 * num1);
    }
    else if(operation == '/'){
      operands.push(num2 / num1);
    }
  }

  cout << "Answer: " << operands.top() << "\n";
  return 0;
}

bool isOperator(char optr) {
  return ((optr == '*') || (optr == '/') || (optr == '+') || (optr == '-'));
}