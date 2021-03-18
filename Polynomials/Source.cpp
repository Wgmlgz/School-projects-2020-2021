#include "stdafx.h"
#include "polinom.h"

int main() {
	List<pair<string, int>> vars1;
	vars1.pushBack({ "x", 2 });

	List<pair<string, int>> vars2;
	vars2.pushBack({ "x", 3 });
	vars2.pushBack({ "y", 4 });

	Polinom t;
	t.data.pushBack({ 2, vars1});
	t.data.pushBack({ 4, vars2});

	List<pair<string, int>> vals;
	vals.pushBack({ "x", 2 });
	vals.pushBack({ "y", 3 });

	cout << t.toStr() << " = " << t.valAtPoint(vals) << endl;
	cout << "(" << t.toStr() << ")' = " << t.derivative("x").toStr() << endl;
}