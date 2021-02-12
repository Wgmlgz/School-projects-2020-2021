#include <iostream>
#include <vector>
#include "converter.h"

int main() {
  Table table(4, 666);
  //std::cout << table.true_ans;
  std::cout << table.genAns();
  table.printAns();
}