#include "BinSearchTree.h"

template<typename T>
class SplayTree : public BinSearchTree<T> {
public:
  using nodeptr = BinTreeNode<T>*;
  nodeptr& getRoot() {
    return (nodeptr&)this->root;
  }
  nodeptr splay(nodeptr node, T data) {
    if (node == nullptr || node->data == data)
      return node;

    if (node->data > data) {
      if (!node->lhs()) return node;
      if (node->lhs()->data > data) {
        node->lhs()->lhs() = splay(node->lhs()->lhs(), data);
        node = this->rrot(node);
      } else if (node->lhs()->data < data) {
        node->lhs()->rhs() = splay(node->lhs()->rhs(), data);
        if (node->lhs()->rhs())
          node->lhs() = this->lrot(node->lhs());
      }

      return !node->lhs() ? node : this->rrot(node);
    } else {
      if (!node->rhs()) return node;

      if (node->rhs()->data > data) {
        node->rhs()->lhs() = splay(node->rhs()->lhs(), data);
        if (node->rhs()->lhs())
          node->rhs() = this->rrot(node->rhs());
      } else if (node->rhs()->data < data) {
        node->rhs()->rhs() = splay(node->rhs()->rhs(), data);
        node = this->lrot(node);
      }

      return !node->rhs() ? node : this->lrot(node);
    }
  }
  virtual void insert(T insert_data) override {
    BinSearchTree<T>::insert(insert_data);
    getRoot() = splay(getRoot(), insert_data);
  }
};