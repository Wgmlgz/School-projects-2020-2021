#include "TreeLib.h"
#include <fstream>
#include "TreePrinterASCII.h"
#include "TreePrinterJSON.h"
#include "RBTree.h"
using nodeptr = AVLTreeNode<int>*;

AVLTree<int> test;


int main() {
  RBTree<int> bst;
  bst.insert(8);
  printASCII(bst.getRoot());
  bst.insert(18);
  printASCII(bst.getRoot());
  bst.insert(5);
  printASCII(bst.getRoot());
  bst.insert(15);
  printASCII(bst.getRoot());
  bst.insert(17);
  printASCII(bst.getRoot());
  bst.insert(25);
  printASCII(bst.getRoot());
  bst.insert(40);
  printASCII(bst.getRoot());
  bst.insert(80);
  printASCII(bst.getRoot());
  bst.deleteNode(25);
  printASCII(bst.getRoot());
  return 0;
}
