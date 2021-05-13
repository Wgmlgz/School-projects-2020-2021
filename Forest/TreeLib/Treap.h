#include "BinSearchTree.h"
#include <random>

double dRand(double fMin = 0.0, double fMax = 1.0) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template<typename T>
class TreapNode : public BinTreeNode<T> {
public:
    TreapNode<T>* get_lhs() { return static_cast<TreapNode<T>*>(BinTreeNode<T>::get_lhs()); }
    TreapNode<T>* get_rhs() { return static_cast<TreapNode<T>*>(BinTreeNode<T>::get_rhs()); }
    void set_lhs(TreapNode<T>* new_ptr) {
        BinTreeNode<T>::set_lhs(static_cast<BinTreeNode<T>*>(new_ptr));
    }
    void set_rhs(TreapNode<T>* new_ptr) {
        BinTreeNode<T>::set_rhs(static_cast<BinTreeNode<T>*>(new_ptr));
    }
    using node_ptr = TreapNode<T>*;
    double priority;
    TreapNode(T new_data, node_ptr new_left = nullptr, node_ptr new_right = nullptr) {
        BinTreeNode<T>::TreeNode::data = new_data;
        priority = dRand();
        BinTreeNode<T>::set_lhs(new_left);
        BinTreeNode<T>::set_rhs(new_right);
    }
    TreapNode(T new_data, double new_priority, node_ptr new_left = nullptr, node_ptr new_right = nullptr) {
        BinTreeNode<T>::TreeNode::data = new_data;
        priority = new_priority;
        BinTreeNode<T>::set_lhs(new_left);
        BinTreeNode<T>::set_rhs(new_right);
    }
};

template<typename T>
class Treap : public BinSearchTree<T> {
public:
    using node_ptr = TreapNode<T>*;
    node_ptr root = nullptr;
    void split(node_ptr node, T x, node_ptr& L, node_ptr& R) {
        node_ptr newTree = nullptr;
        if (node->data <= x) {
            if (node->get_rhs() == nullptr)
                R = nullptr;
            else
                split(node->get_rhs(), x, newTree, R);
            L = new TreapNode<T>(node->data, node->priority, node->get_lhs(), newTree);
        } else {
            if (node->get_lhs() == nullptr)
                L = nullptr;
            else
                split(node->get_lhs(), x, L, newTree);
            R = new TreapNode<T>(node->data, node->priority, newTree, node->get_rhs());
        }
    }
    node_ptr Merge(node_ptr L, node_ptr R) {
        if (L == nullptr) return R;
        if (R == nullptr) return L;

        if (L->priority > R->priority) {
            auto newR = Merge(L->get_rhs(), R);
            return new TreapNode<T>(L->data, L->priority, L->get_lhs(), newR);
        } else {
            auto newL = Merge(L, R->get_lhs());
            return new TreapNode<T>(R->data, R->priority, newL, R->get_rhs());
        }
    }
    node_ptr insert(node_ptr node, T insert_data) {
        node_ptr l, r;
        split(node, insert_data, l, r);
        node_ptr m = new TreapNode<T>(insert_data);
        return Merge(Merge(l, m), r);
    }
    virtual void insert(T insert_data) override {
        cout << "treap insert" << endl;
        if (!this->root) {
            this->root = new TreapNode<T>(insert_data);
            return;
        }
        this->root = insert(root, insert_data);
    }
    virtual node_ptr getRoot() override {
        return root;
    }
    node_ptr next(T input, node_ptr node) {
        if (!node)
            return nullptr;
        if (node->data < input)
            return nullptr;
        auto t = next(input, node->get_lhs());
        return t ? t : node;
    }
    node_ptr next(T input) {
        return next(input, root);
    }
};