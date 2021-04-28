#include  "TreeLib.h"
#include <fstream>
#include "TreePrinterASCII.h"
const bool DEBUG = false;

int main() {
  // createTestTree(50);
  // optputTestTree();
  srand(23442);
  BinSearchTree<int> test;
  string path = "C:\\Code\\School\\Forest\\Frontend\\";
  test.insert(666);
  range(i, 50) {
    auto clone = test.root->clone();
    auto ins_res = test.insert(rand() % 100);


    // BinTreeNode<int>* ttt = test.root;
    // ttt->reverse();
    //printASCII(test.root);
    std::ofstream tree_json(path + "tree_frame_" + to_string(i) + ".json");
    std::ofstream lines_json(path + "lines_frame_" + to_string(i) + ".json");

    struct cupData<int> FUCK = { "da", ins_res->id, test.root->id };

    auto stringify_res =
      toJsonWithCaps(clone, test.root, { FUCK }, {});

    tree_json << stringify_res.first << endl;
    lines_json << stringify_res.second << endl;

    cout << stringify_res.first << endl;
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
