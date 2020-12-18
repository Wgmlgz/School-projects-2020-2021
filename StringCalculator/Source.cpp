#include <iostream>
#include <string>
#include "PostfixExpression.h"

int main() {
  std::string str;
  std::getline(std::cin, str);

  try {
    std::string postfix = GetPostfix(str);
    std::cout << postfix;
  } catch (std::exception e) {
  
  }
}