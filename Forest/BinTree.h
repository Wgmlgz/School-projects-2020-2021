#pragma once
#include "Tree.h"
#include <vector>

template<typename T>
class BinTreeNode : public TreeNode<T> {
public:
  BinTreeNode(T new_data){
      this->branches.resize(2, nullptr);
      this->data = new_data;
  }
  BinTreeNode(){
      this->branches.resize(2, nullptr);
  }
  BinTreeNode* lhs(){ return static_cast<BinTreeNode<T>*>(this->branches[0]); }
  BinTreeNode* rhs(){ return static_cast<BinTreeNode<T>*>(this->branches[1]); }
  void pushLhs(T new_data) { this->pushData(0, new_data); }
  void pushRhs(T new_data) { this->pushData(1, new_data); }
};