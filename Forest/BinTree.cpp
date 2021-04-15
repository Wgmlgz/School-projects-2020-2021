#pragma once
#include "Tree.h"
#include <vector>

template<typename T>
class BinTreeNode : public TreeNode<T> {
public:
  BinTreeNode(){
      branches.resize(2);
  }
  BinTreeNode* lhs(){
      return this->branches[0];
  }
  BinTreeNode* rhs(){
      return this->branches[1];
  }
};