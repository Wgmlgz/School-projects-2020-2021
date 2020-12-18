#pragma once
#include <stack>
#include <string>
#include <math.h>
#include <vector>

// easy life
using str_it = std::string::iterator;
using std::string;
using stack = std::stack<char>;
using std::to_string;

// error custom type
struct error {
  string er;
  str_it pos;
  error(string s, str_it i) {
    er = s;
    pos = i;
  }
};

bool hasChar(string str,char ch) {
  return str.find(ch) != string::npos;
} 
void PrintStack(stack s) {
  if (s.empty()) {
    std::cout << std::endl;
  } else {
    char x = s.top();
    s.pop();
    PrintStack(s);
    std::cout << x << " ";
    s.push(x);
  }
}
int CalculatePostfix(string str) {
  std::stack<int> st;

  auto isDigit = [](char ch) -> bool { return (ch >= '0' && ch <= '9'); };
  auto get = [&st]() {
    int tm = st.top();
    st.pop();
    return tm;
  };
  for (auto i : str) {
    if (isDigit(i)) st.push(i - '0');

    if (i == '+') {
      st.push(get() + get());
    }
    if (i == '-') {
      auto aa = get(), bb = get();
      st.push(bb - aa);
    }
    if (i == '*') {
      st.push(get() * get());
    }
    if (i == '_') {
      st.push(-get());
    }
    if (i == 's') {
      st.push(std::sin(get()));
    }
  }

  return st.top();
}
double calc(string s) {
  char ch;
  std::vector<double> st;
  for (int i = 0; i < s.size(); i++) {
    ch = s[i];
    if (ch == ' ') continue;
    if (ch == '_') {
      double b = st.back();
      st.pop_back();
      st.push_back(-b);
    } else if (ch == 's') {
      double b = st.back();
      st.pop_back();
      st.push_back(std::sin(b));
    } 
    else if (ch >= '0' && ch <= '9') {
      string number = "";
      while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        number += s[i++];
      }
      i--;
      int x = 0;
      for (int j = number.size() - 1, p = 1; j >= 0; p *= 10, j--)
        x += (number[j] - '0') * p;
      st.push_back(x);
    } else {
      if (st.size() < 2) std::exception("Not enough operands for binary operation");
      double b = st.back();
      st.pop_back();
      double a = st.back();
      st.pop_back();
      if (ch == '+') {
        st.push_back(a + b);
      } else if (ch == '-') {
        st.push_back(a - b);
      } else if (ch == '*') {
        st.push_back(a * b);
      } else if (ch == '/') {
        if (b == 0) throw std::exception("Division by zero");
        st.push_back(a / b);
      } else if (ch == '^') {
        st.push_back(pow(a, b));
      }
    }
  }
  if (st.size() > 1) std::exception("WTF HOW???");
  return st.back();
}
string ConvertToPostfix(string str, bool display_str = false) {
  string ret;
  try {
    string res;
    stack st;
    st.push('(');
    str.push_back(')');
    auto get = [&st]() {
      char tmp = st.top();
      st.pop();
      return tmp;
    };
    auto pushOperation = [&res](char val) {
      //res.push_back(' ');
      res.push_back(val);
      //res.push_back(' ');
    };
    char last = 'q';
    for (auto i = str.begin(); i < str.end(); ++i) {
      char val = *i;
      if (st.empty()) {
        //std::cout << "&&&&&&&" << val << "&&&&&&&";
        // throw error("Expected a '('", str.end());
      }
      //PrintStack(st);
      
      auto threeLetterFunc = [&st, &val, &i, &str, get,
                              &res](string exp) -> bool {
        auto old_i = i;
        if (hasChar(string(1, exp[0]), val)) {
          if (i + 2 < str.end()) {
            if (*++i == exp[1] && *++i == exp[2]) {
              return true;
            } else {
              throw error("Do you mean 'sin'?", old_i);
            }
          } else {
            throw error("Do you mean 'sin'?", old_i);
          }
        } else {
          i = old_i;
          return false;
        }
      };
      if (hasChar("+*/^", val)) {
        if (!hasChar(")0123456789", last))
          throw error("Only numbers or ')' are allowed before operetions", i);
      }
      if (hasChar("0123456789", val)) {
        if (!hasChar("0123456789", last)) pushOperation(' ');
        res.push_back(val);
      }
      else if (val == '(') {
        st.push(val);
      }
      else if (val == ')') {
        if (!hasChar(")0123456789", last)) {
          if (i == str.end() - 1) {
            throw error("Only numbers or ')' are allowed at the end of expression", str.begin());
          } else {
            throw error("Only numbers or ')' are allowed before ')'", i);
          }
        }
          
        bool flag = true;
        while (!st.empty()) {
          char tmp = get();
          if (tmp != '(') {
            pushOperation(tmp);
          } else {
            flag = false;
            break;
          }
        }
        if (flag) {
          throw error("Expected an expression before ')'", str.begin());
        }
      }
      // + -
      else if (hasChar("+-", val)) {
        //std::cout << "&" << last << "%" << val << "!";
        if (hasChar("_s^(*/+-q", last)) {
          
          if (val == '-') st.push('_');
        } else {
          while (!st.empty() && hasChar("_s^*/+-", (st.top()))) {
            pushOperation(get());
          }
          st.push(val);
        }
      }
      // * /
      else if (hasChar("*/", val)) {
        while (!st.empty() && hasChar("_s^*/", (st.top()))) {
          pushOperation(get());
        }
        st.push(val);
      }
      // ^
      else if (hasChar("^", val)) {
        while (!st.empty() && hasChar("_s", (st.top()))) {
          pushOperation(get());
        }
        st.push(val);
      }
      // sin
      else if (threeLetterFunc("sin")) {
        st.push('s');
      }
      // else error
      else {
        throw error("Unknown expression", i);
      }
      //if (hasChar("-+_*/s^", val) && hasChar("0123456789", last)) {
      //  res.insert(res.end() - 1, ' ');
      //}

      last = val;
    }

    if (!st.empty()) {
      throw error("Expected a ')'", str.end());
    }

    str.erase(str.end() - 1);
    if (display_str) ret += str + " =\n";
    ret += "=" + res + " =\n";
    try {
      double i_res = calc(res);
      ret += "= " + to_string(i_res) + "\n";
    } catch (std::exception er) {
      ret += "= " + string(er.what()) + "\n";
    }
    //ret += 
  } catch (error e) {
    str.erase(str.end() - 1);
    ret += str + '\n';
    string error_pointer;
    //for (auto i = str.begin(); i < e.pos; ++i) error_pointer += " ";
    //ret += error_pointer + "^" + "\n";
    //ret += error_pointer + "|" + "\n";
    ret += e.er + ", at " + std::to_string(e.pos - str.begin() + 1) + "\n";
  }
  return ret;
}
