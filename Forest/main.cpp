#include "Wgmlgz.h"
#include "BinSearchTree.h"
#include "AVLTree.h"
#include <random>

int main() {
    auto at = AVLTree<int>();
    auto bt = BinSearchTree<int>();
    for (int i = 0; i < 100; ++i) {
      int t = rand()%10000;
      cout << i << endl;
      //range(h, 30000000);
      bt.insert(i);
      at.insert(i);
    at.root->print(); 
    bt.root->print(); 
    }
}