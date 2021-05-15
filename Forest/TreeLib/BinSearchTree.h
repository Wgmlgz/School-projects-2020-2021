#pragma once
#include "BinTree.h"

template<typename T>
class BinSearchTree {
  using node_ptr = BinTreeNode<T>*;
  node_ptr last_inserted_node = nullptr;

  node_ptr insert(node_ptr node, T insert_data) {
    if (!node) {
      last_inserted_node = new BinTreeNode<T>(insert_data);
      return last_inserted_node;
    }
    if (insert_data < node->data)
      node->lhs() = insert(node->lhs(), insert_data);
    else
      node->rhs() = insert(node->rhs(), insert_data);
    return node;
  }

public:
  node_ptr root = nullptr;
  node_ptr& getRoot() {
    return root;
  }

  node_ptr rrot(node_ptr node) {
    node_ptr tmp = node->lhs();
    node->lhs() = (tmp->rhs());
    tmp->rhs() = (node);
    return tmp;
  }
  node_ptr lrot(node_ptr node) {
    node_ptr tmp = node->rhs();
    node->rhs() = (tmp->lhs());
    tmp->lhs() = (node);
    return tmp;
  }
  virtual void insert(T insert_data) {
    cout << "Bin insert" << endl;
    root = insert(root, insert_data);
  }
};