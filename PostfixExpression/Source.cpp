#include <iostream>
#include "PostfixExpression.h"
#include <vector>
int main() {
  std::vector<string> tests = {
      "sin(9*2*5)"};
  for (auto s : tests) {
    std::cout << ConvertToPostfix(s) << std::endl;
  }
  for(;;) {
    string s ;
    std::cin >> s;
    std::cout << ConvertToPostfix(s) << std::endl;
  }
}