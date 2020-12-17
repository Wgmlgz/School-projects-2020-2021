#include <iostream>
#include "PostfixExpression.h"
#include <vector>
int main() {
  std::vector<string> tests = {
      "(1+2*(3^4^5+6*sin(3-2*-4))+2)/3"};
  for (auto s : tests) {
    std::cout << ConvertToPostfix(s) << std::endl;
  }
  for(;;) {
    string s ;
    std::cin >> s;
    std::cout << ConvertToPostfix(s) << std::endl;
  }
}