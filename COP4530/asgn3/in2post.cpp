#include "Stack.h"
#include <iostream>
#include <sstream>

using namespace cop4530;

int precedence(char c);
std::string inToPost(std::string s);

int evaluateExpression(std::string s);
bool balancedParens(std::string s);
int isOperator(char c);
int isInteger(char c);
int operation(int a, int b, char op);

int main() {
  // declare input string and get it from user
  std::string input;
  std::cout << "Enter your expression: ";
  std::getline(std::cin, input);

  if (!balancedParens(input)) {
    std::cout << "Unbalanced parentheses, this expression cannot be solved."
              << std::endl;
    return 1;
  }

  // overwrite input as postfix notation
  input = inToPost(input);

  // pass input to evalExpress and return solved value
  int val = evaluateExpression(input);

  // print expression
  std::cout << input << " = " << val << std::endl;

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

    // If the scanned character is
    // an operand, add it to output string.
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9'))
      result += c;

    // If the scanned character is an
    // ‘(‘, push it to the stack.
    else if (c == '(')
      stack.push('(');

    // If the scanned character is an ‘)’,
    // pop and to output string from the stack
    // until an ‘(‘ is encountered.
    else if (c == ')') {
      while (stack.top() != '(') {
        result += stack.top();
        stack.pop();
      }
      stack.pop();
    }

    // If an operator is scanned
    else {
      while (!stack.empty() && precedence(s[i]) <= precedence(stack.top())) {
        result += stack.top();
        stack.pop();
      }
      stack.push(c);
    }
  }

  // Pop all the remaining elements from the stack
  while (!stack.empty()) {
    result += stack.top();
    stack.pop();
  }

  std::cout << result << std::endl;
}

bool balancedParens(std::string s) {
  Stack<char> stack;
  bool noParens = true;
  int i = 0;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      noParens = false;
    }
  }

  if (noParens) {
    return true;
  }

  if (s.size() == 0) {
    return true;
  }

  while (i < s.size()) {

    if (s[i] == '(') {
      stack.push(s[i]);
    }

    else if ((s[i] == ')' && !stack.empty() && stack.top() == '(')) {
      stack.pop();
    } else {
      return false;
    }
    i++;
  }

  if (stack.empty()) {
    return true;
  }
  return false;
}

// takes postfix notation and determines an answer
int evaluateExpression(std::string s) {
  int a, b;
  Stack<int> stack;
  std::string::iterator it;
  for (it = s.begin(); it != s.end(); it++) {
    // read elements and perform postfix evaluation
    if (isOperator(*it) != -1) {
      a = stack.top();
      stack.pop();
      b = stack.top();
      stack.pop();
      stack.push(operation(a, b, *it));
    } else if (isInteger(*it) > 0) {
      stack.push(*it - 48);
    }
  }
  return stack.top();
}

int isOperator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    return 1; // character is an operator
  return -1;  // not an operator
}

int isInteger(char c) {
  if (c >= '0' && c <= '9')
    return 1; // character is an operand
  return -1;  // not an operand
}

int operation(int a, int b, char op) {
  // Perform operation
  if (op == '+')
    return b + a;
  else if (op == '-')
    return b - a;
  else if (op == '*')
    return b * a;
  else if (op == '/')
    return b / a;
  return -1;
}
