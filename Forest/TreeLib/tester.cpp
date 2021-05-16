#include"TreesChangesHandler.h"
//#include "TreeLib.h"
#include "Wgmlgz.h"
int main() {
  srand(23442);
  AVLTreeHandler<int> test;
  cout << " aaaa";
  // createTestTree(50);
  // optputTestTree();
  //std::function<void(nodeptr node)> on_insert = on_insertf;
  //test.on_insert = on_insert;
  //test.on_balance = on_balance;
  test.tree_ptr->insert(666);
  //range(i, 100) test.insert(rand() % 1000);
  //printASCII(test.root);
  range(i, 10) {
    //auto clone = test.root->clone();
    int t = rand() % 1000;
    //string insert_data = to_string(t);
    test.insert(t);
    printASCII(test.tree_ptr->getRoot());
    // for (int j = 0; j < ins_stack.size() - 1; ++j) {
    //   write(clone, clone, { { insert_data, ins_res->id, ins_stack[j] } },
    //     { { insert_data, ins_res->id, ins_stack[j + 1] } });
    // }
    // write(clone, test.root, { {insert_data, ins_res->id,
    // ins_stack[ins_stack.size() - 1]} }, {});

    //printASCII(test.root);
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
