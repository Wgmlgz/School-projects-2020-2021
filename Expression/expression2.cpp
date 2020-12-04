#include "expression2.h"

void CoutColor(string s, int color) {
  if (color == -1) color = 7;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, color);
  std::cout << s;
  SetConsoleTextAttribute(hConsole, 7);
}


bool IsStartEqual(str_it start, str_it end, string s) {
  if (end - start < s.size()) return false;
  auto cur = start;
  for (auto i = s.begin(); i < s.end() && cur < end; ++i, ++cur) {
    if (*cur != *i) return false;
  }
  return true;
}

void CheckBrackets(str_it start, str_it end) {
  if (end - start == 0) throw error("Expected '(' and ')' after function", start);
  if (*(start) == '(') {
    if (end - start == 1) throw error("Expected a ')' after operands", end - 1);
    if (*(end - 1) == ')') {
      return;
    } else {
      throw error("Expected a ')' after operands", end);
    }
  } else {
    throw error("Expected a '(' after operation", start);
  }
}
vec GetOperands(str_it start, str_it end) {
  vec ret;
  CheckBrackets(start, end);
  int brackets = 0;
  auto last_start = start + 1;
  for (auto cur = start + 1; cur < end - 1; ++cur) {
    if (*cur == '(') ++brackets;
    if (*cur == ')') --brackets;
    if (*cur == ',' and brackets == 0) {
      ret.push_back(CheckExpression(last_start, cur));
      last_start = cur + 1;
    }
  }
  ret.push_back(CheckExpression(last_start, end-1));
  return ret;
}
bool CheckOR(vec v) {
  for (bool i : v)
    if (i) return true;
  return false;
}
bool CheckAND(vec v) {
  for (bool i : v)
    if (!i) return false;
  return true;
}
bool CheckNOT(vec v) {
  return !v[0];
}

bool ExpressinOR(str_it start, str_it end) {
  auto v = GetOperands(start, end);
  if (v.size() < 2)
    throw error("'or' needs 2 or more operands, separated by comma", start + 1);
  else
    return CheckOR(v);
}
bool ExpressinAND(str_it start, str_it end) {
  auto v = GetOperands(start, end);
  if (v.size() < 2)
    throw error("'and' needs 2 or more operands, separated by comma", start + 1);
  else
    return CheckAND(v);
}
bool ExpressinNOT(str_it start, str_it end) {
  auto v = GetOperands(start, end);
  if (v.size() != 1)
    throw error("'not' needs 1 operand", start + 1);
  else
    return CheckNOT(v);
}

bool CheckExpression(str_it start, str_it end) {
  string s = string(start, end);
  if (s == "true") return true;
  if (s == "false") return false;

  if (IsStartEqual(start, end, "or"))
    return ExpressinOR(start + 2, end);
  if (IsStartEqual(start, end, "and"))
    return ExpressinAND(start + 3, end);
  if (IsStartEqual(start, end, "not"))
    return ExpressinNOT(start + 3, end);

  if (IsStartEqual(start, end, "o"))
    throw error("Do you mean 'or'?", start);
  if (IsStartEqual(start, end, "a"))
    throw error("Do you mean 'and'?", start);
  if (IsStartEqual(start, end, "n"))
    throw error("Do you mean 'not'?", start);
  if (IsStartEqual(start, end, "t"))
    throw error("Do you mean 'true'?", start);
  if (IsStartEqual(start, end, "f"))
    throw error("Do you mean 'false'?", start);

  throw error("Unknown word \"" + s + "\"", start);
}

void TryExpression(string test){
  string ret;
  try {
    string tt = (CheckExpression(test.begin(), test.end()) ? "true" : "false");
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