#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define range3(name, start, stop, step) for (int name = start; name < stop; name += step)
#define range2(name, start, stop) for (int name = start; name < stop; ++name)
#define range(name, stop) for (int name = 0; name < stop; ++name)

//#define max(a, b) (a > b ? a : b)

#define Tclass template<typename T> class

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::max;