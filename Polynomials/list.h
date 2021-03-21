#pragma once
#include "stdafx.h"

template <typename T>
class Node {
 public:
  T data;
  Node *prev = nullptr, *next = nullptr;
  Node(T t) { data = t; }
  ~Node() {
    if (prev) prev->next = next;
    if (next) next->prev = prev;
  }
};

template <typename T>
class List {
 public:
  int size = 0;
  Node<T>*begin = nullptr, *end = nullptr;
  function<bool(T, T)> less_f;
  List<T> copy() {
    Node<T>* prev = nullptr;
    List<T> new_list;
    for (auto i = begin; i != nullptr; i = i->next) {
      new_list.pushBack(i->data);
    }
    return new_list;
  }
  bool empty() { return size == 0; }
  void remove(Node<T>* nd) {
    if (!nd) return;
    if (nd == begin) begin = nd->next;
    if (nd == end) end = nd->prev;
    --size;
  }
  void insertAfter(Node<T>* nd, T t) {
    ++size;
    Node<T>* new_node = new Node<T>(t);
    if (nd) {
      if (nd->next)
        nd->next->prev = new_node;
      else
        end = new_node;
      new_node->prev = nd;
      new_node->next = nd->next;
      nd->next = new_node;
    } else {
      if (!end) end = new_node;
      new_node->next = begin;
      if (begin) begin->prev = new_node;
      begin = new_node;
    }
  }
  Node<T>* find(T t) {
    for (auto i = begin; i != nullptr; i = i->next) {
      if (i->data == t) return i;
    }
    return nullptr;
  }
  template <typename T_find>
  Node<T>* find(T_find t, function<bool(T_find, T)> eq_f) {
    for (auto i = begin; i != nullptr; i = i->next) {
      if (eq_f(t, i->data)) return i;
    }
    return nullptr;
  }
  void clear() {
    for (auto i = begin; i != nullptr;) {
      auto next = i->next;
      delete i;
      i = next;
    }
  }
  void pushBack(T t) { insertAfter(end, t); }
};

template <typename T>
class SortedList : public List<T> {
 public:
  function<bool(T, T)> less;
  SortedList(function<bool(T, T)> cmp_) { less = cmp_; }
  void insert(T t) {
    Node<T>* last = nullptr;
    for (Node<T>* i = List<T>::begin; i != nullptr; i = i->next) {
      if (less(i->data, t) == false) {
        List<T>::insertAfter(last, t);
        return;
      }
    }
    List<T>::insertAfter(List<T>::end, t);
  }
  SortedList<T> copy() {
    Node<T>* prev = nullptr;
    SortedList<T> new_list{less};
    for (auto i = List<T>::begin; i != nullptr; i = i->next) {
      new_list.insert(i->data);
    }
    return new_list;
  }
  void pushBack(T t) { insert(t); }
};
