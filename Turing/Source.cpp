#include <iostream>
#include <string>
#include <vector>
#include "turing.h"
int main() {
	//std::vector<Act> a = { Act };
	TuringMachine a_to_b("aaaa", {
		{"a", {{"b", rt}}},
		{"~", {ST}}
	});
	TuringMachine wtf("aaabbbaaa", {
		{"a", { {"c", nn, 1},    NN,          NN,           NN         }},
		{"b", { {"d", nn, 2},    NN,          NN,           NN         }},
		{"c", { LT,              RT,         RT,          {"a", rt} }},
		{"d", { LT,              RT,         RT,          {"b", rt} }},
		{"~", { {SKIP, rt, 3}, {"c", nn, 0}, {"d", nn, 0}, ST         }}
	}, 8);

	// modified ascii table
	std::vector<std::string> v = {
	 /*v00*/ "00",
	 /*v01*/ "01",
	 /*v02*/ "02",
	 /*v03*/ "03",
	 /*v04*/ "04",
	 /*v05*/ "05",
	 /*v06*/ "06",
	 /*v07*/ "07",
	 /*v08*/ "08",
	 /*v09*/ "09",
	 /*v0A*/ "\\n",
	 /*v0B*/ "0B",
	 /*v0C*/ "0C",
	 /*v0D*/ "0D",
	 /*v0E*/ "0E",
	 /*v0F*/ "0F",
	 /*v10*/ "10",
	 /*v11*/ "11",
	 /*v12*/ "12",
	 /*v13*/ "13",
	 /*v14*/ "14",
	 /*v15*/ "15",
	 /*v16*/ "16",
	 /*v17*/ "17",
	 /*v18*/ "18",
	 /*v19*/ "19",
	 /*v1A*/ "1A",
	 /*v1B*/ "1B",
	 /*v1C*/ "1C",
	 /*v1D*/ "1D",
	 /*v1E*/ "1E",
	 /*v1F*/ "1F",
	 /*v20*/ " ", 
	 /*v21*/ "!",
	 /*v22*/ "22",
	 /*v23*/ "23",
	 /*v24*/ "24",
	 /*v25*/ "25",
	 /*v26*/ "26",
	 /*v27*/ "27",
	 /*v28*/ "28",
	 /*v29*/ "29",
	 /*v2A*/ "2A",
	 /*v2B*/ "+ ",
	 /*v2C*/ "2C",
	 /*v2D*/ "- ",
	 /*v2E*/ "2E",
	 /*v2F*/ "/ ",
	 /*v30*/ "0",  
	 /*v31*/ "1",	 
	 /*v32*/ "2",	 
	 /*v33*/ "3",	 
	 /*v34*/ "4",	 
	 /*v35*/ "5",	 
	 /*v36*/ "6",	 
	 /*v37*/ "7",	 
	 /*v38*/ "8",	 
	 /*v39*/ "9",	 
	 /*v3A*/ "3A",
	 /*v3B*/ "3B",
	 /*v3C*/ "3C",
	 /*v3D*/ "3D",
	 /*v3E*/ "3E",
	 /*v3F*/ "3F",
	 /*v40*/ "@",  
	 /*v41*/ "A",  
	 /*v42*/ "B",  
	 /*v43*/ "C",  
	 /*v44*/ "D",  
	 /*v45*/ "E",  
	 /*v46*/ "F",  
	 /*v47*/ "G",  
	 /*v48*/ "H",  
	 /*v49*/ "I",  
	 /*v4A*/ "J",  
	 /*v4B*/ "K",  
	 /*v4C*/ "L",  
	 /*v4D*/ "M",  
	 /*v4E*/ "N",  
	 /*v4F*/ "O",
	 /*v50*/ "P",    
	 /*v51*/ "Q",	   
	 /*v52*/ "R",	   
	 /*v53*/ "S",	   
	 /*v54*/ "T",	   
	 /*v55*/ "U",	   
	 /*v56*/ "V",	   
	 /*v57*/ "W",	   
	 /*v58*/ "X",	   
	 /*v59*/ "Y",	   
	 /*v5A*/ "Z",	   
	 /*v5B*/ "5B",   
	 /*v5C*/ "5C",   
	 /*v5D*/ "5D",   
	 /*v5E*/ "5E",   
	 /*v5F*/ "_",	   
	 /*v60*/ "`",  
	 /*v61*/ "a",  
	 /*v62*/ "b",  
	 /*v63*/ "c",  
	 /*v64*/ "d",  
	 /*v65*/ "e",  
	 /*v66*/ "f",  
	 /*v67*/ "g",  
	 /*v68*/ "h",  
	 /*v69*/ "i",  
	 /*v6A*/ "j",  
	 /*v6B*/ "k",  
	 /*v6C*/ "l",  
	 /*v6D*/ "m",  
	 /*v6E*/ "n",  
	 /*v6F*/ "o",
	 /*v70*/ "p",
	 /*v71*/ "q",
	 /*v72*/ "r",
	 /*v73*/ "s",
	 /*v74*/ "t",
	 /*v75*/ "u",
	 /*v76*/ "v",
	 /*v77*/ "w",
	 /*v78*/ "x",
	 /*v79*/ "y",
	 /*v7A*/ "z",
	 /*v7B*/ "7B",
	 /*v7C*/ "7C",
	 /*v7D*/ "7D",
	 /*v7E*/ "7E",
	 /*v7F*/ "7F",
};
	// rough table
	std::vector<std::pair<cell_t, std::vector<Act>>> brainfuck_table = {
		// 0:init program pointer
		// 1:init space between programm and data pointer
		// 2:init data pointer
		// 3:find p do
		// 4:find d and increment
		// 5:find d and decrement
		// 6:find p, ++p and do (find and left side)
		//  7:helper for 6 ()
		// 8:find d and move <
		// 9:find d and move >
		// 10:set this as d and do 3
		// 11:go and check d value (doind fhen [p)
		//	12:find [p and do
		//  13:find end and skip
		//	  14:open all [
		//    15:close first {
		//    16:return all to [] and move p to end
		//   17:open all ]
		//   18:close first }
		//   19 return all to [] and move p to start
		// 20:init space between output and program
		// 21:init output pointer
		// 22:go to d
		// 23:find p, ++p and do (find and right side)
		// 24:find : and 25
		// 25 - ?: grab d to o
		// 25 - ?: grab d to o
	//                                                                                                                                                                  
	//     0               1              2         3        4              5         6         7        8              9         10       11         12             13        14          15        16          17          18        19        20               21             22        23       24
	{"~",  {ST,  {"||", rt, 2},{v[0] + "d", nn, 3}, NN,      NN,            NN,       NN,       NN,      NN,            NN,{v[0] + "d",lt, 6},NN,     NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN, {"||", lt, 21},  {"|o", rt, 1},       RT,  {"|o", rt},   NN}},
	{"||", {ST,             RT,           NN,       LT,      RT,            RT,       LT,       ST,      RT,            RT,       NN,      RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,{SKIP, rt, 24 + 128 + 127}}},
	{"+",  {{"+p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"+p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{"-",  {{"-p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"-p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{"<",  {{"<p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"<p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{">",  {{">p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {">p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{"[",  {{"[p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"[p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"{", rt},     NN,       NN,      {"{", rt, 18}, NN,       NN,       NN,              NN,            RT,       RT,      RT}},
	{"]",  {{"]p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"]p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"}", lt, 15}, NN,       NN,      {"}", lt},     NN,       NN,       NN,              NN,            RT,       RT,      RT}},
	{".",  {{".p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {".p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{".p", {NN,             RT,           NN, {SKIP, rt, 22},NN,            NN,  {".", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {".", rt, 7}, RT}},
	{"+p", {NN,             RT,           NN, {SKIP, rt, 4}, NN,            NN,  {"+", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"+", rt, 7}, RT}},
	{"-p", {NN,             RT,           NN, {SKIP, rt, 5}, NN,            NN,  {"-", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"-", rt, 7}, RT}},
	{"<p", {NN,             RT,           NN, {SKIP, rt, 8}, NN,            NN,  {"<", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"<", rt, 7}, RT}},
	{">p", {NN,             RT,           NN, {SKIP, rt, 9}, NN,            NN,  {">", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {">", rt, 7}, RT}},
	{"[p", {NN,             RT,           NN, {SKIP, rt, 11},NN,            NN,  {"[", rt, 7},  NN,      NN,            NN,       NN,      NN,   {"[", rt, 7}, {SKIP, rt, 14}, NN,    {"[", rt, 16}, NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"[", rt, 7}, RT}},
	{"]p", {NN,             RT,           NN, {SKIP, lt, 17},NN,            NN,  {"]", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,    {"]", lt, 19}, NN,       NN,              NN,            RT,  {"]", rt, 7}, RT}},
	{"{",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,    {"(", rt, 14}, NN,     {"(", lt},      NN,  {"[p", nn, 3}, NN,              NN,            RT,       NN,      NN}},
	{"}",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,  {")", rt},       NN,  {"]", rt, 7},    LT,    {")", lt, 17}, NN,       NN,              NN,            RT,       NN,      NN}},
	{"(",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"[", rt},     LT,         RT,    {"[", lt},   NN,              NN,            RT,       NN,      NN}},
	{")",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"]", rt},     LT,         RT,    {"]", lt},   NN,              NN,            RT,       NN,      NN}},
	{"|o", {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            NN,       NN,      NN}},
	{":",  {ST,             RT,           NN,       LT,      RT,            RT,       LT,       ST,      RT,            RT,       NN,      RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,      RT}},
	{",",  {{",p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {",p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT,      RT}},
	{",p", {NN,             RT,           NN, {SKIP, rt, 24},NN,            NN,  {",", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {",", rt, 7}, RT}},
	{"", {}} };
	TuringMachine brainfuck(brainfuck_table);

	for (int i = 0; i < 128; ++i)
		brainfuck.addSymbol({ v[i] + "d", {NN, NN, NN, LT, {v[i == 127? 0 : i + 1] + "d", lt, 6}, {v[i?i - 1:127] + "d", lt, 6}, NN, NN, {v[i], lt, 10}, {v[i], rt, 10}, NN, {SKIP, lt, i?12:13}, NN, NN, NN, NN, NN, NN, NN, NN, NN, NN, {SKIP, lt, 25 + i}, NN}});
	for (int i = 0; i < 128; ++i)
		//                            0   1   2   3   4   5   6   7   8   9      10             11  12  13  14  15  16  17  18  19  20  21  22  23    24
		brainfuck.addSymbol({ v[i], {NN, RT, NN, LT, RT, RT, LT, NN, RT, RT,{v[i] + "d",lt, 6}, RT, LT, LT, NN, NN, NN, NN, NN, NN, NN, NN, RT, RT, {":", rt, i + 24 + 128}} });
	std::vector<Act> tmp = {NN,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,NN,NN,NN,NN,{v[0], lt, 23},LT,LT,LT};
	for (int i = 0; i < 128; ++i) tmp.push_back(NN);
	for (int i = 0; i < 128; ++i) tmp.push_back(LT);
	for (int i = 0; i < 128; ++i) {
		tmp[20].ch = v[i];
		brainfuck.addState(tmp);
	}
	//       0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 
	tmp = { NN,RT,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN,NN };
	for (int i = 0; i < 128; ++i) tmp.push_back({v[0] + "d", lt, 6});
	for (int i = 0; i < 128; ++i) tmp.push_back(RT);
	for (int i = 0; i < 128; ++i) {
		for (int j = 0; j < 128; ++j) {
			tmp[25 + j].ch = v[i] + "d";
		}
		brainfuck.addState(tmp);
	}

	// Hello world!
	std::cout << brainfuck.getRes("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.:aab");

	// 2
	//std::cout << brainfuck.getRes(",>,>,>>++++++++[-<++++++>>++++++<]<[-<<<->->->]<<<[->++++++++++<]>[-<+++++>]>>>>++<<<<<[->>>>>.>+<<<<<<[->>>>>-------.+++++++.<<<<<]]>>[->>>>[-<-------.+++++++>]<.---.+++.<<<[->>>-------.+++++++.---.+++.<<<]]:010", 1);
	//+
	//std::cout << brainfuck.getRes("+++++++++>[][].", 1000);
}