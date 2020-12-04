//#include <iostream>
//#include "expression.h"
#include "expression2.h"

int main() {
  // std::cout << "Hi\n";
  // std::vector<string> st = {"or(or(false,false),false)",
  //                          "true", "not(true)"
  //                          "false",
  //                          "or()",
  //                          "or(pizda,true)",
  //                          "or(true,true)",
  //                          "or(false,false)",
  //                          "o(false,or(false,true))",
  //                          "or(falfalse,or(false,true))",
  //
  //                          "and(true,false)",
  //                          "and(false,true)",
  //                          "and(true,true)",
  //                          "and(false,false)",
  //                          "not(and(false,or(false,true)))",
  //                          "and(falfalse,or(false,true))"
  //};
  // for (string i : st) {
  //  //CheckAll(i);
  //}
  for (;;) {
    CoutColor("Please, type new test (or 'q' to exit): ", 112);

    string s; std::cin >> s;
    if (s == "q") return 0;

    TryExpression(s);
  }
}
