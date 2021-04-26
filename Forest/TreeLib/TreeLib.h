#pragma once
#include "AVLTree.h"
#include "Wgmlgz.h"
#include <fstream>
#include <stdio.h>
#include <Tree.h>

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

void createJson(int tree_id) {

}