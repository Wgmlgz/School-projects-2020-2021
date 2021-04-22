#include <random>
#include <iostream>
#include <vector>
#include "Wgmlgz.h"


using vstr = vector<string>;

struct V2 { int x = 0, y = 0; };
struct Rect { V2 pos, size; };


template<typename T>
class TreeNode {
public:
    std::vector<TreeNode*> branches;
    T data;
    TreeNode() {};
    explicit TreeNode(T new_data) {
        data = new_data;
        branches.resize(5, nullptr);
    }
    void pushData(size_t push_pos, T new_data) {
        branches[push_pos] = new TreeNode(new_data);
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
        return { x, y };
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

public:
    void print() {
        for (auto& i : renderRec())
            cout << i << endl;
    }
};

template<typename T>
class BinTreeNode : public TreeNode<T> {
public:
    void init() {
        this->branches.resize(2, nullptr);
    }
    explicit BinTreeNode(T new_data) {
        init();
        this->data = new_data;
    }
    BinTreeNode() {
        init();
    }
    BinTreeNode<T>* get_lhs() { return static_cast<BinTreeNode<T>*>(this->branches[0]); }
    BinTreeNode<T>* get_rhs() { return static_cast<BinTreeNode<T>*>(this->branches[1]); }
    void set_lhs(BinTreeNode<T>* new_ptr) {
        this->branches[0] = static_cast<TreeNode<T>*>(new_ptr);
    }
    void set_rhs(BinTreeNode<T>* new_ptr) {
        this->branches[1] = static_cast<TreeNode<T>*>(new_ptr);
    }

    void pushLhs(T new_data) { this->pushData(0, new_data); }
    void pushRhs(T new_data) { this->pushData(1, new_data); }
};

template<typename T>
class BinSearchTree {
    using node_ptr = BinTreeNode<T>*;
    node_ptr insert(node_ptr node, T insert_data) {
        if (!node) return new BinTreeNode<T>(insert_data);
        if (insert_data < node->data)
            node->set_lhs(insert(node->get_lhs(), insert_data));
        else
            node->set_rhs(insert(node->get_rhs(), insert_data));
        return node;
    }

public:
    node_ptr root = nullptr;
    node_ptr rrot(node_ptr node) {
        node_ptr FUCKPCF_tmp = node->get_lhs();
        node->set_lhs(FUCKPCF_tmp->get_rhs());
        FUCKPCF_tmp->set_rhs(node);
        return FUCKPCF_tmp;
    }
    node_ptr lrot(node_ptr node) {
        node_ptr FUCKPCF_tmp = node->get_rhs();
        node->set_rhs(FUCKPCF_tmp->get_lhs());
        FUCKPCF_tmp->set_lhs(node);
        return FUCKPCF_tmp;
    }
    void insert(T insert_data) {
        root = insert(root, insert_data);
    }
};

double dRand(double fMin = 0.0, double fMax = 1.0) {
    double FUCKPCF_tmp = static_cast<double>(rand()) / RAND_MAX;
    return fMin + FUCKPCF_tmp * (fMax - fMin);
}

template<typename T>
class TreapNode : public BinTreeNode<T> {
public:
    TreapNode<T>* get_lhs() { return static_cast<TreapNode<T>*>(BinTreeNode<T>::get_lhs()); }
    TreapNode<T>* get_rhs() { return static_cast<TreapNode<T>*>(BinTreeNode<T>::get_rhs()); }
    void set_lhs(TreapNode<T>* new_ptr) {
        BinTreeNode<T>::set_lhs(static_cast<BinTreeNode<T>*>(new_ptr));
    }
    void set_rhs(TreapNode<T>* new_ptr) {
        BinTreeNode<T>::set_rhs(static_cast<BinTreeNode<T>*>(new_ptr));
    }
    using node_ptr = TreapNode<T>*;
    double priority = dRand();
    TreapNode(T new_data, node_ptr new_left = nullptr, node_ptr new_right = nullptr) {
        BinTreeNode<T>::TreeNode::data = new_data;
        priority = dRand();
        BinTreeNode<T>::set_lhs(new_left);
        BinTreeNode<T>::set_rhs(new_right);
    }
    TreapNode(T new_data, double new_priority, node_ptr left = nullptr, node_ptr right = nullptr) {
        BinTreeNode<T>::TreeNode::data = new_data;
        priority = new_priority;
        BinTreeNode<T>::set_lhs(left);
        BinTreeNode<T>::set_rhs(right);
    }
};

template<typename T>
class Treap : public BinSearchTree<T> {
public:
    using node_ptr = TreapNode<T>*;

    void split(node_ptr node, T x, node_ptr& L, node_ptr& R) {
        node_ptr newTree = nullptr;
        if (node->data <= x) {
            if (node->get_rhs() == nullptr)
                R = nullptr;
            else
                split(node->get_rhs(), x, newTree, R);
            L = new TreapNode<T>(node->data, node->priority, node->get_lhs(), newTree);
        } else {
            if (node->get_lhs() == nullptr)
                L = nullptr;
            else
                split(node->get_lhs(), x, L, newTree);
            R = new TreapNode<T>(node->data, node->priority, newTree, node->get_rhs());
        }
    }
    node_ptr Merge(node_ptr L, node_ptr R) {
        if (L == nullptr) return R;
        if (R == nullptr) return L;

        if (L->priority > R->priority) {
            auto newR = Merge(L->get_rhs(), R);
            return new TreapNode<T>(L->data, L->priority, L->get_lhs(), newR);
        } else {
            auto newL = Merge(L, R->get_lhs());
            return new TreapNode<T>(R->data, R->priority, newL, R->get_rhs());
        }
    }
    node_ptr insert(node_ptr node, T insert_data) {
        node_ptr l = nullptr, r = nullptr;
        split(node, insert_data, l, r);
        node_ptr m = new TreapNode<T>(insert_data);
        return Merge(Merge(l, m), r);
    }
    void insert(T insert_data) {
        if (!this->root) {
            this->root = new TreapNode<T>(insert_data);
            return;
        }
        this->root = insert(static_cast<node_ptr>(this->root), insert_data);
    }
    node_ptr next(T input, node_ptr node) {
        // TODO: fix this shit

        // if (!node)
        //     return nullptr;
        // if (node->data == input)
        //     return node;
        // if (node->data < input) {
        //     auto t = next(input, node->get_rhs());
        //     return t ? t : node;
        // } else {
        //     auto t = next(input, node->get_rhs());
        //     if (t->data <= input ? t : node)
        //     return t ? t: node;
        // }
    }
    node_ptr next(T input) {
        return next(input, static_cast<node_ptr>(this->root));
    }
};

const bool DEBUG = true;

int main() {
    auto tr = Treap<int>();
    int input = 0, numbers = 10, last = -1;
    char ch;

    std::cin >> numbers;
    for (int counter = 0; counter < numbers; ++counter) {
        std::cin >> ch >> input;
        if (ch == '+') {
            if (last != -1)
                tr.insert(input + last);
            else
                tr.insert(input);
            last = -1;
        } else {
            auto res = tr.next(input);
            if (res) {
                std::cout << res->data << std::endl;
                last = res->data;
            } else {
                std::cout << -1 << std::endl;
            }
        }
        if (DEBUG) tr.root->print();
    }
}
