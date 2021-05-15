#pragma once
#include "Tree.h"
#include "Wgmlgz.h"
#include "Colors.h"

// settings
int size_x = 75;
int size_y = 100;
const string DEFAULT_COLOR = "#44475a";

template<typename T>
struct nodeData {
    string content = "";
    double id = 0;
    Rect rect = { {0,0}, {0, 0} };
    TreeNode<T>* ptr = nullptr;
    string color = DEFAULT_COLOR;
};
// vector<nodeData> nodes;

template<typename T>
V2 calcNodeSz(
    TreeNode<T>* node, int parent_id,
    vector<nodeData<T>>& all_child_rects,
    vector<pair<double, double>>& connections
) {
    if (!node) return { 0, 0 };
    vector<V2> child_sizes;

    V2 this_size = { 0, size_y };
    double this_id = node->id;
    if (parent_id != -1) connections.push_back({ parent_id, this_id });

    int child_n = 0;
    for (auto i : node->branches) {
        ++child_n;
        if (i == nullptr) {
            //continue;
            double tmp_id = node->id + 0.001 * child_n;
            connections.push_back({ this_id, tmp_id });
            all_child_rects.push_back({ "null", tmp_id, { {this_size.x, -size_y}, {size_x, size_y} } });
            child_sizes.push_back({ size_x, size_y });
            this_size.x += size_x;
        } else {
            auto sz = all_child_rects.size();

            auto calc_res = calcNodeSz(i, this_id, all_child_rects, connections);

            auto st = all_child_rects.begin() + sz;
            auto end = all_child_rects.end();
            for (auto i = st; i != end; ++i) {
                i->rect.pos.x += this_size.x;
                i->rect.pos.y -= size_y;
            }

            if (calc_res.y > this_size.y) this_size.y = calc_res.y;
            this_size.x += calc_res.x;
        }
    }
    if (this_size.x < size_x) this_size.x = size_x;
    this_size.y += size_y;
    string color = DEFAULT_COLOR;

    auto avl_node = dynamic_cast<AVLTreeNode<T>*>(node);
    if (avl_node) {
        if (abs(AVLTree<T>::bf(avl_node)) == 2) {
            color = "#ff5555";
        } else if (abs(AVLTree<T>::bf(avl_node)) == 1) {
            color = "#ffb86c";
        } else {
            color = "#5cbd75";
        }

    }
    auto treap_node = dynamic_cast<TreapNode<T>*>(node);
    if (treap_node) {
        //auto hsv_color = hsv{ treap_node->priority * 180, 1.0, 1.0 };
        double t = treap_node->priority;
        t /= 2;
        t += 0.2;
        auto rgb_color = rgb{ t, t, t };
        //auto rgb_color = hsv2rgb(hsv_color);
        cout << rgb_color.r << " " << rgb_color.g << " " << rgb_color.b << endl;
        color = rgb2hex(rgb_color, true);
    }
    auto rb_node = dynamic_cast<RBNode<T>*>(node);
    if (rb_node) {
        if (rb_node->color) {
            color = "#ff5555";
        }
    }


    all_child_rects.push_back({ node->to_str(), this_id, {{this_size.x / 2 - size_x / 2, 0} , {size_x, size_y}}, node, color });
    if (parent_id == -1) {
        for (auto& i : all_child_rects) {
            i.rect.pos.x -= this_size.x / 2;
            i.rect.pos.y += this_size.y / 2;
        }
    }
    return this_size;
}

