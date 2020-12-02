#include <iostream>
#include <string>
using namespace std;
bool BoolExpression(string s) {
  if (s == "true") return true;
  if (s == "false") return false;
  if (s[0] == '(') {
    int brackts_counter = 1;
    auto first = s.begin() + 1;
    for (auto cur = first; cur < s.end(); ++cur) {
      if (*cur == '(') ++brackts_counter;
      if (*cur == ')') --brackts_counter;
      if (brackts_counter == 0)
    }
  }
  ;
}

int main() {
  string s;
  cin >> s;
  BoolExpression(s);
}