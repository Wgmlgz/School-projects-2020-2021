#pragma once
#include <string>
#include <vector>
#include <memory>

enum class Dir { left, none, right };
const auto left = Dir::left;
const auto right = Dir::right;
const auto none = Dir::none;
struct Act {
	char ch = '\t';
	Dir dir = right;
	int q = -2;
};
const char SKIP = '\t';
const char ERR = '-';
const Act STOP{ SKIP , none, -1 };
const Act LEFT{ SKIP , left, -2 };
const Act RIGHT{ SKIP , right, -2 };
const Act NONE{ '-' , none, -2 };
class TuringMachine {
public:

	struct Cell {
		char ch = '~';
		Cell* left = nullptr;
		Cell* right = nullptr;
	};

	Cell* last;
	Cell* curr;
	Cell* anchor;
	int state = 0;
	//std::vector<Cell> cells;
	std::vector<std::pair<char, std::vector<Act>>> table;

	int iteration = 0;
	const int max_iterations = 5000;

	void setDefault(std::string s, int pos = 0) {
		Cell* left = nullptr;
		Cell* right = nullptr;
		for (auto i : s) {
			auto tmp_cell = new Cell{ i, left, right };
			if (left != nullptr) left->right = tmp_cell;
			else curr = tmp_cell, anchor = tmp_cell;
			left = tmp_cell;
		}
		for (int i = 0; i < pos; ++i) curr = curr->right;
	}
	bool iterate() {
		++iteration;
		if (state == -1 || iteration > max_iterations) return false;
		Act act{ '\0' };

		for (auto i : table) {
			if (i.first == curr->ch) {
				if (state >= i.second.size() || state < 0) throw std::exception("Current state is outside of table");
				act = i.second[state];
			}
		}
		std::string er = "This symbol ("; er.push_back(curr->ch); er += ") is not allowed";
		if (act.ch == '\0') throw std::exception(er.c_str());
		if (act.q != -2) state = act.q;
		if (act.ch == ERR) throw std::exception("Looks like you have some error in algorithm");
		if (act.ch != SKIP) curr->ch = act.ch;
		Cell* tmp_cell;
		if (act.dir == left) {
			if (curr->left == nullptr) {
				tmp_cell = new Cell{ '~', nullptr, curr };
				curr->left = tmp_cell;
			}
			curr = curr->left;
		}
		else if (act.dir == right) {
			if (curr->right == nullptr) {
				tmp_cell = new Cell{ '~', curr, nullptr };
				curr->right = tmp_cell;
			}
			curr = curr->right;
		}
	}
	std::string toStr() {

		Cell* left = anchor;
		while (left->left != nullptr) left = left->left;
		std::string top;
		std::string bottom;
		bool do_bot = true;
		do {
			top.push_back(left->ch);
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
		} while (left != nullptr);

		return top + "\n" + bottom;
	}
	void run(bool show = true) {
		try {
			do { if (show) std::cout << toStr() << std::endl; } while (iterate());
		}
		catch (const std::exception& err) {
			std::cout << err.what() << std::endl;
		}
	}
	std::string getRes(bool show = true) {
		run(show);
		return toStr();
	}
	TuringMachine(std::string s, std::vector<std::pair<char, std::vector<Act>>> ntable, int pos = 0) {
		setDefault(s, pos);
		table = ntable;
	}
};