#pragma once
#include "AVLTree.h"
#include "Treap.h"
#include "Wgmlgz.h"
#include <fstream>
#include <stdio.h>
#include "Tree.h"
#include "TreePrinterJSON.h"
#include "TreePrinterASCII.h"


// buff
int buff_index = 0;
string buff = "test str\n   CUM!!!!!";

void put2Buff(string str) {
    buff = str;
    buff_index = 0;
}

int readChar() {
    if (buff_index >= buff.size()) return 0;
    return buff[buff_index++];
}


struct TreeData {
    string display_name = "I'm a defaut tree(";
    BinSearchTree<int>* tree_ptr = nullptr;
    vector<string> json_states_stack;
    vector<string> json_lines_stack;
};

vector<TreeData> trees = {
    {"Binary search tree", new BinSearchTree<int>()},
    {"AVL tree", new AVLTree<int>() },
    {"AVL tree", new AVLTree<int>() },
    {"Treap", new Treap<int>() },
    {"Treap", new Treap<int>()}
};

int current_tree = 0;
void selectTree(int n) {
    current_tree = n;
}
void insert(int insert_data) {
    trees[current_tree].tree_ptr->insert(insert_data);
    auto json = toJson<int>(trees[current_tree].tree_ptr->getRoot());
    trees[current_tree].json_states_stack.push_back(json.first);
    trees[current_tree].json_lines_stack.push_back(json.second);
}
void getName() {
    put2Buff(trees[current_tree].display_name);
}
void getState(int state = -1) {
    if (trees[current_tree].json_states_stack.size()) {
        if (state == -1) {
            put2Buff(trees[current_tree].json_states_stack[trees[current_tree].json_states_stack.size() - 1]);
        } else {
            put2Buff(trees[current_tree].json_states_stack[state]);
        }
    } else {
        put2Buff("");
    }
}
void getLines(int state = -1) {
    if (trees[current_tree].json_lines_stack.size()) {
        if (state == -1) {
            put2Buff(trees[current_tree].json_lines_stack[trees[current_tree].json_lines_stack.size() - 1]);
        } else {
            put2Buff(trees[current_tree].json_lines_stack[state]);
        }
    } else {
        put2Buff("");
    }
}
