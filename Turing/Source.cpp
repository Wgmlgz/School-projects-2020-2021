#include <iostream>
#include <string>
#include <vector>
#include "turing.h"

int main() {
	//std::vector<Act> a = { Act };
	TuringMachine a_to_b("aaaa", {
		{'a', {{'b', right}}},
		{'~', {STOP}}
	});
	TuringMachine wtf("aaabbbaaa", {
		{'a', { {'c', none, 1},    NONE,          NONE,           NONE         }},
		{'b', { {'d', none, 2},    NONE,          NONE,           NONE         }},
		{'c', { LEFT,              RIGHT,         RIGHT,          {'a', right} }},
		{'d', { LEFT,              RIGHT,         RIGHT,          {'b', right} }},
		{'~', { {SKIP, right, 3}, {'c', none, 0}, {'d', none, 0}, STOP         }}
	}, 8);
	std::cout << wtf.getRes(false);
}