#pragma once
#include "BinTree.h"

template<typename T>
class BinSearchTree {
  using node_ptr = BinTreeNode<T>*;
  node_ptr insert(node_ptr node, T insert_data) {
    if (!node) return new BinTreeNode<T>(insert_data);
    if (insert_data < node->data)
      node->set_lhs(insert(node->get_lhs(), insert_data));
    else
      node->set_rhs(insert(node->get_rhs(), insert_data));
    return node;
  }
public:
  node_ptr root = nullptr;
  node_ptr rrot(node_ptr node) {
    node_ptr tmp = node->get_lhs();
    node->set_lhs(tmp->get_rhs());
    tmp->set_rhs(node);
    return tmp;
  }
  node_ptr lrot(node_ptr node) {
    node_ptr tmp = node->get_rhs();
    node->set_rhs(tmp->get_lhs());
    tmp->set_lhs(node);
    return tmp;
  }
  void insert(T insert_data) {
    root = insert(root, insert_data);
  }
};