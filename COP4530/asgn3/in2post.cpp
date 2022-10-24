#include "Stack.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace cop4530;

int precedence(char c);
std::string inToPost(std::string s);

int evaluateExpression(std::string s);
bool balancedParens(std::string s);
bool isOperator(char c);
bool isInteger(char c);
int operation(int a, int b, char op);

int main() {
  // declare input string and get it from user
  TOP:
  std::string s;
  std::cout << "Enter your expression: ";
  std::getline(std::cin, s);

  s.erase(remove(s.begin(), s.end(), ' '), s.end());

  
  if (!balancedParens(s)) {
    std::cout << "Unbalanced parentheses, this expression cannot be solved."
              << std::endl;
    return 1;
  }

  // overwrite input as postfix notation
  s = inToPost(s);

  // pass input to evalExpress() and return solved value
  int val = evaluateExpression(s);

  switch (val) {
    case -1:
      std::cout << s << " cannot be solved. -1" << std::endl;
      goto TOP;
    case -2:
      std::cout << s << " cannot be solved. -2" << std::endl;
      goto TOP;
    case -3:
      std::cout << s << " cannot be solved. -3" << std::endl;
      goto TOP;
  }
  
  if(val == -1) {
    
  }

  // print expression
  std::cout << s << " = " << val << std::endl;

  goto TOP;
  
  return 0;
}

int precedence(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return -1;
}

std::string inToPost(std::string s) {

  Stack<char> stack;
  std::string result;

  for (int i = 0; i < s.length(); i++) {
    char c = s[i];

    // if operand, add to result
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      result += c;

    // if '(', push to stack
    else if (c == '(')
      stack.push('(');

    // if ‘)’, pop and then add eacch one to result until ‘(‘
    else if (c == ')') {
      while (stack.top() != '(') {
        result += stack.top();
        stack.pop();
      }
      stack.pop();
    }

    // if operator, check precedence and add to result
    else {
      while (!stack.empty() && precedence(s[i]) <= precedence(stack.top())) {
        result += stack.top();
        stack.pop();
      }
      stack.push(c);
    }
  }

  // pop everything from the stack
  while (!stack.empty()) {
    result += stack.top();
    stack.pop();
  }
  return result;
}

bool balancedParens(std::string s) {
  Stack<char> stack;
  bool noParens = true;
  int i = 0;

  if (s.size() == 0) {
    return true;
  }

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(' || s[i] == ')') {
      noParens = false;
    }
  }

  if (noParens) {
    return true;
  }
  
  for (char c : s) {
    if (c == '(') {
      stack.push(c);
    }
    else if ((c == ')' && !stack.empty() && stack.top() == '(')) {
      stack.pop();
    } 
    else if (isalnum(c) || c == '+' || c == '-' || c == '/' || c == '*') {
      continue;
    }
    else {
      return false;
    }
  }

  if (stack.empty()) {
    return true;
  }
  return false;
}

int evaluateExpression(std::string s) {
  // create stack
    Stack<int> stack;
 
    // loop our expression
    for (char c: s)
    {
        // push ints to stack
        if (c >= '0' && c <= '9') {
            stack.push(c - '0');
        }
        else if (isalpha(c)) {
          return -1;
        }
        
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
          
            // pop top 2 ints and store them
            // check if top is another operator
            int x = stack.top();
            stack.pop();

            int y = stack.top();
            stack.pop();
          
            // take char and perform that operation
            if (c == '+') {
                stack.push(y + x);
            }
            else if (c == '-') {
                stack.push(y - x);
            }
            else if (c == '*') {
                stack.push(y * x);
            }
            else if (c == '/') {
                stack.push(y / x);
            }
        }
    }
  
    // return last value on stack
    return stack.top();
}