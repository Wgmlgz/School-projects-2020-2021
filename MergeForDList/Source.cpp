#include <iostream>
#include <utility>
#include <ctime>
using std::pair;

struct node {
	node* l = nullptr;
	node* r = nullptr;
	int data = 0;
};
using np = node*;
using lst = pair<np, np>;

lst genRandomList(int sz) {
	np cur = nullptr;
	np h = nullptr;
	for (int i = 0; i < sz; ++i) {
		auto t = new node;
		t->data = rand() % 10;
		if (cur) cur->r = t;
		if (!h) h = t;
		t->l = cur;
		cur = t;
	}
	return { h, cur };
}
void printList(lst ls) {
	auto cur = ls.first;
	while (cur != nullptr) {
		std::cout << cur->data << " ";
		cur = cur->r;
	}
	std::cout << std::endl;
}

lst merge(lst a, lst b) {
	lst ret;
	auto prev = a.first->l;
	auto end = b.second->r;
	np ap = a.first;
	np bp = b.first;
	np rp;
	a.second->r = nullptr;
	b.second->r = nullptr;
	a.first->l = nullptr;
	b.first->l = nullptr;

	if (ap->data < bp->data) {
		rp = ap;
		ap = ap->r;
	}
	else {
		rp = bp;
		bp = bp->r;
	}
	ret.first = rp;
	if (prev) prev->r = rp;

	while (ap != nullptr && bp != nullptr) {
		if (ap->data < bp->data) {
			rp->r = ap;
			ap->l = rp;
			ap = ap->r;
		}
		else {
			rp->r = bp;
			bp->l = rp;
			bp = bp->r;
		}
		rp = rp->r;
	}

	if (ap != nullptr) {
		rp->r = ap;
		ap->l = rp;
		if (end) { end->l = a.second; a.second->r = end;}
		ret.second = a.second;
	}
	else if (bp != nullptr) {
		rp->r = bp;
		bp->l = rp;
		if (end) { end->l = b.second; b.second->r = end; }
		ret.second = b.second;
	}

	return ret;
}
lst mergeSort(lst& ls, size_t sz = -1) {
	if (sz == 1) return ls;
	if (sz == -1) {
		sz = 0;
		auto t = ls.first;
		while (t != nullptr) {
			t = t->r;
			++sz;
		}
	}
	lst a = { ls.first, nullptr };
	lst b = { nullptr, ls.second };

	np mid = ls.first;
	for (int i = 0; i < sz / 2; ++i) mid = mid->r;
	a.second = mid->l;
	b.first = mid;
	a = mergeSort(a, sz / 2);
	b = mergeSort(b, sz - sz / 2);
	auto ret = merge(a, b);
	ls = ret;
	return ret;
}
int main() {
	srand(time(0));
	auto L = genRandomList(15);
	printList(L);
	mergeSort(L);
	printList(L);
}