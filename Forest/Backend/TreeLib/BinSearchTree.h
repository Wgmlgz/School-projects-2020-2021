#pragma once
#include "BinTree.h"

template<typename T>
class BinSearchTree {
  using nodeptr = BinTreeNode<T>*;

  nodeptr insert(nodeptr node, T insert_data) {
    if (!node) {
      last_inserted_node = new BinTreeNode<T>(insert_data);
      return last_inserted_node;
    }
    on_insert(node);
    if (insert_data < node->data)
      node->lhs() = insert(node->lhs(), insert_data);
    else if (insert_data > node->data)
      node->rhs() = insert(node->rhs(), insert_data);
    on_insert_place_found();
    return node;
  }

public:
  nodeptr root = nullptr;
  nodeptr last_inserted_node = nullptr;


  std::function<void(nodeptr node)> on_insert = [](nodeptr) {};
  std::function<void()> on_insert_place_found = []() {};

  nodeptr& getRoot() {
    return root;
  }

  nodeptr rrot(nodeptr node) {
    nodeptr tmp = node->lhs();
    node->lhs() = (tmp->rhs());
    tmp->rhs() = (node);
    return tmp;
  }
  nodeptr lrot(nodeptr node) {
    nodeptr tmp = node->rhs();
    node->rhs() = (tmp->lhs());
    tmp->lhs() = (node);
    return tmp;
  }
  virtual void insert(T insert_data) {
    last_inserted_node = nullptr;
    root = insert(root, insert_data);
  }
};