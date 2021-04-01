#pragma once
#include "list.h"
#include "parcer.h"
#include "stdafx.h"

int powInt(int x, int n) {
  int y = 1;
  for (int i = 0; i < n; i++) y *= x;
  return y;
}

class Polinom {
 public:
  class Monom {
   public:
    int64_t mult_val = 1;
    static function<bool(Monom, Monom)> isLessMonom;
    struct VarT {
      char name;
      int power;
      bool operator==(const VarT& var) {
        return this->name == var.name && this->power == var.power;
      }
      static function<bool(VarT, VarT)> isLessVar;
    };
    SortedList<VarT> vars{VarT::isLessVar};
    
    static function<bool(char, VarT)> eqName;

    void clear() {
      mult_val = 1;
      vars.clear();
    }
    VarT* insertVar(VarT var) {
      auto find_res = vars.find<char>(var.name, [](char ch, VarT var) -> bool {return ch == var.name;});
      if (find_res)
        find_res->data.power += var.power;
      else
        find_res = vars.insert(var);
      return &find_res->data;
    }
    //Monom operator*(const Monom& sec) {
    //  return Monom{2};
    //  Monom res = Monom {mult_val, vars.copy()};
    //  return res;
    //  res.mult_val *= sec.mult_val;
    //  for (auto i = sec.vars.begin; i != nullptr; i = i->next) {
    //    if (res.vars.find(i->data))
    //      res.vars.find(i->data)->data.power += i->data.power;
    //    else
    //      res.vars.insert(i->data);
    //  }
    //  return res;
    //}
    int valAtPoint(List<pair<char, int>> vals) {
      int control_sum = 0;
      int mult = 1;
      for (auto i = vals.begin; i != nullptr; i = i->next) {
        auto find_res = vars.find<char>(i->data.first, eqName);
        if (find_res) {
          mult *= powInt(i->data.second, find_res->data.power);
          ++control_sum;
        }
      }
      if (control_sum > vars.size)
        throw std::exception("Too many variables found (maybe some copies)");
      if (control_sum < vars.size)
        throw std::exception("Not all variables were initialized");
      return mult_val * mult;
    }
  };
  static function<bool(Monom, Monom)> isLessMonom;
  SortedList<Monom> monoms{isLessMonom};

  void insetrMonom(Monom monom) {
    if (monom.mult_val == 0) {
      monom.vars.clear();
    }
    auto find_res = monoms.find<SortedList<Monom::VarT>>(
        monom.vars, [](SortedList<Monom::VarT> a, Monom b) -> bool {
          if (a.size == b.vars.size) {
            for (auto i = a.begin, j = b.vars.begin; i != nullptr;
                i = i->next, j = j->next) {
              if (i->data.name != j->data.name ||
                  i->data.power != j->data.power)
                return false;
            }
            return true;
          }
          return false;
        });
    if (find_res)
      find_res->data.mult_val += monom.mult_val;
    else
      monoms.insert(monom);
  }
  void fromStr(string str) {}
  string toStr() {
    if (monoms.size == 0) return "0";
    string ret;
    for (auto i = monoms.begin; i != nullptr; i = i->next) {
      auto i_d = i->data;
      string monom_str;
      if (i_d.mult_val < 0 || i != monoms.begin) {
        //monom_str += " ";
        monom_str += (i_d.mult_val > 0 ? " + " : " ");
        //monom_str += " ";
      }
      if (i_d.vars.size == 0 || i_d.mult_val != 1)
        monom_str += std::to_string(i_d.mult_val);
      for (auto i = i_d.vars.begin; i != nullptr; i = i->next) {
        if (i->data.power != 0) {
          monom_str += i->data.name;
          if (i->data.power != 1) {
            monom_str += "^";
            monom_str += std::to_string(i->data.power);
          }
        }
      }
      ret += monom_str;
    }
    return ret;
  }

