#pragma once
#include "Tree.h"
#include <vector>

template<typename T>
class BinTreeNode : public TreeNode<T> {
public:
  void init() {
    this->branches.resize(2, nullptr);
  }
  BinTreeNode(T new_data) {
    init();
    this->data = new_data;
  }
  BinTreeNode() {
    init();
  }
  BinTreeNode<T>* get_lhs() { return static_cast<BinTreeNode<T>*>(this->branches[0]); }
  BinTreeNode<T>* get_rhs() { return static_cast<BinTreeNode<T>*>(this->branches[1]); }
  void set_lhs(BinTreeNode<T>* new_ptr) {
    this->branches[0] = static_cast<TreeNode<T>*>(new_ptr);
  }
  void set_rhs(BinTreeNode<T>* new_ptr) {
    this->branches[1] = static_cast<TreeNode<T>*>(new_ptr);
  }

  void pushLhs(T new_data) { this->pushData(0, new_data); }
  void pushRhs(T new_data) { this->pushData(1, new_data); }


  // stuff
  void reverse() {
    std::swap(this->branches[0], this->branches[1]);
    if (get_lhs()) get_lhs()->reverse();
    if (get_rhs()) get_rhs()->reverse();
  }
};