#pragma once
#include "stdafx.h"
#include "list.h"

int powInt(int x, int n) {
	int y = 1;
	for (int i = 0; i < n; i++) y *= x;
	return y;
}
auto eqName = [](string a, pair<string, int> b) -> bool { return a == b.first; };
class Polinom {
public:
	class Monom {
	public:
		int mult_val;
		List<pair<string, int>> vars;
		int valAtPoint(List<pair<string, int>> vals) {
			int control_sum = 0;
			int mult = 1;
			for (auto i = vals.begin; i != nullptr; i = i->next) {
				auto find_res = vars.find<string>(i->data.first, eqName);
				if (find_res) {
					mult *= powInt(i->data.second, find_res->data.second);
					++control_sum;
				}
			}
			if (control_sum > vars.size)
				throw std::exception("Too many variables found (maybe some copies)");
			if (control_sum < vars.size)
				throw std::exception("Not all variables were initialized");
			return mult_val * mult;
		}
	};
	List<Monom> data;

	void insetrMonom(Monom monom) {
		for (auto i = data.begin; i != nullptr; i = i->next) {
			auto i_d = i->data;
			//if ()
		}
	}
	void fromStr(string str) {

	}
	string toStr() {
		string ret;
		for (auto i = data.begin; i != nullptr; i = i->next) {
			auto i_d = i->data;
			string monom_str;

			monom_str += std::to_string(i_d.mult_val);
			for (auto i = i_d.vars.begin; i != nullptr; i = i->next) {
				//if (!(i == i_d.vars.begin && i_d.mult_val == 1)) monom_str += "*";
				if (i->data.second != 0) {
					monom_str += i->data.first;
					if (i->data.second != 1) {
						monom_str += "^";
						monom_str += std::to_string(i->data.second);
					}
				}
			}
			ret += monom_str;

			if (i != data.end) ret += " + ";
		}
		
		return ret;
	}
	Polinom(List<Monom> data_) {
		data = data_;
	}
	Polinom(string str) {

	}
	Polinom() {

	}

	// methods
	int valAtPoint(List<pair<string, int>> vals) {
		int sum = 0;
		for (auto i = data.begin; i != nullptr; i = i->next) sum += i->data.valAtPoint(vals);
		return sum;
	}
	Polinom derivative(string var, int n) {
		if (n == 0) return *this;
		if (n < 0) throw std::exception("Bruh, bro that's cringe(((((");
		Polinom der;
		auto poli_copy = data;
		for (auto i = data.begin; i != nullptr; i = i->next) {
			auto i_d = i->data;
			auto vars_copy = i_d.vars.copy();
			auto find_res = vars_copy.find<string>(var, eqName);
			if (find_res) {
				auto mult_val = i_d.mult_val * find_res->data.second;
				if (find_res->data.second == 1) vars_copy.remove(find_res);
				else --find_res->data.second;
				der.data.pushBack({mult_val, vars_copy});
			}
		}
		if (n == 1) {
			return der;
		} else {
			return der.derivative(var, n - 1);
		}
	}
};