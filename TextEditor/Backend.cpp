#include "Backend.h"

// inserts
void WgzStrings::Insert(std::string s, int pos) {
  if (pos == -1) pos = 0;
  if (pos >= strings.size()) strings.resize(pos, new std::string("$"));
  strings.insert(strings.begin() + pos, new std::string(s));
}
void WgzStrings::InsertMultiple(std::vector<std::string> strs, int pos) {
  if (pos >= strings.size()) {
    strings.resize(pos, new std::string("$"));
    for (int i = 0; i < strs.size(); ++i)
      strings.push_back(new std::string(strs[i]));
  } else {
    for (int i = 0; i < strs.size(); ++i)
      strings.insert(strings.begin() + pos + i, new std::string(strs[i]));
  }
}
void WgzStrings::Erase(int pos) {
  --pos;
  strings.erase(strings.begin() + pos);
}

// modify
void WgzStrings::InsertSubstring(std::string s, int str_pos, int char_pos) {
  --str_pos;
  --char_pos;
  strings[str_pos]->insert(char_pos, s);
}
void WgzStrings::ReplaceSymbol(char ch, int str_pos, int char_pos) {
  --str_pos;
  --char_pos;
  (*strings[str_pos])[char_pos] = ch;
}
void WgzStrings::ReplaceSubstring(std::string old_str, std::string new_str, int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  else --end_index;
  --begin_index;
  for (int i = begin_index; i < end_index; ++i) {
    size_t pos = strings[i]->find(old_str);
    while (pos != std::string::npos) {
      strings[i]->replace(pos, old_str.size(), new_str);
      pos = strings[i]->find(old_str, pos + new_str.size());
    }
  }
}

// algorithmic
void WgzStrings::RemoveZeroes(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  else --end_index;
  --begin_index;
  for (int i = begin_index; i < end_index; ++i) {
    for (int index = 0; index < strings[i]->size() - 1; ++index) {
      if ((*strings[i])[index] == '0') {
        if (std::string("0123456789").find((*strings[i])[index + 1]) != -1) {
          if (index == 0) {
            strings[i]->erase(strings[i]->begin() + index);
            --index;
          }
          else if (std::string("0123456789").find((*strings[i])[index - 1]) == -1) {
            strings[i]->erase(strings[i]->begin() + index);
            --index;
          }
        }
      }
    }
  }
}
void WgzStrings::RemoveAsterisks(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  else --end_index;
  --begin_index;
  for (int i = begin_index; i < end_index; ++i) {
    *strings[i] += "6";
    for (int j = 0; j < strings[i]->size(); ++j) {
      if (strings[i]->at(j) == '*') {
        int k = j;
        for (; strings[i]->at(j) == '*' && j < strings[i]->size() - 1; ++j) continue;
        if (j == k + 1) continue;

        std::string tmp;
        for (int h = 0; h < (j - k) / 2; ++h) tmp += "+";
        strings[i]->replace(strings[i]->begin() + k,
                            strings[i]->begin() + j, tmp);
        j = 0;
      }
    }
    strings[i]->erase(--strings[i]->end());
  }
}
void WgzStrings::RemoveBracketsContent(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  else--end_index;
  --begin_index;
  for (auto i = strings.begin() + begin_index;
       i < strings.begin() + end_index; ++i) {
    for (auto j = (*i)->begin(); j < (*i)->end(); ++j) {
      if (*j == '{') {
        for (; *j != '}'; (*i)->erase(j)) continue;
        (*i)->erase(j);
      }
    }
  }
}
void WgzStrings::RemoveDigitsWithIncreasingValues(int begin_index, int end_index) {
  if (end_index == -1) end_index = strings.size();
  else --end_index;
  --begin_index;
  for (auto i = strings.begin() + begin_index; i < strings.begin() + end_index;
       ++i) {
    for (auto j = (*i)->begin(); j < (*i)->end(); ++j) {
      auto IsDigit = [](char ch) -> bool {
        return std::string("0123456789").find(ch) != -1;
      };
      if (IsDigit(*j)) {
        auto k = j;
        for (;;)
          ;
      }
    }
  }
}

// helper methods
std::string WgzStrings::GetAll() {
  std::string result;
  for (auto i : strings) result += "" + *i + '\n';
  return result;
}
std::vector<std::string> WgzStrings::Split(std::string str, std::string token) {
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
