#include "parcer.h"
#include "polinom.h"
#include "stdafx.h"

int main() {
  Parser parser({
      {"sp", {" "}},
      {"int", {"0123456789"}},
      {"var", {"abcdefghijklmnopqrstuvwxyz", 1}},
      {"pow", {"^"}},
      {"sign", {"+-", 1}},
      {"mult", {"*", 1}},
  }, {
      {"1",  "sp"},
      {"2",  "sign"},
      {"3",  "sp"},
      {"4",  "int"},
      {"5",  "sp"},
      {"6",  "mult"},
      {"7",  "sp"},
      {"8",  "var"},
      {"9",  "sp"},
      {"10", "pow"},
      {"11", "sp"},
      {"12", "int"},
      {"13", "sp"},
      {"14", "mult"},
      {"15", "sp"},
  }, {
      {"0",  {"1", "2", "4", "8"}},
      {"1",  {"2"}},
      {"2",  {"3", "4", "8"}},
      {"3",  {"4"}},
      {"4",  {"5", "6", "8", "2"}},
      {"5",  {"6", "8", "2"}},
      {"6",  {"7", "8"}},
      {"7",  {"8"}},
      {"8",  {"8", "9", "10", "2", "13", "14"}},
      {"9",  {"2", "10"}},
      {"10", {"11", "12"}},
      {"11", {"12"}},
      {"12", {"13", "14"}},
      {"13", {"14", "2"}},
      {"14", {"15", "8"}},
      {"15", {"8"}}
  });
  parser.toWords("666gay^666   +  228-2");
  //parser.toWords("3x*y^2333   ---+++---+  6x66 - 2");
  // SortedList<Polinom::Monom::VarT> vars1{Polinom::Monom::VarT::isLessVar};
  // vars1.insert({ 'x', 2 });

  // SortedList<Polinom::Monom::VarT> vars2{ Polinom::Monom::VarT::isLessVar };
  // vars2.insert({ 'y', 4 });
  // vars2.insert({ 'x', 2 });
  //

  // Polinom t, t2;
  // t.data.insert({ 2, vars1});
  // t.data.insert({ 4, vars2});

  ////List<pair<char, int>> vals;
  ////vals.pushBack({ 'x', 2 });
  ////vals.pushBack({ 'y', 3 });

  ////cout << t.toStr() << ") + (" << t2.toStr() << " = ";
  ////cout << (t + t2).toStr() << endl;
  // char der_ch = 'z';
  // cout << "d/d" << der_ch << "(" << t.toStr() << ") = " <<
  // t.derivative(der_ch).toStr() << endl;
}