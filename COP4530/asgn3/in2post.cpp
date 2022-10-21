#include "Stack.h"
#include <iostream>
#include <sstream>

using namespace cop4530;

int precedence(char c);
void inToPost(std::string s);

int main() {
  std::string input;

  std::cout << "Enter your expression: ";
  std::getline(std::cin, input);

  inToPost(input);
  return 0;
}

int prec(char c) {
  if (c == '^')
    return 3;
  else if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return -1;
}

void inToPost(std::string s) {
  Stack<char> _stack;
  std::string return_string;

  for (int i = 0; i < s.length(), i++) {
    char c = s[i];

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')) {
      return_string += c;
    } else if (c == '(') {
      _stack.push(c);
    } else if (c == ')') {
      while (_stack.top() != '(') {
        return_string += _stack.top();
        _stack.pop();
      }
      _stack.pop();
    } else {
      while (!_stack.empty() && precedence(s[i]) <= precedence(_stack.top())) {
        return_string += _stack.top();
        _stack.pop();
      }
    }
  }
  while (!_stack.empty()) {
    return_string += _stack.top();
    _stack.pop();
  }

  std::cout << return_string << std::endl;
}