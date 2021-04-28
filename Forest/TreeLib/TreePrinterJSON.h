#pragma once
#include "Tree.h"
#include "Wgmlgz.h"

// settings
int size_x = 75;
int size_y = 75;

template<typename T>
struct nodeData {
    string content = "";
    int id = 0;
    Rect rect = { {0,0}, {0, 0} };
    TreeNode<T>* ptr = nullptr;
};
// vector<nodeData> nodes;

template<typename T>
V2 calcNodeSz(
    TreeNode<T>* node, int parent_id,
    vector<nodeData<T>>& all_child_rects,
    vector<pair<int, int>>& connections
) {
    vector<V2> child_sizes;

    V2 this_size = { 0, size_y };
    int this_id = node->id;
    if (parent_id != -1) connections.push_back({ parent_id, this_id });

    for (auto i : node->branches) {
        if (i == nullptr) {
            continue;
            // int tmp_id = rand();
            // connections.push_back({ this_id, tmp_id });
            // //all_child_rects.push_back({ "null", to_string(rand()), {{0, 0}, {size_x, size_y}} });
            // all_child_rects.push_back({ "null", tmp_id, { {this_size.x, -size_y}, {size_x, size_y} } });
            // child_sizes.push_back({ size_x, size_y });
            // this_size.x += size_x;
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
    all_child_rects.push_back({ node->to_str(), this_id, {{this_size.x / 2 - size_x / 2, 0} , {size_x, size_y} }, node });
    return this_size;
}

string createJSONNode(string id, string content, int x, int y, int x1, int y1) {
    string json;

    json += "\"" + id + "\"" + ":{";
    json += "\"c\":\"" + content + "\",";
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
    vector<pair<int, int>>& connections_old,
    vector<nodeData<T>>& calc_res_new,
    vector<pair<int, int>>& connections_new
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
            -curr_node.rect.pos.y
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
    vector<pair<int, int>> connections_old, connections_new;

    calcNodeSz(node_old, -1, nodes_old, connections_old);
    calcNodeSz(node_new, -1, nodes_new, connections_new);

    auto inner_json = innerJson(nodes_old, connections_old, nodes_new, connections_new);

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
    vector<pair<int, int>> connections_old, connections_new;

    calcNodeSz(node_old, -1, nodes_old, connections_old);
    calcNodeSz(node_new, -1, nodes_new, connections_new);


    for (auto& i : old_caps) {
        nodeData<T> old_t;
        bool find_old = false, find_new = false;

        for (auto& j : nodes_old) {
            if (j.id == i.head_id) {
                nodes_old.push_back({
                    i.content, i.id,
                    {{j.rect.pos.x, j.rect.pos.y + 100} , {0, 0}}, nullptr
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
