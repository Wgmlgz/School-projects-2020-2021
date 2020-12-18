#include "PostfixExpression.h"

std::string GetPostfix(std::string& str) {
  auto end = str.end();
  auto get_int = [](str_it begin, str_it end) -> int {
    auto i = begin;
	for (; i < end; ++i) {
      if (!(*i >= '0' && *i <= '9')) break;
	}
    if (i == begin) return -1;
    return std::atoi(string(begin, i).c_str());
  };

  int res = get_int(str.begin(), end);
  if (res != -1) {
    return std::to_string(res);
  }
  return "no";
}
void CheckRegularExpression(std::string& str) {

}