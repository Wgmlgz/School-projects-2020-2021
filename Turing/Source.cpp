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
	//TuringMachine da("aaa", {
	//	{"a", },
	//	{},
	//	{}
	//});
TuringMachine brain_fuck("+++++[->+>+<<]", {
	    // 0:init program pointer
	    // 1:init space between programm and data pointer
		// 2:init data pointer
		// 3:find p do
		// 4:find d and increment
		// 5:find d and decrement
		// 6:find p, ++p and do
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
		//  17:none
		//   18:open all ]
		//   19:close first }
		//   20 return all to [] and move p to start
		//
//                                                                                                                                                                  
//     0               1              2              3        4              5         6             7        8              9         10       11         12             13        14          15        16        17        18          19        20
{"~",  {ST,       {"|", rt, 2}, {"0d", nn, 3},       NN,      NN,            NN,       NN,           NN,      NN,            NN, {"0d", lt, 6}, NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"|",  {ST,            NN,            NN,            LT,      RT,            RT,       LT,           ST,      RT,            RT,       NN,      RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},

{"+",  {{"+p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {"+p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,       NN,       LT,         RT,       LT       }},
{"-",  {{"-p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {"-p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,       NN,       LT,         RT,       LT       }},
{"<",  {{"<p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {"<p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,       NN,       LT,         RT,       LT       }},
{">",  {{">p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {">p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,       RT,         LT,       RT,       NN,       LT,         RT,       LT       }},

{"[",  {{"[p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {"[p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"{", rt},     NN,       NN,       NN,    {"{", rt, 19}, NN,       NN       }},
{"]",  {{"]p", rt, 1}, RT,            NN,            LT,      RT,            RT,       LT,     {"]p", nn, 3}, RT,            RT,       NN,      RT,        LT,            LT,    {"}", lt, 15}, NN,       NN,       NN,    {"}", lt},     NN,       NN       }},

{"+p", {NN,             NN,           NN,      {SKIP, rt, 4}, NN,            NN,  {"+", rt, 7},      NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"-p", {NN,             NN,           NN,      {SKIP, rt, 5}, NN,            NN,  {"-", rt, 7},      NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"<p", {NN,             NN,           NN,      {SKIP, rt, 8}, NN,            NN,  {"<", rt, 7},      NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{">p", {NN,             NN,           NN,      {SKIP, rt, 9}, NN,            NN,  {">", rt, 7},      NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},

{"[p", {NN,             NN,           NN,      {SKIP, rt, 11},NN,            NN,  {"[", rt, 7},      NN,      NN,            NN,       NN,      NN,   {"[", rt, 7}, {SKIP, rt, 14}, NN,    {"[", rt, 16}, NN,       NN,       NN,         NN,       NN       }},
{"]p", {NN,             NN,           NN,      {SKIP, lt, 18},NN,            NN,  {"]", rt, 7},      NN,      NN,            NN,       NN,      NN,        NN,            NN,       NN,         NN,       NN,       NN,       NN,    {"]", lt, 20}, NN       }},
{"{",  {NN,             NN,           NN,            NN,      NN,            NN,       NN,           NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,    {"(", rt, 14}, NN,       NN,   {"(", lt},      NN,  {"[p", nn, 3} }},
{"}",  {NN,             NN,           NN,            NN,      NN,            NN,       NN,           NN,      NN,            NN,       NN,      NN,        NN,            NN,  {")", rt},       NN,  {"]", rt, 7},  NN,       LT,    {")", lt, 18}, NN       }},
{"(",  {NN,             NN,           NN,            NN,      NN,            NN,       NN,           NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"[", rt},   NN,       LT,         RT,    {"[", lt}   }},
{")",  {NN,             NN,           NN,            NN,      NN,            NN,       NN,           NN,      NN,            NN,       NN,      NN,        NN,            NN,       RT,         LT,    {"]", rt},   NN,       LT,         RT,    {"]", lt}   }},

{"0d", {NN,             NN,           NN,            LT, {"1d", lt, 6}, {"Fd", lt, 6}, NN,           NN, {"0", lt, 10}, {"0", rt, 10}, NN, {SKIP, lt, 13}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"1d", {NN,             NN,           NN,            LT, {"2d", lt, 6}, {"0d", lt, 6}, NN,           NN, {"1", lt, 10}, {"1", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"2d", {NN,             NN,           NN,            LT, {"3d", lt, 6}, {"1d", lt, 6}, NN,           NN, {"2", lt, 10}, {"2", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"3d", {NN,             NN,           NN,            LT, {"4d", lt, 6}, {"2d", lt, 6}, NN,           NN, {"3", lt, 10}, {"3", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"4d", {NN,             NN,           NN,            LT, {"5d", lt, 6}, {"3d", lt, 6}, NN,           NN, {"4", lt, 10}, {"4", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"5d", {NN,             NN,           NN,            LT, {"6d", lt, 6}, {"4d", lt, 6}, NN,           NN, {"5", lt, 10}, {"5", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"6d", {NN,             NN,           NN,            LT, {"7d", lt, 6}, {"5d", lt, 6}, NN,           NN, {"6", lt, 10}, {"6", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"7d", {NN,             NN,           NN,            LT, {"8d", lt, 6}, {"6d", lt, 6}, NN,           NN, {"7", lt, 10}, {"7", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"8d", {NN,             NN,           NN,            LT, {"9d", lt, 6}, {"7d", lt, 6}, NN,           NN, {"8", lt, 10}, {"8", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"9d", {NN,             NN,           NN,            LT, {"Ad", lt, 6}, {"8d", lt, 6}, NN,           NN, {"9", lt, 10}, {"9", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Ad", {NN,             NN,           NN,            LT, {"Bd", lt, 6}, {"9d", lt, 6}, NN,           NN, {"A", lt, 10}, {"A", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Bd", {NN,             NN,           NN,            LT, {"Cd", lt, 6}, {"Ad", lt, 6}, NN,           NN, {"B", lt, 10}, {"B", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Cd", {NN,             NN,           NN,            LT, {"Dd", lt, 6}, {"Bd", lt, 6}, NN,           NN, {"C", lt, 10}, {"C", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Dd", {NN,             NN,           NN,            LT, {"Ed", lt, 6}, {"Cd", lt, 6}, NN,           NN, {"D", lt, 10}, {"D", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Ed", {NN,             NN,           NN,            LT, {"Fd", lt, 6}, {"Dd", lt, 6}, NN,           NN, {"E", lt, 10}, {"E", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"Fd", {NN,             NN,           NN,            LT, {"0d", lt, 6}, {"Ed", lt, 6}, NN,           NN, {"F", lt, 10}, {"F", rt, 10}, NN, {SKIP, lt, 12}, NN,            NN,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"0",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"0d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"1",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"1d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"2",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"2d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"3",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"3d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"4",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"4d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"5",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"5d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"6",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"6d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"7",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"7d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"8",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"8d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"9",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"9d", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"A",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Ad", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"B",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Bd", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"C",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Cd", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"D",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Dd", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"E",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Ed", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
{"F",  {NN,             NN,           NN,            LT,      RT,            RT,       LT,           NN,      RT,            RT, {"Fd", lt, 6}, RT,        LT,            LT,       NN,         NN,       NN,       NN,       NN,         NN,       NN       }},
	  //{"<p", {NONE,             NONE,                                  }},
	  //{">p", {NONE,             NONE,                                   }},

		//{"[", },
		//{"]", },
{"", {}} });

 

	std::cout << brain_fuck.getRes(true);
}