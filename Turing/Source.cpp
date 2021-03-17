#include <iostream>
#include <string>
#include <vector>
#include "turing.h"
#include "brainfuck.h"
int main() {
	//std::vector<Act> a = { Act };
	TuringMachine* a_to_b = new TuringMachine("aaaa", {
				{"a", {{"b", rt}}},
				{"~", {RT}}
		});
	TuringMachine wtf("aaabbbaaa", {
		{"a", { {"c", nn, 1},    NN,          NN,           NN         }},
		{"b", { {"d", nn, 2},    NN,          NN,           NN         }},
		{"c", { LT,              RT,         RT,          {"a", rt} }},
		{"d", { LT,              RT,         RT,          {"b", rt} }},
		{"~", { {SKIP, rt, 3}, {"c", nn, 0}, {"d", nn, 0}, ST         }}
	}, 8);

	auto da = TuringMachine("   a   ,   b   ,   >   ,     0\n~,  ~    ,=,-1","aaaaaaa");
	auto brainfuck = brainfuckTM();
	//auto t = brainfuck.parceStrToTable("   a   ,   b   ,   >   ,     0\n~,  ~    ,=,-1");
	//brainfuck.table = t;
	brainfuck.setDefault("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.:aab");
	//brainfuck.setDefault("aaaaaaa");
	brainfuck.run(100);
	std::cout << brainfuck.toStr() << std::endl;
	//for (int i = 0; i < 10000000; ++i) {
	//
	//	//std::cout << brainfuck.toStrUnity() << std::endl;
	//	std::cout << brainfuck.toStr() << std::endl;
	//	brainfuck.safeIterate();
	//}

	
	// Hello world!
	//std::cout << brainfuck.getRes("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.:aab", 100);

	// 2
	//std::cout << brainfuck.getRes(",>,>,>>++++++++[-<++++++>>++++++<]<[-<<<->->->]<<<[->++++++++++<]>[-<+++++>]>>>>++<<<<<[->>>>>.>+<<<<<<[->>>>>-------.+++++++.<<<<<]]>>[->>>>[-<-------.+++++++>]<.---.+++.<<<[->>>-------.+++++++.---.+++.<<<]]:010", 1);
	//+
	//std::cout << brainfuck.getRes("+++++++++>[][].", 1000);
}