#include "BinSearchTree.h"
#include <random>

double dRand(double fMin = 0.0, double fMax = 1.0) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

template<typename T>
class TreapNode : public BinTreeNode<T> {
public:
    using node_ptr = TreapNode<T>*;
    double priority;

    TreapNode<T>*& lhs() { return (TreapNode<T>*&)(this->branches[0]); }
    TreapNode<T>*& rhs() { return (TreapNode<T>*&)(this->branches[1]); }

    TreapNode(T new_data, node_ptr new_left = nullptr, node_ptr new_right = nullptr) {
        this->data = new_data;
        priority = dRand();
        lhs() = new_left;
        rhs() = new_right;
    }
    TreapNode(T new_data, double new_priority, node_ptr new_left = nullptr, node_ptr new_right = nullptr) {
        this->data = new_data;
        priority = new_priority;
        lhs() = new_left;
        rhs() = new_right;
    }
};

template<typename T>
class Treap : public BinSearchTree<T> {
public:
    using node_ptr = TreapNode<T>*;
    node_ptr& getRoot() {
        return (node_ptr&)this->root;
    }
    void split(node_ptr node, T insert_data, node_ptr& lhs, node_ptr& rhs) {
        if (!node)
            lhs = rhs = nullptr;
        else if (insert_data < node->data)
            split(node->lhs(), insert_data, lhs, node->lhs()), rhs = node;
        else
            split(node->rhs(), insert_data, node->rhs(), rhs), lhs = node;
    }
    void merge(node_ptr& t, node_ptr lhs, node_ptr rhs) {
        if (!lhs || !rhs)
            t = lhs ? lhs : rhs;
        else if (lhs->priority > rhs->priority)
            merge(lhs->rhs(), lhs->rhs(), rhs), t = lhs;
        else
            merge(rhs->lhs(), lhs, rhs->lhs()), t = rhs;
    }
    void insert(node_ptr& t, node_ptr it) {
        if (!t)
            t = it;
        else if (it->priority > t->priority)
            split(t, it->data, it->lhs(), it->rhs()), t = it;
        else
            insert(it->data < t->data ? t->lhs() : t->rhs(), it);
    }

    virtual void insert(T insert_data) override {
        node_ptr new_node = new TreapNode<T>(insert_data);
        insert(getRoot(), new_node);
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
        return next(input, getRoot());
    }
};