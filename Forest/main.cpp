#include "Wgmlgz.h"
#include "BinSearchTree.h"
#include <random>
int main() {
  while (1) {
    auto bt = BinSearchTree<int>();
    for (int i = 0; i < 100; ++i) {
      int t = rand()%100;
      //range(h, 30000000);
      bt.insert(t);
    }
    bt.root->print();
  }
}