#pragma once
#include "Wgmlgz.h"
#include "Tree.h"



// settings
int spacing_x = 0;
int spacing_y = 0;
int block_spacing = 1;
int vertical_spacing = 0;

string cor_top = ".";
string cor_donw = "\'";

char sp = ' ';
char hor = '-';
string ver = "|";


string cor_top_arr = ".";
char hor_arr = '-';
string ver_arr = "|";

using vstr = vector<string>;

vstr null_render = { "null" };


template<typename T>
V2 size(TreeNode<T>* node) {
    int max = 0;
    for (auto i : node->to_vstr())
        if (i.length() > max)
            max = i.length();
    int x = max + spacing_x * 2 + 2;
    int y = 2 + node->to_vstr().size() + spacing_y * 2;
    return V2{ x, y };
}

void _print(vstr& v) {
    for (auto& i : v) {
        cout << i << "#" << endl;
    }
}

template<typename T>
vstr render(TreeNode<T>* node) {
    vector<string> ret;

    ret.push_back(cor_top + string(size(node).x - 2, hor) + cor_top);
    int to_fill = size(node).x - 2;

    range(i, spacing_y)
        ret.push_back(ver + string(size(node).x - 2, sp) + ver);

    for (auto i : node->to_vstr()) {
        string tmp = ver;
        tmp += string(((to_fill - i.length()) / 2), ' ');
        tmp += i;
        tmp += string(to_fill - ((to_fill - i.length()) / 2) - i.length(), ' ');
        tmp += ver;
        ret.push_back(tmp);
    }

    range(i, spacing_y)
        ret.push_back(ver + string(size(node).x - 2, sp) + ver);
    ret.push_back(cor_donw + string(size(node).x - 2, hor) + cor_donw);
    //_print(ret);
    return ret;
}

template<typename T>
vstr renderRec(TreeNode<T>* node) {
    //if (isEnd()) {
    //  return render();
    //}

    vector<vstr> rendered_branches;
    for (auto i : node->branches) {
        if (i == nullptr) rendered_branches.push_back(null_render);
        else rendered_branches.push_back(renderRec(i));
    }
    int max = 0;
    for (auto& i : rendered_branches)
        if (i.size() > max) max = i.size();
    for (auto& i : rendered_branches)
        if (i.size() < max)
            i.resize(max, string(i[0].size(), ' '));
    vstr rendered_this = render(node);
    int offset = vertical_spacing + rendered_this.size();
    vstr res(rendered_branches[0].size() + offset);
    if (rendered_branches.size() == 1) {
        for (auto& i : rendered_branches[0]) {
            if (i.length() < rendered_this[0].length()) {
                i.resize(rendered_this[0].length(), ' ');
            }
        }
    }
    range(i, rendered_branches.size()) {
        range2(j, offset, offset + rendered_branches[i].size()) {
            res[j] += rendered_branches[i][j - offset];
            if (i < rendered_branches.size() - 1) {
                res[j] += string(block_spacing, ' ');
            }
        }
    }
    range2(i, (rendered_this.size() - 2) / 2 + 1, offset) {
        range(j, rendered_branches.size()) {
            int to_fill = rendered_branches[j][0].size();
            bool b = (i != (rendered_branches.size() - 2) / 2 + 1);
            res[i] += string(to_fill - to_fill / 2 - 1, !b && j != 0 ? hor_arr : ' ');
            res[i] += b ? ver_arr : cor_top_arr;
            res[i] += string(to_fill / 2, !b && j != rendered_branches.size() - 1 ? hor_arr : ' ');
            if (j < rendered_branches.size() - 1)
                res[i] += string(block_spacing, b ? ' ' : hor_arr);
        }
    }
    range(i, (rendered_this.size() - 2) / 2 + 1) {
        res[i] += string(res[res.size() - 1].size(), ' ');
    }
    int placement_offset = (res[0].size() - rendered_this[0].size()) / 2;
    range(i, rendered_this.size()) {
        range(j, rendered_this[0].size()) {
            res[i][j + placement_offset] = rendered_this[i][j];
        }
    }
    //_print(res);
    return res;
}

template<typename T>
void printASCII(TreeNode<T>* node) {
    for (auto& i : renderRec(node))
        cout << i << endl;
}