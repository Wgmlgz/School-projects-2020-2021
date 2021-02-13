#pragma once
#include <string>
#include <vector>
#include <memory>

class TuringMachine {
public:
	struct Cell {
		char ch = '~';
		Cell* left = nullptr;
		Cell* right = nullptr;
	};
	struct Action {
		enum Dir {left, right};
		char ch = '~';
		Dir dir = right;
		int q = -2;
	};

	Cell* last;
	Cell* curr;
	int state = 0;
	std::vector<Cell> cells;
	std::vector<std::pair<char, std::vector<Action>>> table;

	int iteration = 0;
	const int max_iterations = 5000;

	void setDefault(std::string s, int pos = 0) {
		cells.clear();
		cells.resize(s.length());
		for (int i = 0; i < s.size(); ++i)     cells[i].ch    = s[i];
		for (int i = 1; i < s.size(); ++i)     cells[i].left  = &cells[i - 1];
		for (int i = 0; i < s.size() - 1; ++i) cells[i].right = &cells[i + 1];
		curr = &cells[pos];
	}
	bool iterate() {
		++iteration;
		if (state == -1 || iteration > max_iterations) return false;
		Action* act = nullptr;
		for (auto i : table) {
			if (i.first == curr->ch) {
				if (state >= i.second.size() || state < 0) throw std::exception("Current state is outside of table");
				act = &i.second[state];
			}
		}
		if (act == nullptr) throw std::exception("This symbol is not allowed");
		if (act->q != -2) state = act->q;
		curr->ch = act->ch;
		if (act->dir == Action::left) {
			if (curr->left == nullptr) cells.push_back(Cell({'~', nullptr, curr}));
			curr->left = &cells[cells.size() - 1];
			curr = curr->left;
		}
		else if (act->dir == Action::right) {
			if (curr->left == nullptr) cells.push_back(Cell({'~', curr, nullptr}));
			curr->right = &cells[cells.size() - 1];
			curr = curr->right;
		}
	}
	std::string toStr() {
		Cell* left = &cells[0];
		while (left->left != nullptr) left = left->left;
		std::string res;
		do {
			res.push_back(left->ch);
			left = left->right;
		} while (left->right != nullptr);
		return res;
	}
	TuringMachine(std::string s, std::vector<std::pair<char, std::vector<Action>>> ntable, int pos = 0) {
		setDefault(s, pos);
		do { std::cout << toStr() << std::endl; } while (iterate());
	}
};