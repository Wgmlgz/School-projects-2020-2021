#include <vector>
#include <string>
#include <iostream>
#include "pyrange.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

using vstr = vector<string>;
template<typename T> 
class Node {
public:
  T* data;
  std::vector<T*> branches;
};

struct V2 {int x = 0, y = 0; };
struct Rect { V2 pos, size; };

class StrTreeNode {
// settings
public:
  vector<StrTreeNode*> branches;

  int spacing_x = 0;
  int spacing_y = 0;
  vector<string> data;
  int color;
  V2 pos;
  V2 size(){
    int max = 0;
    for (auto i : data)
      if (i.length() > max)
        max = i.length();
    int x = max + spacing_x * 2 + 2;
    int y = 2 + data.size() + spacing_y * 2;
    return {x, y};
  }
  vstr render() {
    string cor_top = ".";
    string cor_donw = "\'";
    //string corner = ".";
    char sp = ' ';
    char hor = '-';
    string ver = "|";
    vector<string> ret;
    ret.push_back(cor_top + string(size().x - 2, hor) + cor_top);
    int to_fill = size().x - 2;
    for (auto i : range(spacing_y))
      ret.push_back(ver + string(size().x - 2, sp) + ver);
    for (auto i : data) {
        string tmp = ver;
        tmp += string(((to_fill - i.length()) / 2), ' ');
        tmp += i;
        tmp += string(to_fill - ((to_fill - i.length()) / 2) - i.length(), ' ');
        tmp += ver;
        ret.push_back(tmp);
    }
    for (auto i : range(spacing_y))
      ret.push_back(ver + string(size().x - 2, sp) + ver);
    ret.push_back(cor_donw + string(size().x - 2, hor) + cor_donw);
    return ret;
  }
  void _print(vstr& v){
    for (auto& i : v) {
      cout << i << endl;
    }
  }
  void print(){
    for (auto& i : renderRec()) {
      cout << i << endl;
    }
  }
  vstr renderRec() {
    if (branches.size() == 0) {
      return render();
    }
    int block_spacing = 0;
    int vertical_spacing = 1;
    string corner = ".";
    string ver = "|";
    string hor = "_";

    vector<vstr> rendered_brunches;
    for (auto i : branches)
      rendered_brunches.push_back(i->renderRec());
    int max = 0;
    for (auto& i : rendered_brunches)
      if (i.size() > max) max = i.size();
    for (auto& i : rendered_brunches)
      if (i.size() < max) 
        for (auto j : range(max - i.size()))
          i.push_back(string(i[0].size(), ' '));
    vstr rendered_this = render();
    int offset = vertical_spacing + rendered_this.size();
    vstr res(rendered_brunches[0].size() + offset);
    for (auto i : range(rendered_brunches.size())) {
      for (auto j : range(offset, offset + rendered_brunches[i].size())) {
        res[j] += rendered_brunches[i][j - offset];
        if (i < rendered_brunches.size() - 1)
          res[j] += string(block_spacing, ' ');
      }
    }
    
    for (auto i : range((rendered_this.size() - 2) / 2 + 1,  offset)) {
      for (auto j : range(rendered_brunches.size())) {
        int to_fill = rendered_brunches[j][0].size();
        bool b = (i != (rendered_brunches.size() - 2) / 2 + 1);
        res[i] += string(to_fill - to_fill / 2 - 1, !b && j != 0 ?'-':' ');
        res[i] += b ? ver : corner;
        res[i] += string(to_fill / 2, !b && j != rendered_brunches.size() - 1?'-':' ');
        if (j < rendered_brunches.size() - 1)
            res[i] += string(block_spacing, b?' ':'-');
      }
    }
    for (auto i : range((rendered_this.size() - 2) / 2 + 1)) {
      res[i] += string(res[res.size() - 1].size(), ' ');
    }
    int placement_offset = (res[0].size() - rendered_this[0].size()) / 2;
    for (auto i : range(rendered_this.size())) {
      for (auto j : range(rendered_this[0].size())) {
        res[i][j + placement_offset] = rendered_this[i][j];
      }
    }
    return res;
  }
  StrTreeNode(string str) {
    data = {str};
  }
  StrTreeNode(vector<string> v) {
    data = v;
  }
};
class StringTree {
  StrTreeNode* root;
};
template<typename T> 
class Tree {
public:
    Node<T>* root;
    void calcRect(){

    }
    void print(){

    }
};

template<typename T> 
class BiraryTree : public Tree<T> {
    
};
