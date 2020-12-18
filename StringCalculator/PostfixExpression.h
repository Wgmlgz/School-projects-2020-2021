#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using str_it = std::string::iterator;
// custom error type
struct error {
  string er;
  str_it pos;
  error(string s, str_it i) {
    er = s;
    pos = i;
  }
};

std::string GetPostfix(std::string& str);
void CheckRegularExpression(std::string& str);