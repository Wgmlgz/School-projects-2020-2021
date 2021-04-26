#pragma once
#include "Tree.h"
#include "Wgmlgz.h"

// settings
int size_x = 50;
int size_y = 50;

struct nodeData {
    string content;
    int id;
    Rect rect;
};
vector<nodeData> nodes;
vector<pair<int, int>> connections;

int id_counter = 0;
template<typename T>
pair<vector<nodeData>, V2> calcNodeSz(TreeNode<T>* node, int parent_id) {
    vector<nodeData> all_child_rects;
    vector<V2> child_sizes;

    V2 this_size = { 0, size_y };
    int this_id = ++id_counter;
    if (parent_id != -1) connections.push_back({ parent_id, this_id });

    for (auto i : node->branches) {
        if (i == nullptr) {
            continue;
            int tmp_id = ++id_counter;
            connections.push_back({ this_id, tmp_id });
            //all_child_rects.push_back({ "null", to_string(rand()), {{0, 0}, {size_x, size_y}} });
            all_child_rects.push_back({ "null", tmp_id, { {this_size.x, -size_y}, {size_x, size_y} } });
            child_sizes.push_back({ size_x, size_y });
            this_size.x += size_x;
        } else {
            auto calc_res = calcNodeSz(i, this_id);

            for (auto& i : calc_res.first) {
                i.rect.pos.x += this_size.x;
                i.rect.pos.y -= size_y;
            }

            if (calc_res.second.y > this_size.y) this_size.y = calc_res.second.y;
            this_size.x += calc_res.second.x;

            all_child_rects.insert(all_child_rects.end(), calc_res.first.begin(), calc_res.first.end());
        }
    }
    if (this_size.x < size_x) this_size.x = size_x;
    this_size.y += size_y;
    all_child_rects.push_back({ to_string(node->data), this_id, {{this_size.x / 2 - size_x / 2, 0} , {size_x, size_y} } });
    return { all_child_rects, this_size };
}

template<typename T>
pair<string, string> toJson(TreeNode<T>* node) {
    id_counter = 0;
    auto calc_res = calcNodeSz(node, -1).first;
    string json = "{";
    for (int i = 0; i < calc_res.size(); ++i) {
        auto curr_node = calc_res[i];
        json += "\"id_" + to_string(curr_node.id) + "\"" + ":{";
        json += "\"content\":\"" + curr_node.content + "\",";
        json += "\"x\":" + to_string(curr_node.rect.pos.x + 100) + ",";
        json += "\"y\":" + to_string(-curr_node.rect.pos.y + 100) + ",";
        json += "\"x1\":" + to_string(curr_node.rect.pos.x) + ",";
        json += "\"y1\":" + to_string(-curr_node.rect.pos.y);
        json += "}";
        json += (i == calc_res.size() - 1 ? "" : ",");
    }
    json += "}";


    string lines_json = "{";
    for (int i = 0; i < connections.size(); ++i) {
        auto curr_line = connections[i];
        lines_json += "\"" + to_string(rand() + rand()) + "\"" + ":{";
        lines_json += "\"a\":\"id_" + to_string(curr_line.first) + "\",";
        lines_json += "\"b\":\"id_" + to_string(curr_line.second) + "\"";
        lines_json += "}";
        lines_json += (i == connections.size() - 1 ? "" : ",");
    }
    lines_json += "}";
    return { json, lines_json };
}
