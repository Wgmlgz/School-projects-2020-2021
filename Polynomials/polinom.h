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
    int mult_val = 1;

    struct VarT {
      char name;
      int power;
      static function<bool(VarT, VarT)> isLessVar;
    };
    SortedList<VarT> vars{VarT::isLessVar};
    static function<bool(Monom, Monom)> isLessMonom;
    static function<bool(char, VarT)> eqName;

    void clear() {
      mult_val = 1;
      vars.clear();
    }
    void insertVar(VarT var) {
      auto find_res = vars.find(var);
      if (find_res)
        find_res->data.power += var.power;
      else
        vars.insert(var);
    }

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
  SortedList<Monom> monoms{Monom::isLessMonom};

  void insetrMonom(Monom monom) {
    auto find_res = monoms.find<SortedList<Monom::VarT>>(
        monom.vars, [](SortedList<Monom::VarT> a, Monom b) -> bool {
          if (a.size == b.vars.size) {
            for (auto i = a.begin, j = b.vars.begin; i != nullptr;
                 i = i->next, j = j->next) {
              if (i->data.name != j->data.name ||
                  i->data.power != j->data.power)
                return false;
            }
          }
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

      monom_str += std::to_string(i_d.mult_val);
      for (auto i = i_d.vars.begin; i != nullptr; i = i->next) {
        // if (!(i == i_d.vars.begin && i_d.mult_val == 1)) monom_str += "*";
        if (i->data.power != 0) {
          monom_str += i->data.name;
          if (i->data.power != 1) {
            monom_str += "^";
            monom_str += std::to_string(i->data.power);
          }
        }
      }
      ret += monom_str;

      if (i != monoms.end) ret += " + ";
    }

    return ret;
  }
  // Polinom(List<Monom> data_) {
  //    data = data_;
  //}
  // Polinom(string str) {

  //}
  Polinom(string str) {
    auto words = Parser({
      {"sp", {" "}},
      {"int", {"0123456789"}},
      {"var", {"abcdefghijklmnopqrstuvwxyz", 1}},
      {"pow", {"^"}},
      {"sign", {"+-", 1}},
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
      {"3", {"4"}},
      {"4", {"5", "6", "8", "2"}},
      {"5", {"6", "8", "2"}},
      {"6", {"7", "8"}},
      {"7", {"8"}},
      {"8", {"8", "9", "10", "2", "13", "14"}},
      {"9", {"2", "10"}},
      {"10", {"11", "12"}},
      {"11", {"12"}},
      {"12", {"13", "14"}},
      {"13", {"14", "2"}},
      {"14", {"15", "8"}},
      {"15", {"8"}}
    }).toWords(str);
    Monom monom;
    for (auto i : words) {
    //for (int i = 0; i < words.size(); ++i) {
      //if (i.name == "sign") {
      //if (i.content == "-") monom
      //}
    }
  }
  Polinom() {}

  // methods
  int valAtPoint(List<pair<char, int>> vals) {
    int sum = 0;
    for (auto i = monoms.begin; i != nullptr; i = i->next)
      sum += i->data.valAtPoint(vals);
    return sum;
  }
  Polinom derivative(char var, int n = 1) {
    if (n == 0) return *this;
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
    if (n == 1) {
      return der;
    } else {
      return der.derivative(var, n - 1);
    }
  }
  Polinom operator+(const Polinom& sec) {
    for (auto i = sec.monoms.begin; i != nullptr; i = i->next) {
      auto find_res = monoms.find<Monom>(i->data, [](Monom a, Monom b) -> bool {
        if (a.vars.size != b.vars.size) return false;
        for (auto i = a.vars.begin, j = b.vars.begin; i != nullptr;
             i = i->next, j = j->next)
          if (i->data.name != j->data.name || i->data.power != i->data.power)
            return false;
        return true;
      });
      if (find_res)
        find_res->data.mult_val += i->data.mult_val;
      else
        monoms.insert(i->data);
    }
    return *this;
  }
};

function<bool(Polinom::Monom::VarT, Polinom::Monom::VarT)>
    Polinom::Monom::VarT::isLessVar =
        [](Polinom::Monom::VarT a, Polinom::Monom::VarT b) -> bool {
  return a.name - 'a' < b.name - 'a';
};

function<bool(Polinom::Monom, Polinom::Monom)> Polinom::Monom::isLessMonom =
    [](Monom a, Monom b) -> bool {
  auto i = a.vars.begin, j = b.vars.begin;
  for (; i != nullptr && j != nullptr; i = i->next, j = j->next) {
    if (i->data.name != j->data.name) {
      if (i->data.power != i->data.power)
        return !(i->data.power < i->data.power);
      else
        return !(i->data.name < j->data.name);
    }
  }
  return !(i == nullptr);
};

function<bool(char, Polinom::Monom::VarT)> Polinom::Monom::eqName =
    [](char a, VarT b) -> bool { return a == b.name; };
