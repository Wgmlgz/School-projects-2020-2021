#include <iostream>
//#include "RedBlack.h"
#include <random>
#include "Tree.h"
void add(StrTreeNode* da, int depth = 0) {
  if (depth > 8) return;
  int aa = 3;
  if (depth > 6) aa  = 1;
  for (auto i : range(aa)) {
    da->branches.push_back(new StrTreeNode(rand() % 2 ?"a" : "2"));
  }
  for (auto i : da->branches) {
    add(i, depth + 1);
  }
}
int main() {
  auto tree = StrTreeNode("da");
  add(&tree);
  tree.print();
}