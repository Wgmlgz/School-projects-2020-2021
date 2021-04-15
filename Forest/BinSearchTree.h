#pragma once
#include "BinTree.h"

template<typename T>
class BinSearchTree {
  void insertRec(BinTreeNode<T>* node, T insert_data) {
    if (insert_data < node->data) {
      if (node->lhs())
        insertRec(node->lhs(), insert_data);
      else
        node->pushLhs(insert_data);
    } else {
      if (node->rhs())
        insertRec(node->rhs(), insert_data);
      else
        node->pushRhs(insert_data);
    }
  }
public:
  BinTreeNode<T>* root;
 
  void insert(T insert_data) {
    if (root)
      this->insertRec(root, insert_data);
    else
      root = new BinTreeNode<T>(insert_data);  
  }

  void remove() {

  }
};