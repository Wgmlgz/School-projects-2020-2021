#include  "TreeLib.h"
#include <fstream>
const bool DEBUG = false;

int main() {
  // createTestTree(50);
  // optputTestTree();
  srand(23442);
  AVLTree<int> test;
  range(i, 100) {
    test.insert(rand() % 100);
  }
  std::ofstream tree_json("C:\\Code\\School\\Forest\\Frontend\\tree_frame_0.json");
  std::ofstream lines_json("C:\\Code\\School\\Forest\\Frontend\\lines_frame_0.json");

  auto stringify_res = toJson(test.root);
  cout << stringify_res.first << endl;
  cout << stringify_res.second << endl;
  tree_json << stringify_res.first << endl;
  lines_json << stringify_res.second << endl;

}
