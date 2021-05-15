#pragma once
#include "Wgmlgz.h"


struct V2 { int x = 0, y = 0; V2(int nx, int ny) { x = nx; y = ny; } };
struct Rect { V2 pos, size; };
struct Line { V2 pos1, pos2; };
// use ++id_counter
int id_counter = 0;
Tclass TreeNode{
public:
  std::vector<TreeNode*> branches;
  int id = ++id_counter;
  T data;
  TreeNode() {};

  virtual ~TreeNode() = default;

  TreeNode(T new_data) {
    data = new_data;
    branches.resize(5, nullptr);
  }

  TreeNode(T new_data, vector<TreeNode*> new_branches) {
    data = new_data;
    branches = new_branches;
  }

  void pushData(size_t n, T new_data) {
    branches[n] = new TreeNode(new_data);
  }

  bool isEnd() {
    for (auto i : branches) if (i) return false;
    return true;
  }

  virtual TreeNode<T>* clone() {
    vector<TreeNode<T>*> cloned_branches;
    for (auto& i : branches) {
      if (i) cloned_branches.push_back(i->clone());
      else cloned_branches.push_back(nullptr);
    }
    TreeNode<T>* cloned_node =
      new TreeNode<T>(this->data, cloned_branches);
    cloned_node->id = id;
    return cloned_node;
  }

  vector<string> to_vstr() { return { std::to_string(data) }; }
  string to_str() {
    string ret;
    for (auto& i : to_vstr())
      ret += i;
    return ret;
  }
};