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
	//csv
#pragma region csv
	enum class CSVState {
		UnquotedField,
		QuotedField,
		QuotedQuote
	};

	std::vector<std::string> readCSVRow(const std::string& row) {
		CSVState state = CSVState::UnquotedField;
		std::vector<std::string> fields{ "" };
		size_t i = 0; // index of the current field
		for (char c : row) {
			switch (state) {
			case CSVState::UnquotedField:
				switch (c) {
				case ',': // end of field
					fields.push_back(""); i++;
					break;
				case '"': state = CSVState::QuotedField;
					break;
				default:  fields[i].push_back(c);
					break;
				}
				break;
			case CSVState::QuotedField:
				switch (c) {
				case '"': state = CSVState::QuotedQuote;
					break;
				default:  fields[i].push_back(c);
					break;
				}
				break;
			case CSVState::QuotedQuote:
				switch (c) {
				case ',': // , after closing quote
					fields.push_back(""); i++;
					state = CSVState::UnquotedField;
					break;
				case '"': // "" -> "
					fields[i].push_back('"');
					state = CSVState::QuotedField;
					break;
				default:  // end of quote
					state = CSVState::UnquotedField;
					break;
				}
				break;
			}
		}
		return fields;
	}
	std::vector<std::string> split(const std::string& str, const std::string& delim) {
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do {
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos - prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());
		return tokens;
	}
	/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
	std::vector<std::vector<std::string>> readCSV(std::string& str) {
		std::vector<std::vector<std::string>> table;
		for (auto i : split(str, "\n"))
			table.push_back(readCSVRow(i));
		return table;
	}
	std::vector<std::vector<std::string>> readCSV(std::istream& in) {
		std::vector<std::vector<std::string>> table;
		std::string row;
		while (!in.eof()) {
			std::getline(in, row);
			if (in.bad() || in.fail()) {
				break;
			}
			auto fields = readCSVRow(row);
			table.push_back(fields);
		}
		return table;
	}
#pragma endregion
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

	int add_left;
	int add_right;
	int iteration = 0;
	const int max_iterations = 100000000;

	void createOptimizedTable() {
		optimized_table.clear();
		for (auto i : table) optimized_table.insert(i);
	}
	std::vector<std::pair<cell_t, std::vector<Act>>> parceStrToTable(std::string str) {
		auto csv_input = readCSV(str);

		std::vector<std::pair<cell_t, std::vector<Act>>> table;
		for (auto i : csv_input) {
			std::pair<cell_t, std::vector<Act>> line;
			for (size_t j = 0; j < i.size(); ++j) {
				if (j == 0) {
					line.first = i[0];
				}
				else {
					Act tmp_act;
					if (i[j] == "ST") tmp_act = ST;
					if (i[j] == "LT") tmp_act = LT;
					if (i[j] == "RT") tmp_act = RT;
					if (i[j] == "NN") tmp_act = NN;
					else {
						tmp_act.ch = i[j];
						if (i[j + 1] == "<") tmp_act.dir = lt;
						if (i[j + 1] == ">") tmp_act.dir = rt;
						if (i[j + 1] == "lt") tmp_act.dir = lt;
						if (i[j + 1] == "rt") tmp_act.dir = rt;
						if (i[j + 1] == "=") tmp_act.dir = nn;
						if (i[j + 1] == "nn") tmp_act.dir = nn;
						tmp_act.q = std::stoi(i[j + 2]);
						j += 2;
					}
					line.second.push_back(tmp_act);
				}
			}
			table.push_back(line);
		}
		return table;
	}
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
		add_right = s.size();
		createOptimizedTable();
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
				++add_left;
				curr->left = tmp_cell;
			}
			curr = curr->left;
		}
		else if (act.dir == rt) {
			if (curr->right == nullptr) {
				tmp_cell = new Cell{ "~", curr, nullptr };
				++add_right;
				curr->right = tmp_cell;
			}
			curr = curr->right;
		}
	}
	std::string toStrUnity() {
		std::string res;
		Cell* left = anchor;
		while (left->left != nullptr) left = left->left;
		int pos = 0;
		while (left != nullptr) {
			if (left == curr) break;
			else ++pos;
			left = left->right;
		}
		res += std::to_string(pos);
		res += "&";
		res += std::to_string(state);
		res += "&";
		for (int i = 0; i < add_left; ++i) res += "l";
		for (int i = 0; i < add_right; ++i) res += "r";
		add_left = 0;
		add_right = 0;
		
		while (left->left != nullptr) left = left->left;
		while (left != nullptr) {
			res += "`";
			res += left->ch;
			left = left->right;
		}
		res += "%";
		return res;
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
	void safeIterate() {
		try {
			iterate();
		}
		catch (const std::runtime_error& err) {
			//std::cout << err.what() << std::endl;
		}
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
		std::cout << "Run time: " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms iterations: " << iteration <<  "\n";
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