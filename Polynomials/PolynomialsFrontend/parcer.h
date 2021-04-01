#pragma once
#include "stdafx.h"

class Parser {
 public:
 
  // constants
  const string none_id = "__none__";
  const char end_char = '\0';

  // data
  struct WordTemplate {
    string alphabet;
    // 0 - any, 1..9999 - const, -1...-9999, const+
    int size = 666;
  };
  struct State {
    string word_id;
    vector<string> next;
  };
  struct Word {
    string name;
    string content;
  };
  map<string, WordTemplate> words_dict;
  map<string, State> states;

  // run
  vector<Word> toWords(string str) {
    const bool DEBUG = false;
    str += end_char;
    string state = "0";
    int last_pos = -1;
    int cur_size = 0;
    vector<Word> words;
    for (auto i = str.begin(); i != str.end(); ++i) {
      ++cur_size;
      auto ch = *i;
      auto isIn = [&](string str) -> bool {
        //cout << "isIn call$" << ch << "$" << str << "$" << std::boolalpha <<(str.find(ch) !=
        //    string::npos) << endl;
        return str.find(ch) != string::npos;
      };
      if (isIn(words_dict[states[state].word_id].alphabet) &&
          cur_size < words_dict[states[state].word_id].size) {
        continue;
      } else {
        bool find = false;
        for (size_t i = 0; i < states[state].next.size(); ++i) {
          if (isIn(words_dict[states[states[state].next[i]].word_id].alphabet) ||
              ch == end_char) {
            string wrd = last_pos != -1 ? str.substr(last_pos, cur_size) : "";
            if (states[state].word_id != none_id) {
              words.push_back(Word{states[state].word_id, wrd});
              if (DEBUG) cout << states[state].word_id << "_" << wrd << endl;
            }
            last_pos += cur_size;
            cur_size = 0;
            state = states[state].next[i];
            find = true;
            break;
          }
        }
        string err = "This symbol is't allowed here: '";
        err.push_back(ch);
        err += "'";
        if (find == false) throw exception(err.c_str());
      }
    }
    if (DEBUG) cout << "" << endl;
    return words;
  }

  // setup
  void setWords(vector<pair<string, WordTemplate>> dict) {
    for (auto i : dict) words_dict[i.first] = i.second;
  }
  void setStates(vector<pair<string, string>> dict) {
    for (auto i : dict) states[i.first] = State{i.second};
  }
  void setConnections(vector<pair<string, vector<string>>> dict) {
    for (auto i : dict) states[i.first].next = i.second;
  }
  Parser(){};
  Parser(vector<pair<string, WordTemplate>> dict1,
         vector<pair<string, string>> dict2,
         vector<pair<string, vector<string>>> dict3
  ) {
    words_dict[none_id] = {""}; 
    states["0"] = {none_id};
    setWords(dict1);
    setStates(dict2);
    setConnections(dict3);
  }
};
std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter) {
  std::vector<std::string> strings;

  std::string::size_type pos = 0;
  std::string::size_type prev = 0;
  while ((pos = str.find(delimiter, prev)) != std::string::npos) {
    strings.push_back(str.substr(prev, pos - prev));
    prev = pos + 1;
  }

  // To get the last substring (or only, if delimiter is not found)
  strings.push_back(str.substr(prev));

  return strings;
}