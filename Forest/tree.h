#pragma once
#include <vector>

template<typename T>
class Tree {
public:
  template<typename T>
  class TreeNode {
    T* data_p = nullptr;
    std::vector<TreeNode*> brunches;

   public:
    T* data() { return *data_p;}
    TreeNode* brunch(size_t n) {
      if (n < brunches.size()) {
        return brunches[n];
      } else {
        throw std::exception("can't acces this node");
      }
    }

    TreeNode(T& data, std::vector<TreeNode*> new_brunches = {}) {
      *data_p = data;
      if (new_brunches.size()) brunches = new_brunches;
    }
    ~TreeNode() { delete data_p; }
  };

 private:
  TreeNode* root;
 public:
  Tree() {

  }
};
template <typename T>
class BinaryTree : public Tree<T> {
  class BinaryTreeNode : public Tree::TreeNode<T> {
   public:
    BinaryTreeNode* lhs() { return Tree::TreeNode<T>::brunch(0); }
    BinaryTreeNode* rhs() { return Tree::TreeNode<T>::brunch(1); }
  };
};
template <typename T>
class AVLTree : public BinaryTree<T> {

};