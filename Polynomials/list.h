#pragma once
#include "stdafx.h"

template<typename T>
class Node {
public:
	T data;
	Node* prev = nullptr, * next = nullptr;
	Node(T t) {
		data = t;
	}
	~Node() {
		if (prev) prev->next = next;
		if (next) next->prev = prev;
	}
};

template<typename T>
class List {
public:
	int size = 0;
	Node<T>* begin = nullptr, * end = nullptr;
	function<bool(T, T)> less_f;
	List<T> copy() {
		Node<T>* prev = nullptr;
		List<T> new_list;
		for (auto i = begin; i != nullptr; i = i->next) {
			new_list.pushBack(i->data);
		}
		return new_list;
	}
	bool empty() {
		return size == 0;
	}
	void remove(Node<T>* nd) {
		if (!nd) return;
		if (nd == begin) begin = nd->next;
		if (nd == end) end = nd->prev;
		--size;
	}
	void insAfter(Node<T>* nd, T t) {
		if (!nd) {
			if (begin == nullptr) {
				Node<T>* new_node = new Node<T>(t);
				begin = new_node;
				end = new_node;
				++size;
				return;
			} else {
				throw std::exception("Cannot insert element after nullptr");
			}
		}
		Node<T>* new_node = new Node<T>(t);
		if (nd->next) nd->next->prev = new_node;
		else end = new_node;
		new_node->prev = nd;
		new_node->next = nd->next;
		nd->next = new_node;
		++size;
	}
	Node<T>* find(T t) {
		for (auto i = begin; i != nullptr; i = i->next) {
			if (i->data == t) return i;
		}
		return nullptr;
	}
	template<typename T_find>
	Node<T>* find(T_find t, function<bool(T_find, T)> eq_f) {
		for (auto i = begin; i != nullptr; i = i->next) {
			if (eq_f(t, i->data)) return i;
		}
		return nullptr;
	}
	void pushBack(T t) {
		insAfter(end, t);
	}
};