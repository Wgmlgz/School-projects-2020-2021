#include "stdafx.h"
#include "polinom.h"

int main() {
	SortedList<Polinom::Monom::VarT> vars1{Polinom::Monom::VarT::isLessVar};
	vars1.insert({ 'x', 2 });

	SortedList<Polinom::Monom::VarT> vars2{ Polinom::Monom::VarT::isLessVar };
	vars2.insert({ 'y', 4 });
	vars2.insert({ 'x', 2 });
	

	Polinom t, t2;
	t.data.insert({ 2, vars1});
	t.data.insert({ 4, vars2});

	//List<pair<char, int>> vals;
	//vals.pushBack({ 'x', 2 });
	//vals.pushBack({ 'y', 3 });

	//cout << t.toStr() << ") + (" << t2.toStr() << " = ";
	//cout << (t + t2).toStr() << endl;
	char der_ch = 'z';
	cout << "d/d" << der_ch << "(" << t.toStr() << ") = " << t.derivative(der_ch).toStr() << endl;
}