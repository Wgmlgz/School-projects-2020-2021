#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <map>

using cell_t = std::string;
//using std::vector<std::pair<cell_t, std::vector<Act>>> = std::vector<std::pair<cell_t, std::vector<Act>>>;
enum class Dir { left, none, right };
const auto lt = Dir::left;
const auto rt = Dir::right;
const auto nn = Dir::none;
struct Act {
	cell_t ch = "\t";
	Dir dir = rt;
	int q = -2;
};
const cell_t SKIP = "\t";
const cell_t ERR = "ERR";
const Act ST{ SKIP , nn, -1 };
const Act LT{ SKIP , lt, -2 };
const Act RT{ SKIP , rt, -2 };
const Act NN{ ERR , nn, -2 };
class TuringMachine {
public:

	struct Cell {
		std::string ch = "~";
		Cell* left = nullptr;
		Cell* right = nullptr;
	};

	Cell* last;
	Cell* curr;
	Cell* anchor;
	int state = 0;
	//std::vector<Cell> cells;
	std::vector<std::pair<cell_t, std::vector<Act>>> table;
	std::map<cell_t, std::vector<Act>> optimized_table;

	int iteration = 0;
	const int max_iterations = 100000000;

	void setDefault(std::string s, int pos = 0) {
		state = 0;
		iteration = 0;
		Cell* left = nullptr;
		Cell* right = nullptr;
		for (auto i : s) {
			cell_t str;
			str.push_back(i);
			auto tmp_cell = new Cell{ str, left, right };
			if (left != nullptr) left->right = tmp_cell;
			else curr = tmp_cell, anchor = tmp_cell;
			left = tmp_cell;
		}
		for (int i = 0; i < pos; ++i) curr = curr->right;
	}
	void addSymbol(std::pair<cell_t, std::vector<Act>> data) {
		table.push_back(data);
	}
	void addState(std::vector<Act> data) {
		for (int i = 0; i < data.size() && i < table.size(); ++i) {
			table[i].second.push_back(data[i]);
		}
	}
	bool iterate() {
		++iteration;
		if (state == -1 || iteration > max_iterations) return false;
		Act act{ "\0" };

		auto search_res = optimized_table.find(curr->ch);
		if (search_res != optimized_table.end()) {
			if (state >= search_res->second.size() || state < 0) throw (std::runtime_error("Current state is outside of table"));
			act = search_res->second[state];
		}
		else {
			std::string er = "This symbol (" + curr->ch + ") is not allowed";
			if (act.ch == "\0") throw std::runtime_error(er.c_str());
		}		
		
		if (act.q != -2) state = act.q;
		if (act.ch == ERR) {
			std::string er = "Looks like you have some error in algorithm " + std::string(search_res->first);
			throw std::runtime_error(er.c_str());
		}
		if (act.ch != SKIP) curr->ch = act.ch;
		Cell* tmp_cell;
		if (act.dir == lt) {
			if (curr->left == nullptr) {
				tmp_cell = new Cell{ "~", nullptr, curr };
				curr->left = tmp_cell;
			}
			curr = curr->left;
		}
		else if (act.dir == rt) {
			if (curr->right == nullptr) {
				tmp_cell = new Cell{ "~", curr, nullptr };
				curr->right = tmp_cell;
			}
			curr = curr->right;
		}
	}
	std::string toStr() {
		Cell* left = anchor;
		while (left->left != nullptr) left = left->left;
		std::vector<std::string> data;
		std::string bottom;
		int max_ch_size = 1;
		int strip_size = 0;

		while (left != nullptr) {
			if (left->ch.size() > max_ch_size) max_ch_size = left->ch.size();
			++strip_size;
			left = left->right;
		}

		data.resize(max_ch_size);
		bool do_bot = true;
		left = anchor;
		while (left->left != nullptr) left = left->left;
		int pos = 0;
		while (left != nullptr) {
			auto tmp = left->ch;
			tmp.resize(max_ch_size, ' ');
			for (int i = 0; i < max_ch_size; ++i) data[i].push_back(tmp[i]);
			if (do_bot) {
				if (left == curr) {
					bottom.push_back('^');
					bottom += std::to_string(state);
					do_bot = false;
				}
				else {
					bottom.push_back(' ');
				}
			}
			left = left->right;
			++pos;
		}

		std::string res;
		for (auto i : data) res += i + "\n";
		return res + bottom;
	}
	void createOptimizedTable() {
		optimized_table.clear();
		for (auto i : table) optimized_table.insert(i);
	}
	void run(int show = -1) {
		createOptimizedTable();
		auto t_start = std::chrono::high_resolution_clock::now();
		static auto last_show = std::chrono::high_resolution_clock::now();
		try {
			do { 
				if (show == -1 || std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - last_show).count() > show) {
					std::cout << toStr() << std::endl;
					last_show = std::chrono::high_resolution_clock::now();
				}
			} while (iterate());
		}
		catch (const std::runtime_error& err) {
			std::cout << err.what() << std::endl;
		}
		auto t_end = std::chrono::high_resolution_clock::now();
		std::cout << "Run time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms\n";
	}
	std::string getRes(int show = -1) {
		run(show);
		return toStr();
	}
	std::string getRes(std::string n_str, int show = -1) {
		setDefault(n_str);
		return getRes(show);
	}
	TuringMachine(std::string s, std::vector<std::pair<cell_t, std::vector<Act>>> ntable, int pos = 0) {
		setDefault(s, pos);
		table = ntable;
	}
	TuringMachine(std::vector<std::pair<cell_t, std::vector<Act>>> ntable) {
		setDefault("", 0);
		table = ntable;
	}
};