#include <iostream>
#include "PostfixExpression.h"
#include <vector>
int main() {
  std::vector<string> tests = {
      "5+64534+435-45*2",
  "-1*(1-1)", "--1", "sin(666)"};
  for (auto s : tests) {
    //std::cout << ConvertToPostfix(s, true) << std::endl;
  }
  for(;;) {
    string s ;
    std::cin >> s;
    std::cout << ConvertToPostfix(s) << std::endl;
  }
}