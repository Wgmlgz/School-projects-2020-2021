#include "TreeLib.h"
#include <fstream>
#include "TreePrinterASCII.h"

const bool DEBUG = false;

string path = "C:\\Code\\School\\Forest\\Frontend\\";

using node_ptr = AVLTreeNode<int>*;

AVLTree<int> test;
// insert stuff 
vector<int> ins_stack;

void on_insert(node_ptr node) {
  ins_stack.push_back(node->id);

  cout << "on_insert\n";
}

void on_balance(node_ptr node) {
  cout << "on_balance\n";
  //auto clone = test.root->clone();

}

void write(TreeNode<int>* a, TreeNode<int>* b, vector<cupData<int>> acap, vector<cupData<int>> bcap) {
  static int frame_n = 0;

  std::ofstream tree_json(path + "tree_frame_" + to_string(frame_n) + ".json");
  std::ofstream lines_json(path + "lines_frame_" + to_string(frame_n) + ".json");

  auto stringify_res = toJsonWithCaps(a, b, acap, bcap);

  tree_json << stringify_res.first << endl;
  lines_json << stringify_res.second << endl;

  cout << stringify_res.first << endl;

  ++frame_n;
}
int main() {
  srand(23442);
  // createTestTree(50);
  // optputTestTree();
  //std::function<void(node_ptr node)> on_insert = on_insertf;
  test.on_insert = on_insert;
  test.on_balance = on_balance;
  test.insert(666);
  //range(i, 100) test.insert(rand() % 100);
  range(i, 10) {
    ins_stack.clear();
    auto clone = test.root->clone();
    int t = rand() % 100;
    string insert_data = to_string(t);
    auto ins_res = test.insert(t);

    for (int j = 0; j < ins_stack.size() - 1; ++j) {
      write(clone, clone, { { insert_data, ins_res->id, ins_stack[j] } },
        { { insert_data, ins_res->id, ins_stack[j + 1] } });
    }
    write(clone, test.root, { {insert_data, ins_res->id,
    ins_stack[ins_stack.size() - 1]} }, {});
    // BinTreeNode<int>* ttt = test.root;
  // ttt->reverse();
  //printASCII(test.root);
  }
  //auto clone = test.root->clone();
  // range(i, 10) {
  //  test.insert(rand() % 100);
  // }
  //BinTreeNode<int>* ttt = test.root;
  //ttt->reverse();
  //std::swap(clone->branches[0], clone->branches[1]);


  // 
  // printASCII(clone);
  // printASCII(test.root);
  // cout << stringify_res.first << endl;
  // cout << stringify_res.second << endl;


}
