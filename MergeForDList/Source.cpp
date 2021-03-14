#include <iostream>
#include <utility>
#include <ctime>
using std::pair;

struct node {
	node* prev = nullptr;
	node* next = nullptr;
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
		if (cur) cur->next = t;
		if (!h) h = t;
		t->prev = cur;
		cur = t;
	}
	return { h, cur };
}
void printList(lst ls) {
	auto cur = ls.first;
	while (cur != nullptr) {
		std::cout << cur->data << " ";
		cur = cur->next;
	}
	std::cout << std::endl;
}

lst merge(lst a, lst b) {
	lst ret;
	auto prev = a.first->prev;
	auto end = b.second->next;
	np ap = a.first;
	np bp = b.first;
	np rp;
	a.second->next = nullptr;
	b.second->next = nullptr;
	a.first->prev = nullptr;
	b.first->prev = nullptr;

	if (ap->data < bp->data) {
		rp = ap;
		ap = ap->next;
	}
	else {
		rp = bp;
		bp = bp->next;
	}
	ret.first = rp;
	if (prev) prev->next = rp;

	while (ap != nullptr && bp != nullptr) {
		if (ap->data < bp->data) {
			rp->next = ap;
			ap->prev = rp;
			ap = ap->next;
		}
		else {
			rp->next = bp;
			bp->prev = rp;
			bp = bp->next;
		}
		rp = rp->next;
	}

	if (ap != nullptr) {
		rp->next = ap;
		ap->prev = rp;
		if (end) { end->prev = a.second; a.second->next = end;}
		ret.second = a.second;
	}
	else if (bp != nullptr) {
		rp->next = bp;
		bp->prev = rp;
		if (end) { end->prev = b.second; b.second->next = end; }
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
			t = t->next;
			++sz;
		}
	}
	lst a = { ls.first, nullptr };
	lst b = { nullptr, ls.second };

	np mid = ls.first;
	for (int i = 0; i < sz / 2; ++i) mid = mid->next;
	a.second = mid->prev;
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