string createJSONNode(string id, string content, int x, int y, int x1, int y1, string color = DEFAULT_COLOR) {
    string json;

    json += "\"" + id + "\"" + ":{";
    json += "\"c\":\"" + content + "\",";
    json += "\"clr\":\"" + color + "\",";
    json += "\"x\":" + to_string(x) + ",";
    json += "\"y\":" + to_string(y) + ",";
    json += "\"X\":" + to_string(x1) + ",";
    json += "\"Y\":" + to_string(y1);
    json += "}";

    return json;
}
template<typename T>
pair<string, string> innerJson(
    vector<nodeData<T>>& calc_res_old,
    vector<pair<double, double>>& connections_old,
    vector<nodeData<T>>& calc_res_new,
    vector<pair<double, double>>& connections_new
) {
    //vector<pair<int, int>> connections_old, connections_new;
    string json;

    for (int i = 0; i < calc_res_new.size(); ++i) {
        auto curr_node = calc_res_new[i];
        auto find_new = nodeData<T>{ "test", curr_node.id, {{500, -1000}, {0, 0}}, nullptr };

        for (auto i : calc_res_old) {
            if (i.id == curr_node.id) {
                find_new = i;
            }
        }

        json += createJSONNode(
            to_string(curr_node.id),
            curr_node.content,
            find_new.rect.pos.x,
            -find_new.rect.pos.y,
            curr_node.rect.pos.x,
            -curr_node.rect.pos.y,
            curr_node.color
        );
        json += (i == calc_res_new.size() - 1 ? "" : ",");
    }

    string lines_json;
    for (int i = 0; i < connections_new.size(); ++i) {
        auto curr_line = connections_new[i];
        lines_json += "\"" + to_string(rand() + rand()) + "\"" + ":{";
        lines_json += "\"a\":\"" + to_string(curr_line.first) + "\",";
        lines_json += "\"b\":\"" + to_string(curr_line.second) + "\"";
        lines_json += "}";
        lines_json += (i == connections_new.size() - 1 ? "" : ",");
    }
    return { json, lines_json };
}

template<typename T>
pair<string, string> toJson(TreeNode<T>* node_old, TreeNode<T>* node_new) {
    vector<nodeData<T>> nodes_old, nodes_new;
    vector<pair<double, double>> connections_old, connections_new;

    calcNodeSz(node_old, -1, nodes_old, connections_old);
    calcNodeSz(node_new, -1, nodes_new, connections_new);

    auto inner_json = innerJson(nodes_old, connections_old, nodes_new, connections_new);

    return { "{" + inner_json.first + "}", "{" + inner_json.second + "}" };
}
template<typename T>
pair<string, string> toJson(TreeNode<T>* node) {
    vector<nodeData<T>> nodes;
    vector<pair<double, double>> connections;

    calcNodeSz(node, -1, nodes, connections);

    auto inner_json = innerJson(nodes, connections, nodes, connections);

    return { "{" + inner_json.first + "}", "{" + inner_json.second + "}" };
}

template<typename T>
struct cupData {
    string content;
    int id;
    int head_id;
};

template<typename T>
pair<string, string> toJsonWithCaps(TreeNode<T>* node_old, TreeNode<T>* node_new,
    vector<cupData<T>> old_caps,
    vector<cupData<T>> new_caps) {
    vector<nodeData<T>> nodes_old, nodes_new;
    vector<pair<double, double>> connections_old, connections_new;

    calcNodeSz(node_old, -1, nodes_old, connections_old);
    calcNodeSz(node_new, -1, nodes_new, connections_new);


    for (auto& i : old_caps) {
        nodeData<T> old_t;
        bool find_old = false, find_new = false;

        for (auto& j : nodes_old) {
            if (j.id == i.head_id) {
                nodes_old.push_back({
                    i.content, i.id,
                    {{j.rect.pos.x, j.rect.pos.y + 30} , {0, 0}}, nullptr
                    });
            }
        }
        int tmp_id = rand();
        // nodes_old.push_back({ i.second, tmp_id,
        //     {{old_t.rect.pos.x, old_t.rect.pos.y + 100} , {0, 0}}, old_t.ptr
        //     });
        // nodes_new.push_back({ i.second, tmp_id,
        //     {{old_t.rect.pos.x, old_t.rect.pos.y + 100} , {0, 0}}, old_t.ptr
        //     });
    }

    for (auto& i : new_caps) {
        nodeData<T> new_t;
        bool find_old = false, find_new = false;

        for (auto& j : nodes_new) {
            if (j.id == i.head_id) {
                nodes_new.push_back({
                    i.content, i.id,
                    {{j.rect.pos.x, j.rect.pos.y + 50} , {0, 0}}, nullptr
                    });
            }
        }
        int tmp_id = rand();
        // nodes_old.push_back({ i.second, tmp_id,
        //     {{old_t.rect.pos.x, old_t.rect.pos.y + 100} , {0, 0}}, old_t.ptr
        //     });
        // nodes_new.push_back({ i.second, tmp_id,
        //     {{old_t.rect.pos.x, old_t.rect.pos.y + 100} , {0, 0}}, old_t.ptr
        //     });
    }
    auto inner_json = innerJson(nodes_old, connections_old, nodes_new, connections_new);

    return { "{" + inner_json.first + "}", "{" + inner_json.second + "}" };
}
