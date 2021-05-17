#pragma once
#include "AVLTree.h"
#include "TreePrinterJSON.h"
#include "TreePrinterASCII.h"
#include "Wgmlgz.h"
#include <functional>

template<typename T>
class TreeHandler {
public:
  string display_name = "I'm a defaut tree(";
  BinSearchTree<T>* tree_ptr = nullptr;
  vector<string> json_states_stack = { "{\"666\":{\"c\":\"null\",\"clr\":\"#44475a\",\"x\":0,\"y\":0,\"X\":0,\"Y\":0}}" };
  vector<string> json_lines_stack = { "" };
  virtual void insert(T insert_data) {
    tree_ptr->insert(insert_data);
  }
  void write(TreeNode<int>* a, TreeNode<int>* b, vector<cupData<int>> acap, vector<cupData<int>> bcap) {
    static int frame_n = 0;
    auto stringify_res = toJsonWithCaps(a, b, acap, bcap);

    json_states_stack.push_back(stringify_res.first);
    json_lines_stack.push_back(stringify_res.second);

    //cout << stringify_res.first << endl;

    ++frame_n;
  }
};

template<typename T>
class AVLTreeHandler : public TreeHandler<T> {
public:
  vector<int> ins_stack;
  vector<pair<TreeNode<T>*, int>> fix_stack;
  using nodeptr = AVLTreeNode<T>*;
  TreeNode<T>* insert_place_found_clone = nullptr;

  void on_insert(nodeptr node) {
    ins_stack.push_back(node->id);

    cout << "on_insert\n";
  }
  void on_insert_place_found() {
    if (this->tree_ptr->getRoot() and !insert_place_found_clone) {
      insert_place_found_clone = this->tree_ptr->getRoot()->clone();
      insert_place_found_clone->inorderVisit([=](TreeNode<T>* node) {
        static_cast<AVLTree<T>*>(this->tree_ptr)->fixHeight(static_cast<AVLTreeNode<T>*>(node));
        });
    }
  }
  void on_balance(nodeptr node) {
    fix_stack.push_back({ this->tree_ptr->getRoot()->clone(), node->id });
    cout << "on_balance\n";
    //auto clone = test.root->clone();
  }

  virtual void insert(T val) override {
    if (!this->tree_ptr->getRoot()) {
      this->tree_ptr->insert(val);
      this->write(this->tree_ptr->getRoot(), this->tree_ptr->getRoot(), { {} }, {});
      return;
    }
    ins_stack.clear();
    fix_stack.clear();
    insert_place_found_clone = nullptr;
    auto clone = this->tree_ptr->getRoot()->clone();
    this->write(this->tree_ptr->getRoot(), this->tree_ptr->getRoot(), { {} }, {});
    std::string insert_data = to_string(val);
    this->tree_ptr->insert(val);
    printASCII(this->tree_ptr->getRoot());

    auto ins_res = static_cast<AVLTree<T>*>(this->tree_ptr)->last_inserted_node;

    this->write(clone, clone, { },
      { { insert_data, ins_res->id, ins_stack[0] } });
    for (int j = 0; j < ins_stack.size() - 1; ++j) {
      this->write(clone, clone, { { insert_data, ins_res->id, ins_stack[j] } },
        { { insert_data, ins_res->id, ins_stack[j + 1] } });
    }
    this->write(clone, insert_place_found_clone, { {insert_data, ins_res->id,ins_stack[ins_stack.size() - 1]} }, {});
    this->write(insert_place_found_clone, this->tree_ptr->getRoot(), { {} }, {});
  }
  AVLTreeHandler() {
    this->tree_ptr = new AVLTree<T>();
    static_cast<AVLTree<T>*>(this->tree_ptr)->on_insert = [=](nodeptr node) {
      this->on_insert(node);
    };
    static_cast<AVLTree<T>*>(this->tree_ptr)->on_balance = [=](nodeptr node) {
      this->on_balance(node);
    };
    static_cast<AVLTree<T>*>(this->tree_ptr)->on_insert_place_found = [=]() {
      this->on_insert_place_found();
    };
    insert(1);
    insert(2);
    insert(5);
    insert(6);
    insert(7);

  }
};