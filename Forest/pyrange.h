#include <vector>

std::vector<int> range(int end){
  if (end < 0) return {};
  auto v = std::vector<int> (end);
  for (int i = 0; i < v.size(); ++i) {
      v[i] = i;
  }
  return v;
}
std::vector<int> range(int start, int end){
  auto v = std::vector<int> (end - start);
  for (int i = 0; i < v.size(); ++i) {
      v[i] = i + start;
  }
  return v;
}