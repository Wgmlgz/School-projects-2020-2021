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
	 /*v2B*/ "2B",
	 /*v2C*/ "2C",
	 /*v2D*/ "2D",
	 /*v2E*/ "2E",
	 /*v2F*/ "2F",
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
	std::vector<std::pair<cell_t, std::vector<Act>>> brain_fuck_table = {
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
		//  
		//   17:open all ]
		//   18:close first }
		//   19 return all to [] and move p to start
		// 20:init space between output and program
		// 21:init output pointer
		// 22:go to d
		// 23:find p, ++p and do (find and right side)
		// 24 - ?: grab d to o
	//                                                                                                                                                                  
	//     0               1              2         3        4              5         6         7        8              9         10       11         12             13        14          15        16          17          18        19        20               21             22        23     
	{"~",  {ST,  {"__", rt, 2},{v[0] + "d", nn, 3}, NN,      NN,            NN,       NN,       NN,      NN,            NN,{v[0] + "d",lt, 6},NN,     NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN, {"__", lt, 21},  {"_o", rt, 1},       RT,  {"_o", rt}   }},
	{"__", {ST,             RT,           NN,       LT,      RT,            RT,       LT,       ST,      RT,            RT,       NN,      RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT      }},
	{"+",  {{"+p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"+p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT      }},
	{"-",  {{"-p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"-p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT      }},
	{"<",  {{"<p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"<p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT      }},
	{">",  {{">p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {">p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT      }},
	{"[",  {{"[p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"[p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"{", rt},     NN,       NN,      {"{", rt, 18}, NN,       NN,       NN,              NN,            RT,       RT      }},
	{"]",  {{"]p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {"]p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"}", lt, 15}, NN,       NN,      {"}", lt},     NN,       NN,       NN,              NN,            RT,       RT      }},
	{".",  {{".p", lt, 20}, RT,           NN,       LT,      RT,            RT,       LT, {".p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,         LT,         RT,       LT,       NN,              NN,            RT,       RT      }},
	{".p", {NN,             RT,           NN, {SKIP, rt, 22},NN,            NN,  {".", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {".", rt, 7} }},
	{"+p", {NN,             RT,           NN, {SKIP, rt, 4}, NN,            NN,  {"+", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"+", rt, 7} }},
	{"-p", {NN,             RT,           NN, {SKIP, rt, 5}, NN,            NN,  {"-", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"-", rt, 7} }},
	{"<p", {NN,             RT,           NN, {SKIP, rt, 8}, NN,            NN,  {"<", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"<", rt, 7} }},
	{">p", {NN,             RT,           NN, {SKIP, rt, 9}, NN,            NN,  {">", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,  {">", rt, 7} }},
	{"[p", {NN,             RT,           NN, {SKIP, rt, 11},NN,            NN,  {"[", rt, 7},  NN,      NN,            NN,       NN,      NN,   {"[", rt, 7}, {SKIP, rt, 14}, NN,    {"[", rt, 16}, NN,         NN,         NN,       NN,       NN,              NN,            RT,  {"[", rt, 7} }},
	{"]p", {NN,             RT,           NN, {SKIP, lt, 17},NN,            NN,  {"]", rt, 7},  NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,    {"]", lt, 19}, NN,       NN,              NN,            RT,  {"]", rt, 7} }},
	{"{",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,    {"(", rt, 14}, NN,     {"(", lt},      NN,  {"[p", nn, 3}, NN,              NN,            RT,       NN      }},
	{"}",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,  {")", rt},       NN,  {"]", rt, 7},    LT,    {")", lt, 17}, NN,       NN,              NN,            RT,       NN      }},
	{"(",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"[", rt},     LT,         RT,    {"[", lt},   NN,              NN,            RT,       NN      }},
	{")",  {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"]", rt},     LT,         RT,    {"]", lt},   NN,              NN,            RT,       NN      }},
	{"_o", {NN,             NN,           NN,       NN,      NN,            NN,       NN,       NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            NN,       NN      }},
	//{v[0]+"d", {NN,          NN,           NN,       LT, {v[1] + "d", lt, 6}, {v[127] + "d", lt, 6}, NN,       NN, {v[0], lt, 10}, {v[0], rt, 10}, NN, {SKIP, lt, 13}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  0}, NN,          NN                                        }},
	//{v01+"d", {NN,          NN,           NN,       LT, {"2d", lt, 6}, {"0d", lt, 6}, NN,       NN, {v01, lt, 10}, {v01, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  1}, NN,          NN                  }},
	//{v02+"d", {NN,          NN,           NN,       LT, {"3d", lt, 6}, {"1d", lt, 6}, NN,       NN, {v02, lt, 10}, {v02, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  2}, NN,          NN                  }},
	//{v03+"d", {NN,          NN,           NN,       LT, {"4d", lt, 6}, {"2d", lt, 6}, NN,       NN, {v03, lt, 10}, {v03, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  3}, NN,          NN                  }},
	//{v04+"d", {NN,          NN,           NN,       LT, {"5d", lt, 6}, {"3d", lt, 6}, NN,       NN, {v04, lt, 10}, {v04, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  4}, NN,          NN                  }},
	//{v05+"d", {NN,          NN,           NN,       LT, {"6d", lt, 6}, {"4d", lt, 6}, NN,       NN, {v05, lt, 10}, {v05, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  5}, NN,          NN                  }},
	//{v06+"d", {NN,          NN,           NN,       LT, {"7d", lt, 6}, {"5d", lt, 6}, NN,       NN, {v06, lt, 10}, {v06, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  6}, NN,          NN                  }},
	//{v07+"d", {NN,          NN,           NN,       LT, {"8d", lt, 6}, {"6d", lt, 6}, NN,       NN, {v07, lt, 10}, {v07, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  7}, NN,          NN                  }},
	//{v08+"d", {NN,          NN,           NN,       LT, {"9d", lt, 6}, {"7d", lt, 6}, NN,       NN, {v08, lt, 10}, {v08, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  8}, NN,          NN                  }},
	//{v09+"d", {NN,          NN,           NN,       LT, {"Ad", lt, 6}, {"8d", lt, 6}, NN,       NN, {v09, lt, 10}, {v09, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 +  9}, NN,          NN                  }},
	//{v0A+"d", {NN,          NN,           NN,       LT, {"Bd", lt, 6}, {"9d", lt, 6}, NN,       NN, {v0A, lt, 10}, {v0A, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 10}, NN,          NN                  }},
	//{v0B+"d", {NN,          NN,           NN,       LT, {"Cd", lt, 6}, {"Ad", lt, 6}, NN,       NN, {v0B, lt, 10}, {v0B, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 11}, NN,          NN                  }},
	//{v0C+"d", {NN,          NN,           NN,       LT, {"Dd", lt, 6}, {"Bd", lt, 6}, NN,       NN, {v0C, lt, 10}, {v0C, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 12}, NN,          NN                  }},
	//{v0D+"d", {NN,          NN,           NN,       LT, {"Ed", lt, 6}, {"Cd", lt, 6}, NN,       NN, {v0D, lt, 10}, {v0D, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 13}, NN,          NN                  }},
	//{v0E+"d", {NN,          NN,           NN,       LT, {"Fd", lt, 6}, {"Dd", lt, 6}, NN,       NN, {v0E, lt, 10}, {v0E, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 14}, NN,          NN                  }},
	//{v0F+"d", {NN,          NN,           NN,       LT, {"0d", lt, 6}, {"Ed", lt, 6}, NN,       NN, {v0F, lt, 10}, {v0F, rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN, {SKIP, lt, 24 + 15}, NN,          NN                  }},
	//{v00,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v00 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v01,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v01 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v02,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v02 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v03,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v03 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v04,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v04 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v05,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v05 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v06,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v06 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v07,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v07 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v08,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v08 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v09,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v09 + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0A,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0A + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0B,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0B + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0C,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0C + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0D,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0D + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0E,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0E + "d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
	//{v0F,  {NN,             NN,           NN,       LT,      RT,            RT,       LT,       NN,      RT,            RT,{v0F+"d",lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,         NN,         NN,       NN,       NN,              NN,            RT,       RT,         LT                  }},
		  //{"<p", {NONE,             NONE,                                  }},
		  //{">p", {NONE,             NONE,                                   }},

			//{"[", },
			//{"]", },
	{"", {}} };
	TuringMachine brain_fuck(brain_fuck_table);

	for (int i = 0; i < 128; ++i)
		brain_fuck.addSymbol({ v[i] + "d", {NN, NN, NN, LT, {v[i == 127? 0 : i + 1] + "d", lt, 6}, {v[i?i - 1:127] + "d", lt, 6}, NN, NN, {v[i], lt, 10}, {v[i], rt, 10}, NN, {SKIP, lt, i?12:13}, NN, NN, NN, NN, NN, NN, NN, NN, NN, NN, {SKIP, lt, 24 + i}, NN}});
	for (int i = 0; i < 128; ++i)
		brain_fuck.addSymbol({ v[i], {NN, NN, NN, LT, RT, RT, LT, NN, RT, RT,{v[i] + "d",lt, 6}, RT, LT, LT, NN, NN, NN, NN, NN, NN, NN, NN, RT, RT} });
	std::vector<Act> tmp = {NN,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,LT,NN,NN,NN,NN,{v[0], lt, 23}};
	for (int i = 0; i < 128; ++i) tmp.push_back(NN);
	for (int i = 0; i < 128; ++i) tmp.push_back(LT);
	for (int i = 0; i < 128; ++i) {
		tmp[20].ch = v[i];
		brain_fuck.addState(tmp);
	}

	std::cout << brain_fuck.getRes("++>+++++[<+>-]++++++++[<++++++>-]<.", 1000);
	std::cout << brain_fuck.getRes("+++++++++>[][].", 1000);
}