#pragma once
#include <stack>
#include <string>
#include <math.h>

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
string ConvertToPostfix(string str) {
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
    char last = '\0';
    for (auto i = str.begin(); i < str.end(); ++i) {
      //PrintStack(st);
      char val = *i;
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
        if (hasChar("0123456789", last))
          throw error("Sorry, but only numbers < 10", i);
        res.push_back(val);
      } else if (val == '(') {
        st.push(val);
      } else if (val == ')') {
        if (!hasChar(")0123456789", last)) {
          if (i == str.end() - 1) {
            throw error("Only numbers or ')' are allowed at the end of expression", i);
          } else {
            throw error("Only numbers or ')' are allowed before ')'", i);
          }
        }
          
        bool flag = true;
        while (!st.empty()) {
          char tmp = get();
          if (tmp != '(') {
            res.push_back(tmp);
          } else {
            flag = false;
            break;
          }
        }
        if (flag) {
          throw error("Expected an expression before ')'", i);
        }
      }
      // + -
      else if (hasChar("+-", val)) {
        if (hasChar("^(*/+-\0", last)) {
          if (val == '-') st.push('_');
        } else {
          while (!st.empty() && hasChar("s^*/+-", (st.top()))) {
            res.push_back(get());
          }
          st.push(val);
        }
      }
      // * /
      else if (hasChar("*/", val)) {
        while (!st.empty() && hasChar("s^*/", (st.top()))) {
          res.push_back(get());
        }
        st.push(val);
      }
      // ^
      else if (hasChar("^", val)) {
        while (!st.empty() && hasChar("s", (st.top()))) {
          res.push_back(get());
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
      //if (st.empty()) {
      //  if (i == str.end() - 1) {
      //    throw error(
      //        "You probably missed something here",
      //        i);
      //  } else {
      //    throw error(
      //        "Extra ')' found (maybe remove it or add '(' someware before?)",
      //        i);
      //  }
      //}
      last = val;
    }
    if (!st.empty()) {
      throw error("Expected a '('", str.end());
    }

    str.erase(str.end() - 1);
    ret += str + " =\n";
    ret += "= " + res + " =\n";
    try {
      int i_res = CalculatePostfix(res);
      ret += "= " + to_string(i_res) + "\n";
    } catch (...) {
      ret += "= Bruh error while calculation(\n";
    }
    //ret += 
  } catch (error e) {
    str.erase(str.end() - 1);
    ret += str + '\n';
    string error_pointer;
    for (auto i = str.begin(); i < e.pos; ++i) error_pointer += " ";
    ret += error_pointer + "^" + "\n";
    //ret += error_pointer + "|" + "\n";
    ret += e.er + ", at " + std::to_string(e.pos - str.begin() + 1) + "\n";
  }
  return ret;
}
