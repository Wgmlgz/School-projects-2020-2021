#include "Wgmlgz.h"

using vstr = vector<string>;

struct V2 { int x = 0, y = 0; };
struct Rect { V2 pos, size; };

Tclass TreeNode{
public:
  std::vector<TreeNode*> branches;
  T data;
  TreeNode() {};
  TreeNode(T new_data) {
    data = new_data;
    branches.resize(5, nullptr);
  }
  void pushData(size_t n, T new_data) {
    branches[n] = new TreeNode(new_data);
  }
  bool isEnd() {
    for (auto i : branches) if (i) return false;
    return true;
  }

private:
  vector<string> str_data() { return { std::to_string(data) }; }
  vstr null_render = { "null" };
public:
  int spacing_x = 0;
  int spacing_y = 0;
  int block_spacing = 1;
  int vertical_spacing = 0;

  string cor_top = ".";
  string cor_donw = "\'";

  char sp = ' ';
  char hor = '-';
  string ver = "|";


  string cor_top_arr = " ";
  char hor_arr = '_';
  string ver_arr = "|";


private:
  V2 size() {
    int max = 0;
    for (auto i : str_data())
      if (i.length() > max)
        max = i.length();
    int x = max + spacing_x * 2 + 2;
    int y = 2 + str_data().size() + spacing_y * 2;
    return {x, y};
  }
  void _print(vstr& v) {
    for (auto& i : v) {
      cout << i << "#" << endl;
    }
  }
  vstr render() {
    vector<string> ret;

    ret.push_back(cor_top + string(size().x - 2, hor) + cor_top);
    int to_fill = size().x - 2;

    range(i, spacing_y)
      ret.push_back(ver + string(size().x - 2, sp) + ver);

    for (auto i : str_data()) {
        string tmp = ver;
        tmp += string(((to_fill - i.length()) / 2), ' ');
        tmp += i;
        tmp += string(to_fill - ((to_fill - i.length()) / 2) - i.length(), ' ');
        tmp += ver;
        ret.push_back(tmp);
    }

    range(i, spacing_y)
      ret.push_back(ver + string(size().x - 2, sp) + ver);
    ret.push_back(cor_donw + string(size().x - 2, hor) + cor_donw);
    //_print(ret);
    return ret;
  }
  vstr renderRec() {
    //if (isEnd()) {
    //  return render();
    //}

    vector<vstr> rendered_branches;
    for (auto i : this->branches) {
      if (i == nullptr) rendered_branches.push_back(null_render);
      else rendered_branches.push_back(i->renderRec());
    }
    int max = 0;
    for (auto& i : rendered_branches)
      if (i.size() > max) max = i.size();
    for (auto& i : rendered_branches)
      if (i.size() < max)
        i.resize(max, string(i[0].size(), ' '));
    vstr rendered_this = render();
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
    range2(i, (rendered_this.size() - 2) / 2 + 1,  offset) {
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

public:
  void print() {
    for (auto& i : renderRec())
      cout << i << endl;
  }
};

template <typename T>
class Tree {
  virtual void insert(T insert_data) {

  }
}