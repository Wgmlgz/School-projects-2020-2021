#pragma once
#include <string>
#include <utility>
#include <vector>

using namespace std;

class WStrings {
 public:
  std::vector<std::string*> strings;
  // inserts
  void Insert(std::string s, int pos = 0);
  void InsertMultiple(std::vector<std::string> strs, int pos = 0);
  void Erase(int pos = 0);

  // modify
  void InsertSubstring(std::string s, int str_pos = 0, int char_pos = 0);
  void ReplaceSymbol(char ch, int str_pos, int char_pos);
  void ReplaceSubstring(std::string old_str, std::string new_str,
                        int begin_index = 0, int end_index = -1);
  // algorithmic
  void RemoveZeroes(int begin_index = 0, int end_index = -1);
  void RemoveAsterisks(int begin_index = 0, int end_index = -1);

  // helper methods
  std::string GetAll();
  std::vector<std::string> Split(std::string str, std::string token);
};