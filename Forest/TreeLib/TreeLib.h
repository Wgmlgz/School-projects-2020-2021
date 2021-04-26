#pragma once
#include "AVLTree.h"
#include "Wgmlgz.h"
#include <fstream>
#include <stdio.h>
#include "Tree.h"
#include "TreePrinter.h"

AVLTree<int> test_tree;
vector<TreeNode<int>*> forest;
void createTestTree(int tree_size) {
    range(i, tree_size) {
        test_tree.insert(rand() % 100);
    }
}


void outputTestTree() {
    test_tree.root->print();
    auto file = std::ofstream("file.txt");
    file << "test str";
    file.close();
}

string buff = "test str\n   CUM!!!!!";
int buff_index = 0;
void resetRead() {
    buff_index = 0;
}
int readChar() {
    if (buff_index >= buff.size()) return 0;
    return buff[buff_index++];
}
void testTreeToJson() {
    buff = toJson<int>(test_tree.root).first;
    buff_index = 0;
}