  Polinom(string str) {
    try {
      auto words = Parser({
        {"sp", {" "}},
        {"int", {"0123456789"}},
        {"var", {"abcdefghijklmnopqrstuvwxyz", 1}},
        {"pow", {"^", 1}},
        {"sign", {"-+", 1}},
        {"mult", {"*", 1}},
      }, {
        {"1", "sp"},
        {"2", "sign"},
        {"3", "sp"},
        {"4", "int"},
        {"5", "sp"},
        {"6", "mult"},
        {"7", "sp"},
        {"8", "var"},
        {"9", "sp"},
        {"10", "pow"},
        {"11", "sp"},
        {"12", "int"},
        {"13", "sp"},
        {"14", "mult"},
        {"15", "sp"},
      }, {
        {"0", {"1", "2", "4", "8"}},
        {"1", {"2"}},
        {"2", {"3", "4", "8"}},
        {"3", {"4", "8"}},
        {"4", {"5", "6", "8", "2"}},
        {"5", {"6", "8", "2"}},
        {"6", {"7", "8"}},
        {"7", {"8"}},
        {"8", {"8", "9", "10", "2", "13", "14"}},
        {"9", {"2", "10"}},
        {"10", {"11", "12"}},
        {"11", {"12"}},
        {"12", {"13", "14", "2", "8"}},
        {"13", {"14", "2"}},
        {"14", {"15", "8"}},
        {"15", {"8"}}
      }).toWords(str);
      words.push_back({"sign", "+"});
      Monom monom;
      bool start = true;
      Monom::VarT* last_var = nullptr;
      // for (auto i : words) {
      for (int i = 0; i < words.size(); ++i) {
        if (words[i].name == "sign") {
          if (!start) insetrMonom(monom);
          start = false;
          last_var = nullptr;
          monom.clear();
          if (words[i].content == "-") monom.mult_val = -1;
        } else if (words[i].name == "int") {
          start = false;
          if (last_var)
            last_var->power = stoi(words[i].content);
          else
            monom.mult_val *= stoi(words[i].content);
        } else if (words[i].name == "var") {
          start = false;
          last_var = monom.insertVar({words[i].content[0], 1});
        } 
      }
    } catch (exception err) {
      cout << err.what() << endl;
    }
  }
  Polinom copy() {
    return Polinom(toStr()); // this is cursed
  }
  Polinom() {}

  // methods
  bool isNull() { return monoms.size == 0; }
  int valAtPoint(List<pair<char, int>> vals) {
    int sum = 0;
    for (auto i = monoms.begin; i != nullptr; i = i->next)
      sum += i->data.valAtPoint(vals);
    return sum;
  }
  Polinom derivative(char var, int n = 1) {
    if (n == 0) return copy();
    if (n < 0) throw std::exception("Bruh, bro that's cringe(((((");
    Polinom der;

    for (auto i = monoms.begin; i != nullptr; i = i->next) {
      auto i_d = i->data;
      auto vars_copy = i_d.vars.copy();
      auto find_res = vars_copy.find<char>(var, Polinom::Monom::eqName);
      if (find_res) {
        auto mult_val = i_d.mult_val * find_res->data.power;
        if (find_res->data.power == 1)
          vars_copy.remove(find_res);
        else
          --find_res->data.power;
        der.monoms.insert({mult_val, vars_copy});
      }
    }
    return der.derivative(var, n - 1);
  }
  Polinom operator+(const Polinom& sec) {
    Polinom res = copy();
    for (auto i = sec.monoms.begin; i != nullptr; i = i->next)
      res.insetrMonom(i->data);
    return res.copy();
  }
  Polinom operator*(const Polinom& sec) {
    Polinom res;

    for (auto i = monoms.begin; i != nullptr; i = i->next) {
      for (auto j = sec.monoms.begin; j != nullptr; j = j->next) {
        Monom tmp;
        tmp.mult_val = i->data.mult_val * j->data.mult_val;
        for (auto k = i->data.vars.begin; k != nullptr; k = k->next)
          tmp.insertVar(k->data);
        for (auto k = j->data.vars.begin; k != nullptr; k = k->next)
          tmp.insertVar(k->data);
        res.insetrMonom(tmp);
      }
    }
    return res; 
    //return res.copy();
  }
  string intRoots() {
    vector<int> res;
    if (monoms.size != 0 && monoms.end->data.vars.size == 0) {
      int free = monoms.end->data.mult_val;
      if (free < 0) free = -free;
      for (int i = -free; i <= free; ++i) {
        if (i == 0 || free % i == 0) {
          List<pair<char, int>> vals;
          for (char j = 'a'; j <= 'z'; ++j) vals.pushBack({j, i});
          if (valAtPoint(vals) == 0) res.push_back(i);
        }
      }
    } else {
      res.push_back(0);
    }
    string sres;
    for (auto i : res) sres += std::to_string(i) + " ";
    return sres;
  }
};

function<bool(Polinom::Monom::VarT, Polinom::Monom::VarT)>
    Polinom::Monom::VarT::isLessVar =
        [](Polinom::Monom::VarT a, Polinom::Monom::VarT b) -> bool {
  return a.name > b.name;
};

function<bool(Polinom::Monom, Polinom::Monom)> Polinom::isLessMonom =
    [&](Polinom::Monom a, Polinom::Monom b) -> bool {
  auto i = a.vars.begin, j = b.vars.begin;
  for (; i != nullptr && j != nullptr; i = i->next, j = j->next) {
    if (i->data.name != j->data.name)
      return i->data.name > j->data.name;
    else if (i->data.power != j->data.power)
      return i->data.power < j->data.power;
  }
  return i == nullptr;
};

function<bool(char, Polinom::Monom::VarT)> Polinom::Monom::eqName =
    [](char a, VarT b) -> bool { return a == b.name; };
