#include <iostream>
#include <utility>

struct node { int data; node* next; };
using np = node*;
np partition(np low, np high) {
	auto pivot = high->data;
	auto i = low;
	for (auto j = low->next; j != high; j = j->next) {
		if (j->data < pivot) {
			i = i->next;
			std::swap(i->data, j->data);
		}
	}
	std::swap(i->next->data, high->data);
	return i;
}

void qsortRec(np low, np high) {
	if (low != high) {
		auto pi = partition(low, high);
		qsortRec(low, pi);
		qsortRec(pi->next, high);
	}
}

void qsort(np low, np high) {
	qsortRec(new node{ 0, low }, high);
}

void qsort(std::pair<np, np> list) {
	qsort(list.first, list.second);
}
void printList(std::pair<np, np> list) {
	for (auto i = list.first; i != nullptr; i = i->next)
		std::cout << i->data << " ";
	std::cout << std::endl;
}
std::pair<np, np> genRandomList(int n) {
	srand((int)(new int));
	np st = new node;
	np cur = st;
	for (int i = 0; i < n; ++i) {
		cur->data = rand() % 100;
		np next = new node;
		cur->next = next;
		if (i != n - 1) cur = next;
	}
	cur->next = nullptr;
	return std::make_pair(st, cur);
}
int main() {
	auto list = genRandomList(10);
	printList(list);
	qsort(list);
	printList(list);
}