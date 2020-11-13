#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class WStrings {
  vector<string*> strings;

 public:
  // inserts
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

   // modify
  void InsertSubstring(string s, size_t str_pos, size_t char_pos){
    strings[str_pos]->insert(char_pos, s);
  }
  void ReplaceSymbol(char ch, size_t str_pos, size_t char_pos) {
       (*strings[str_pos])[char_pos] = ch; 
  }
  void ReplaceSubstring(string old_str, string new_str, size_t begin_index = 0, size_t end_index = -1) {
    if (end_index == -1) end_index = strings.size();
    for (int i = begin_index; i < end_index; ++i) {
      size_t index = strings[i]->find(old_str);
      if (index == string::npos) continue;
      strings[i]->replace(index, new_str.size(), new_str);
    }
  }

  // algorithmic
  void RemoveZeroes(size_t begin_index = 0, size_t end_index = -1) {
    if (end_index == -1) end_index = strings.size();
    for (int i = begin_index; i < end_index; ++i) {
      for (size_t index = strings[i]->find("0"); index != -1; index = strings[i]->find("0")) {
        if (index != strings[i]->size() - 1) {
          if (string("0123456789").find((*strings[i])[index + 1]) != -1) {
            strings[i]->erase(strings[i]->begin() + index);
          } else break;
        } else break;
      }
    }
  }
  void RemoveAsterisks(size_t begin_index = 0, size_t end_index = -1) {
    if (end_index == -1) end_index = strings.size();
    for (int i = begin_index; i < end_index; ++i) {
      cout << i << endl;
      for (int j = 0; j < strings[i]->size(); ++j) {
        if (strings[i]->at(j) == '*') {
          size_t k = j;
          for (; strings[i]->at(j) == '*' && 
              j < strings[i]->size() -1; ++j) continue;
          string tmp;
          if (j == k) break;
          for (int h = 0; h < (j - k + 1) / 2; ++h) tmp += "+";
          strings[i]->replace(strings[i]->begin() + k, strings[i]->begin() + j + 1, tmp);
          break;
        }
      }
    }
  }
  string GetAll() {
    string result;
    for (auto i : strings) {
      result += "" + *i + '\n';
    }
    return result;
  }
};
int main() {
  WStrings v;

  //v.Insert("**");

  v.Insert("*");
  v.Insert("**");
  v.Insert("***");
  v.Insert("****");
  v.Insert("*****");
  v.Insert("******");
  v.Insert("*******");
  v.Insert("********");
  
  //v.Insert("pizd", 10);
  /*v.InsertMultiple({"wasd", "frog", "zhabka"}, 0);
  v.Erase(1);
  v.InsertSubstring("ass", 0, 1);
  v.ReplaceSymbol('(', 0, 0);
  *///v.ReplaceSubstring("da", "dick");
  v.RemoveAsterisks();
  cout << v.GetAll() << "end";
}