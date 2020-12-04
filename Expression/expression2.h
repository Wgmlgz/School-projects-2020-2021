#pragma once
#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <windows.h>
#include <conio.h>

// help me pls
using str_it = std::string::iterator;
using vec = std::vector<bool>;
using string = std::string;
using pair_it = std::pair<str_it, str_it>;
using pair_pair_it = std::pair<pair_it, pair_it>;


void CoutColor(string s, int color);


// custom error type
struct error {
  string er;
  str_it pos;
  error(string s, str_it i) {
    er = s;
    pos = i;
  }
};

bool IsStartEqual(str_it start, str_it end, string s);
void CheckBrackets(str_it start, str_it end);

vec GetOperands(str_it start, str_it end);

void PrintV(vec v);
bool CheckOR(vec v);
bool CheckAND(vec v);
bool CheckNOT(vec v);

bool ExpressinOR(str_it start, str_it end);
bool ExpressinAND(str_it start, str_it end);
bool ExpressinNOT(str_it start, str_it end);

bool CheckExpression(str_it start, str_it end);
void TryExpression(string s);