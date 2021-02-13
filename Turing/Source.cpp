#include <iostream>
#include <string>
#include <vector>
#include "turing.h"

int main() {
	std::vector<TuringMachine::Action> a = { TuringMachine::Action({'b', TuringMachine::Action::right}) };
	TuringMachine tm("aa", { std::make_pair('a', a) });
	std::cout << tm.toStr();
}