#pragma once
#include <stack>
#include <string>

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
string ConvertToPostfix(string str) {
  string res;
  try {
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
      PrintStack(st);
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

      if (val >= '0' && val <= '9') {
        res.push_back(val);
      } else if (val == '(') {
        st.push(val);
      } else if (val == ')') {
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

      last = val;
    }
  } catch (error er) {
    
  }
  return res;
}
