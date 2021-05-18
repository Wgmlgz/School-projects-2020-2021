#pragma once
#include "TreePrinterJSON.h"
#include "TreePrinterASCII.h"
#include "TreeLib/Trees.h"
#include <functional>

template<typename T>
class TreeHandler {
public:
  using bstnodeptr = BinTreeNode<T>*;

  std::string display_name = "I'm a defaut tree(";
  BinSearchTree<T>* tree_ptr = nullptr;
  std::vector<std::string> json_states_stack = { "{\"666\":{\"c\":\"null\",\"clr\":\"#44475a\",\"x\":0,\"y\":0,\"X\":0,\"Y\":0}}" };
  std::vector<std::string> json_lines_stack = { "" };

  std::vector<int> ins_stack;
  TreeNode<T>* insert_place_found_clone = nullptr;

  void on_insert(bstnodeptr node) {
    ins_stack.push_back(node->id);
  }


  void on_insert_place_found() {
    if (tree_ptr->getRoot() and !insert_place_found_clone) {
      insert_place_found_clone = tree_ptr->getRoot()->clone();
    }
  }

  void write(TreeNode<int>* a, TreeNode<int>* b, std::vector<cupData<int>> acap, std::vector<cupData<int>> bcap) {
    static int frame_n = 0;
    auto stringify_res = toJsonWithCaps(a, b, acap, bcap);

    json_states_stack.push_back(stringify_res.first);
    json_lines_stack.push_back(stringify_res.second);

    //std::cout << std::stringify_res.first << std::endl;

    ++frame_n;
  }

  bool tryRootInsert(T val) {
    if (!this->tree_ptr->getRoot()) {
      this->tree_ptr->insert(val);
      this->write(this->tree_ptr->getRoot(), this->tree_ptr->getRoot(), { {} }, {});
      return true;
    }
    return false;
  }
  void writeBstInsert(T val) {
    ins_stack.clear();
    this->insert_place_found_clone = nullptr;
    auto clone = this->tree_ptr->getRoot()->clone();
    this->write(this->tree_ptr->getRoot(), this->tree_ptr->getRoot(), { {} }, {});
    std::string insert_data = std::to_string(val);
    this->tree_ptr->insert(val);
    printASCII(this->tree_ptr->getRoot());

    auto ins_res = static_cast<BinSearchTree<T>*>(this->tree_ptr)->last_inserted_node;

    this->write(clone, clone, { },
      { { insert_data, ins_res->id, this->ins_stack[0] } });
    for (int j = 0; j < this->ins_stack.size() - 1; ++j) {
      this->write(clone, clone, { { insert_data, ins_res->id, this->ins_stack[j] } },
        { { insert_data, ins_res->id, this->ins_stack[j + 1] } });
    }
    this->write(clone, this->tree_ptr->getRoot(), {
      {insert_data, ins_res->id,this->ins_stack[this->ins_stack.size() - 1]}
      }, {});

  }

  virtual void insert(T val) {
    if (this->tryRootInsert(val)) return;
    this->writeBstInsert(val);
  }

  explicit TreeHandler() {
    this->tree_ptr = new BinSearchTree<T>();
    this->tree_ptr->on_insert = [=](bstnodeptr node) {
      this->on_insert(node);
    };
    this->tree_ptr->on_insert_place_found = [=]() {
      this->on_insert_place_found();
    };
    insert(1);
    insert(2);
    insert(5);
    insert(6);
    insert(7);

  }
};

template<typename T>
class AVLTreeHandler : public TreeHandler<T> {
public:
  std::vector<std::pair<TreeNode<T>*, int>> fix_stack;
  using nodeptr = AVLTreeNode<T>*;
  using bstnodeptr = BinTreeNode<T>*;


  void on_insert_place_found() {
    if (this->tree_ptr->getRoot() and !this->insert_place_found_clone) {
      this->insert_place_found_clone = this->tree_ptr->getRoot()->clone();
      this->insert_place_found_clone->inorderVisit([=](TreeNode<T>* node) {
        static_cast<AVLTree<T>*>(this->tree_ptr)->fixHeight(static_cast<AVLTreeNode<T>*>(node));
        });
    }
  }
  void on_balance(nodeptr node) {
    fix_stack.push_back({ this->tree_ptr->getRoot()->clone(), node->id });
    std::cout << "on_balance\n";
  }

  virtual void insert(T val) override {
    if (this->tryRootInsert(val)) return;
    this->writeBstInsert(val);
    this->write(this->insert_place_found_clone, this->tree_ptr->getRoot(), { {} }, {});
  }
  AVLTreeHandler() {
    this->tree_ptr = new AVLTree<T>();
    this->tree_ptr->on_insert = [=](bstnodeptr node) {
      this->on_insert(node);
    };
    this->tree_ptr->on_insert_place_found = [=]() {
      on_insert_place_found();
    };
    static_cast<AVLTree<T>*>(this->tree_ptr)->on_balance = [=](nodeptr node) {
      this->on_balance(node);
    };
    insert(1);
    insert(2);
    insert(5);
    insert(6);
    insert(7);

  }
};

template<typename T>
class TreapHandler : public TreeHandler<T> {
public:
  using nodeptr = TreapNode<T>*;
  using bstnodeptr = BinTreeNode<T>*;


  //void on_balance(nodeptr node) {
  //  fix_stack.push_back({ this->tree_ptr->getRoot()->clone(), node->id });
  //  std::cout << "on_balance\n";
  //}

  virtual void insert(T val) override {
    if (this->tryRootInsert(val)) return;
    //this->writeBstInsert(val);
    auto clone = this->tree_ptr->getRoot()->clone();
    this->tree_ptr->insert(val);

    this->write(clone, this->tree_ptr->getRoot(), { {} }, {});
  }
  TreapHandler() {
    this->tree_ptr = new Treap<T>();
    this->tree_ptr->on_insert = [=](bstnodeptr node) {
      this->on_insert(node);
    };
    this->tree_ptr->on_insert_place_found = [=]() {
      this->on_insert_place_found();
    };
    this->tree_ptr->insert(1);
    this->tree_ptr->insert(2);
    this->tree_ptr->insert(3);

    // static_cast<AVLTree<T>*>(this->tree_ptr)->on_balance = [=](nodeptr node) {
      // this->on_balance(node);
    // };
    // insert(1);
    // insert(2);
    // insert(5);
    // insert(6);
    // insert(7);

  }
};