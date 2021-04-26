#pragma once
#include "Wgmlgz.h"
#include "BinSearchTree.h"
#include "BinTree.h"
//#include "Tree.h"
Tclass AVLTreeNode : public BinTreeNode<T>{
public:
  int height = 0;
  AVLTreeNode<T>* get_lhs() { return static_cast<AVLTreeNode<T>*>(BinTreeNode<T>::get_lhs()); }
  AVLTreeNode<T>* get_rhs() { return static_cast<AVLTreeNode<T>*>(BinTreeNode<T>::get_rhs()); }
  void set_lhs(AVLTreeNode<T>* new_ptr) {
    BinTreeNode<T>::set_lhs(static_cast<BinTreeNode<T>*>(new_ptr));
    //this->isEnd = false;
  }
  void set_rhs(AVLTreeNode<T>* new_ptr) {
    BinTreeNode<T>::set_rhs(static_cast<BinTreeNode<T>*>(new_ptr));
    //this->isEnd = false;
  }
  AVLTreeNode(T new_data) {
    BinTreeNode<T>::TreeNode::data = new_data;
  }
};

Tclass AVLTree : public BinSearchTree<T>{
  using node_ptr = AVLTreeNode<T>*;
  int height(node_ptr node) {
    return node ? node->height : 0;
  }
  int bf(node_ptr node) {
    return height(node->get_rhs()) - height(node->get_lhs());
  }
  void fix_height(node_ptr node) {
    node->height = 1 + max(height(node->get_rhs()), height(node->get_lhs()));
  }
  void fix_height(node_ptr a, node_ptr b) {
    fix_height(a); fix_height(b);
  }
  node_ptr rrotAVL(node_ptr node) {
    node_ptr tmp = static_cast<node_ptr>(BinSearchTree<T>::rrot(static_cast<BinTreeNode<T>*>(node)));
    fix_height(node, tmp);
    return tmp;
  }
  node_ptr lrotAVL(node_ptr node) {
    node_ptr tmp = static_cast<node_ptr>(BinSearchTree<T>::lrot(static_cast<BinTreeNode<T>*>(node)));
    fix_height(node, tmp);
    return tmp;
  }
  node_ptr balance(node_ptr node) {
    fix_height(node);
    if (bf(node) == 2) {
      if (bf(node->get_rhs()) < 0)
        node->set_rhs(rrotAVL(node->get_rhs()));
      return lrotAVL(node);
    }
    else if (bf(node) == -2) {
    if (bf(node->get_lhs()) > 0)
      node->set_lhs(lrotAVL(node->get_lhs()));
    return rrotAVL(node);
    }
    return node;
}
node_ptr insert(node_ptr node, T insert_data) {
  if (!node) return new AVLTreeNode<T>(insert_data);
  if (insert_data < node->data)
    node->set_lhs(insert(node->get_lhs(), insert_data));
  else
    node->set_rhs(insert(node->get_rhs(), insert_data));
  return balance(node);
}
public:
  void insert(T insert_data) {
    this->root = this->insert(static_cast<node_ptr>(this->root), insert_data);
  }
};