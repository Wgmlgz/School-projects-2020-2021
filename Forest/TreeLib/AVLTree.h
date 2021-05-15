#pragma once
#include "Wgmlgz.h"
#include "BinSearchTree.h"
#include "BinTree.h"
//#include "Tree.h"
#include <functional>
Tclass AVLTreeNode : public BinTreeNode<T>{
public:
  int height = 1;
  AVLTreeNode<T>*& lhs() { return (AVLTreeNode<T>*&)(this->branches[0]); }
  AVLTreeNode<T>*& rhs() { return (AVLTreeNode<T>*&)(this->branches[1]); }

  AVLTreeNode(T new_data) {
    BinTreeNode<T>::TreeNode::data = new_data;
  }
  AVLTreeNode<T>* clone() {
    vector<TreeNode<T>*> cloned_branches;
    for (auto& i : BinTreeNode<T>::TreeNode::branches) {
      if (i) cloned_branches.push_back(static_cast<AVLTreeNode<T>*>(i)->clone());
      else cloned_branches.push_back(nullptr);
    }
    //--id_counter;
    AVLTreeNode<T>* cloned_node =
      new AVLTreeNode<T>(this->data);
    static_cast<TreeNode<T>*>(cloned_node)->branches = cloned_branches;
    cloned_node->id = BinTreeNode<T>::TreeNode::id;
    cloned_node->height = height;
    return cloned_node;
  }

};

Tclass AVLTree : public BinSearchTree<T>{
  using node_ptr = AVLTreeNode<T>*;
public:
  node_ptr& getRoot() {
    return (node_ptr&)this->root;
  }

  std::function<void(node_ptr node)> on_insert = [](node_ptr) {};
  std::function<void(node_ptr node)> on_balance = [](node_ptr) {};
private:
  int height(node_ptr node) {
    return node ? node->height : 0;
  }
  int bf(node_ptr node) {
    cout << node->data << " " << height(node->rhs()) << " " << height(node->lhs()) << endl;
    return height(node->rhs()) - height(node->lhs());
  }
  void fix_height(node_ptr node) {
    node->height = 1 + max(height(node->rhs()), height(node->lhs()));
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
      on_balance(node);
      if (bf(node->rhs()) < 0)
        node->rhs() = (rrotAVL(node->rhs()));
      return lrotAVL(node);
    } else if (bf(node) == -2) {
      on_balance(node);
      if (bf(node->lhs()) > 0)
        node->lhs() = (lrotAVL(node->lhs()));
      return rrotAVL(node);
    }
    return node;
  }

  node_ptr last_inserted_node;
  node_ptr insert(node_ptr node, T insert_data) {
    if (!node) {
      last_inserted_node = new AVLTreeNode<T>(insert_data);
      return last_inserted_node;
    }
    on_insert(node);
    if (insert_data < node->data)
      node->lhs() = (insert(node->lhs(), insert_data));
    else if (insert_data > node->data)
      node->rhs() = (insert(node->rhs(), insert_data));
    else
      return node;
    return balance(node);
  }
  node_ptr minValueNode(node_ptr node) {
    node_ptr current = node;
    while (current->lhs() != NULL)
        current = current->lhs();
    return current;
  }

  public: node_ptr deleteNode(node_ptr node, T new_data) {
    if (node == NULL) return node;

    if (new_data < node->data)
      node->lhs() = deleteNode(node->lhs(), new_data);
    else if (new_data > node->data)
      node->rhs() = deleteNode(node->rhs(), new_data);
    else {
      if ((node->lhs() == NULL) ||
        (node->rhs() == NULL)) {
        node_ptr temp = node->lhs() ?
          node->lhs() :
          node->rhs();
        if (temp == NULL) {
          temp = node;
          node = NULL;
        } else {
          *node = *temp;
          free(temp);
        }
      } else {
        node_ptr temp = minValueNode(node->rhs());
        node->data = temp->data;
        node->rhs() = (deleteNode(node->rhs(), temp->data));
      }
    }

    if (node == NULL)
    return node;

    node->height = 1 + max(height(node->lhs()), height(node->rhs()));

    int balance = bf(node);

    if (balance > 1 && bf(node->lhs()) >= 0)
      return rrotAVL(node);

    if (balance > 1 && bf(node->lhs()) < 0) {
      node->lhs() = (lrotAVL(node->lhs()));
      return rrotAVL(node);
    }

    if (balance < -1 && bf(node->rhs()) <= 0)
      return lrotAVL(node);

    if (balance < -1 &&
      bf(node->rhs()) > 0) {
      node->rhs() = (rrotAVL(node->rhs()));
      return lrotAVL(node);
    }

    return node;
  }

public:
  virtual void insert(T insert_data) override {
    cout << "avl insert" << endl;
    getRoot() = insert(getRoot(), insert_data);
  }
  node_ptr remove(T remove_data) {
    getRoot() = deleteNode(getRoot(), remove_data);
  }
};