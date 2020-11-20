#include "Backend.h"

// inserts
void WStrings::Insert(std::string s, int pos) {
  if (pos == -1) pos = 0;
  if (pos >= strings.size()) {
    strings.resize(pos, new std::string("$"));
  }
  strings.insert(strings.begin() + pos, new std::string(s));
}
void WStrings::InsertMultiple(std::vector<std::string> strs, int pos) {
  if (pos >= strings.size()) {
    strings.resize(pos, new std::string("$"));
    for (int i = 0; i < strs.size(); ++i) {
      strings.push_back(new std::string(strs[i]));
    }
  } else {
    for (int i = 0; i < strs.size(); ++i) {
      strings.insert(strings.begin() + pos + i, new std::string(strs[i]));
    }
  }
}
void WStrings::Erase(int pos) {
  strings.erase(strings.begin() + pos);
  // strings.
}

// modify
void WStrings::InsertSubstring(std::string s, int str_pos,
                               int char_pos) {
  strings[str_pos]->insert(char_pos, s);
}
void WStrings::ReplaceSymbol(char ch, int str_pos, int char_pos) {
  (*strings[str_pos])[char_pos] = ch;
}
void WStrings::ReplaceSubstring(std::string old_str, std::string new_str,
                                int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  for (int i = begin_index; i < end_index; ++i) {
    size_t pos = strings[i]->find(old_str);
    while (pos != std::string::npos) {
      strings[i]->replace(pos, old_str.size(), new_str);
      pos = strings[i]->find(old_str, pos + new_str.size());
    }

    // int index = strings[i]->find(old_str);
    // if (index == string::npos) continue;
    // strings[i]->replace(index, new_str.size(), new_str);
  }
}

// algorithmic
void WStrings::RemoveZeroes(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  for (int i = begin_index; i < end_index; ++i) {
    for (int index = strings[i]->find("0"); index != -1;
         index = strings[i]->find("0")) {
      if (index != strings[i]->size() - 1) {
        if (std::string("0123456789").find((*strings[i])[index + 1]) != -1) {
          strings[i]->erase(strings[i]->begin() + index);
        } else
          break;
      } else
        break;
    }
  }
}
void WStrings::RemoveAsterisks(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  for (int i = begin_index; i < end_index; ++i) {
    for (int j = 0; j < strings[i]->size(); ++j) {
      if (strings[i]->at(j) == '*') {
        int k = j;
        for (; strings[i]->at(j) == '*' && j < strings[i]->size() - 1; ++j)
          continue;
        std::string tmp;
        if (j == k) break;
        for (int h = 0; h < (j - k + 1) / 2; ++h) tmp += "+";
        strings[i]->replace(strings[i]->begin() + k,
                            strings[i]->begin() + j + 1, tmp);
        break;
      }
    }
  }
}

// helper methods
std::string WStrings::GetAll() {
  std::string result;
  for (auto i : strings) result += "" + *i + '\n';
  return result;
}
std::vector<std::string> WStrings::Split(std::string str, std::string token) {
  std::vector<std::string> result;
  while (str.size()) {
    int index = str.find(token);
    if (index != std::string::npos) {
      result.push_back(str.substr(0, index));
      str = str.substr(index + token.size());
      if (str.size() == 0) result.push_back(str);
    } else {
      result.push_back(str);
      str = "";
    }
  }
  return result;
}
