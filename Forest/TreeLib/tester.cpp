#include "TreeLib.h"
#include <fstream>
#include "TreePrinterASCII.h"
using node_ptr = AVLTreeNode<int>*;

AVLTree<int> test;

int main() {
  srand(23442);

  test.insert(666);
  range(i, 10) {
      cout << "%" << i << endl;
    test.insert(rand()% 10);
    printASCII(test.root);
  }
  test.remove(5);
  printASCII(test.root);  
}
