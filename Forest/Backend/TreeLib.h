#pragma once
#include <fstream>
#include <stdio.h>
#include "TreesChangesHandler.h"

// buff
int buff_index = 0;
std::string buff = "test str\n   CUM!!!!!";

void put2Buff(std::string str) {
    buff = str;
    buff_index = 0;
}

int readChar() {
    if (buff_index >= buff.size()) return 0;
    return buff[buff_index++];
}

std::vector<TreeHandler<int>*> trees = {
    new TreeHandler<int>(),
    new AVLTreeHandler<int>(),
    new RBTreeHandler<int>(),
    new TreapHandler<int>(),
    new SplayTreeHandler<int>()

};

int current_tree = 0;
void selectTree(int n) {
    current_tree = n;
}
void insert(int insert_data) {
    trees[current_tree]->insert(insert_data);
}
void getName() {
    put2Buff(trees[current_tree]->display_name);
}
int getStackSize() {
    return trees[current_tree]->json_states_stack.size();
}
void getState(int state = -1) {
    if (trees[current_tree]->json_states_stack.size()) {
        if (state == -1) {
            put2Buff(trees[current_tree]->json_states_stack[trees[current_tree]->json_states_stack.size() - 1]);
        } else {
            put2Buff(trees[current_tree]->json_states_stack[state]);
        }
    } else {
        put2Buff("");
    }
}
void getLines(int state = -1) {
    if (trees[current_tree]->json_lines_stack.size()) {
        if (state == -1) {
            put2Buff(trees[current_tree]->json_lines_stack[trees[current_tree]->json_lines_stack.size() - 1]);
        } else {
            put2Buff(trees[current_tree]->json_lines_stack[state]);
        }
    } else {
        put2Buff("");
    }
}
