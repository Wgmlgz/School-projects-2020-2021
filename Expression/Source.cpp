#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <windows.h>
#include <conio.h>

    // help me pls
using str_it = std::string::iterator;
using string = std::string;

void CoutColor(string, int color = -1);

// error custom type
struct error {
  string er;
  str_it pos;
  error(string s, str_it i) {
    er = s;
    pos = i;
  }
};

// expression check
void CheckBrackets(str_it start, str_it end) {
  if (*(start) == '(') {
    if (*(end - 1) == ')') {
      return;
    } else {
      throw error("Expected a ')' after operands", end - 1);
    }
  } else {
    throw error("Expected a '(' after operation", start);
  }
};
std::pair<std::pair<str_it, str_it>, std::pair<str_it, str_it>> GetTwoOperands(
    str_it start, str_it end) {
  CheckBrackets(start, end);
  int brackets = 0;
  auto comma_find = end;
  for (auto cur = start + 1; cur < end - 1; ++cur) {
    if (*cur == '(') ++brackets;
    if (*cur == ')') --brackets;
    if (*cur == ',' and brackets == 0) {
      comma_find = cur;
      break;
    }
  }

  if (comma_find == end) {
    string content = string(start + 1, end - 1);
    throw error("Expected 2 operands, separated by comma", start + 1);
  } else {
    return make_pair(make_pair(start + 1, comma_find),
                     make_pair(comma_find + 1, end - 1));
  }
}
bool BoolExpression(str_it start, str_it end) {
  string s = string(start, end);

  if (s.size() == 0) throw error("Empty expression", start);
  if (s == "true") return true;
  if (s == "false") return false;
  if (s.size() < 9) {
    if (*start == 't') throw error("Do you mean \"true\"?", start);
    if (*start == 'f') throw error("Do you mean \"false\"?", start);
    throw error("Unknown word \"" + s + "\"", start);
  } 

  string oper;
  oper += string() + *start + *(start + 1);

  if (oper == "or") {
    auto operands = GetTwoOperands(start + 2, end);
    return BoolExpression(operands.first.first, operands.first.second) ||
           BoolExpression(operands.second.first, operands.second.second);
  }
  oper += *(start + 2);
  if (oper == "and") {
    auto operands = GetTwoOperands(start + 3, end);
    return BoolExpression(operands.first.first, operands.first.second) &&
           BoolExpression(operands.second.first, operands.second.second);
  }
  if (oper == "not") {
    CheckBrackets(start + 3, end);
    return !BoolExpression(start + 4, end - 1);
  }
  if (*start == 't') throw error("Do you mean \"true\"?", start);
  if (*start == 'f') throw error("Do you mean \"false\"?", start);
  throw error("Unknown word \"" + s + "\"", start);
}

// run
string Exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

// checkers
void TestGCC(string test) {
  string ret;
  string programm;
  programm += "#include <iostream>\n";
  programm += "#define TRUE true\n";
  programm += "#define FALSE false\n";
  // programm += "#define NOT not\n";
  programm += "bool AND(bool a, bool b) { return a && b; }\n";
  programm += "bool OR(bool a, bool b) { return a || b; }\n";
  programm += "bool NOT(bool a) { return !a; }\n";
  programm += "bool Check() {\n";
  programm += "bool b =\n";
  std::transform(test.begin(), test.end(), test.begin(), ::toupper);
  programm += test;
  programm += "\n";
  programm += ";return b;\n";
  programm += "}\n";
  programm += "int main(){std::cout << Check();}\n";
  std::ofstream GCC_check;
  GCC_check.open("GCC_check.cpp");
  GCC_check << programm;
  GCC_check.close();
  string gcc_result = Exec("gcc GCC_check.cpp -lstdc++");
  //std::cout << gcc_result;
  if (gcc_result == "") {
    gcc_result += (Exec(".\\a.exe") == "1" ? "true" : "false") + string("\n");
    CoutColor(gcc_result, 10);
  } else {
    return;
  }
}
void TestWgmlgz(string test) {
  string ret;
  try {
    string tt = (BoolExpression(test.begin(), test.end()) ? "true" : "false");
    ret += tt + "\n";
    CoutColor(ret, 10);
  } catch (const error e) {
    ret += test + '\n';
    string error_pointer;
    for (auto i = test.begin(); i < e.pos; ++i) error_pointer += " ";
    ret += error_pointer + "^" + "\n";
    ret += error_pointer + "|" + "\n";
    ret += e.er + ", at " + std::to_string(e.pos - test.begin() + 1) + "\n";
    CoutColor(ret, 12);
  }
}
void CoutColor(string s, int color) {
  if (color == -1) color = 7;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
  std::cout << s;
  SetConsoleTextAttribute(hConsole, 7);
}
void CheckAll(string test) {
  system("CLS");
  CoutColor(test + "\n");
  CoutColor("\n--------------------- Da ----------------------\n\n", 112);
  TestWgmlgz(test);
  CoutColor("\n--------------------- GCC ---------------------\n\n", 112);
  TestGCC(test);
  CoutColor("\n-----------------------------------------------\n", 112);
  CoutColor("Press enter for new test...", 112);
  _getch();
  system("CLS");
}

// main
int main() {
  std::cout << "Hi\n";
  std::vector<string> st = {"or(or(false,false),false)",
                            "true", "not(true)"
                            "false",
                            "or()",
                            "or(pizda,true)",
                            "or(true,true)",
                            "or(false,false)",
                            "o(false,or(false,true))",
                            "or(falfalse,or(false,true))",
                            
                            "and(true,false)",
                            "and(false,true)",
                            "and(true,true)",
                            "and(false,false)",
                            "not(and(false,or(false,true)))",
                            "and(falfalse,or(false,true))"
  };
  for (string i : st) {
    //CheckAll(i);
  }
  for (;;) {
    string s;
    CoutColor("Please, type new test: ", 112);
    std::cin >> s;
    CheckAll(s);
  }
}
