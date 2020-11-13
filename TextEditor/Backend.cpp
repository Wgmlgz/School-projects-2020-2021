#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class WStrings {
  vector<string*> strings;

 public:
  void Insert(string s, size_t pos = 0) {
    if (pos >= strings.size()) {
      strings.resize(pos, new string("$"));
    }
    strings.insert(strings.begin() + pos, new string(s));
  }
  void InsertMultiple(vector<string> strs, size_t pos = 0) {
    if (pos >= strings.size()) {
      strings.resize(pos, new string("$"));
      for (int i = 0; i < strs.size(); ++i) {
        strings.push_back(new string(strs[i]));
      }
    } else {
      for (int i = 0; i < strs.size(); ++i) {
        strings.insert(strings.begin() + pos + i, new string(strs[i]));
      }
    }
  }
  void Erase(size_t pos = 0) {
    strings.erase(strings.begin() + pos);
    //strings.
  }
  string GetAll() {
    string result;
    for (auto i : strings) {
      result += " " + *i + '\n';
    }
    return result;
  }
};
int main() {
  WStrings v;
  v.Insert("da");
  v.Insert("pizd", 10);
  v.InsertMultiple({"wasd", "frog", "zhabka"}, 0);
  v.Erase(1);
  cout << v.GetAll();
}