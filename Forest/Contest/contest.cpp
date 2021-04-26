// #include <random>
// #include <iostream>
// #include <vector>
// #include <stdio.h>      /* printf, scanf, puts, NULL */
// #include <stdlib.h>     /* srand, rand */
// #include <time.h>      

// struct item {
//     int key, prior, index;
//     item * lhs = nullptr, * rhs = nullptr;
//     item() { }
//     item (int key, int prior) : key(key), prior(prior), lhs(NULL), rhs(NULL) { }
// };

// using node_ptr = item *;

// void split (node_ptr tree, int key, node_ptr & left, node_ptr & right) {
//     if (!tree)
//         left = right = NULL;
//     else if (key < tree->key)
//         split (tree->lhs, key, left, tree->lhs),  right = tree;
//     else
//         split (tree->rhs, key, tree->rhs, right),  left = tree;
// }

// void insert (node_ptr & t, node_ptr it) {
//     if (!t)
//         t = it;
//     else if (it->prior > t->prior)
//         split (t, it->key, it->lhs, it->rhs),  t = it;
//     else
//         insert (it->key < t->key ? t->lhs : t->rhs, it);
// }

// void merge (node_ptr & t, node_ptr l, node_ptr r) {
//     if (!l || !r)
//         t = l ? l : r;
//     else if (l->prior > r->prior)
//         merge (l->rhs, l->rhs, r),  t = l;
//     else
//         merge (r->lhs, l, r->lhs),  t = r;
// }

// void erase (node_ptr & t, int key) {
//     if (t->key == key) {
//         node_ptr th = t;
//         merge (t, t->lhs, t->rhs);
//         delete th;
//     }
//     else
//         erase (key < t->key ? t->lhs : t->rhs, key);
// }

// node_ptr unite (node_ptr l, node_ptr r) {
//     if (!l || !r)  return l ? l : r;
//     if (l->prior < r->prior)  std::swap (l, r);
//     node_ptr lt, rt;
//     split (r, l->key, lt, rt);
//     l->lhs = unite (l->lhs, lt);
//     l->rhs = unite (l->rhs, rt);
//     return l;
// }

// node_ptr next(int input, node_ptr node) {
//     if (!node)
//         return nullptr;
//     if (node->key == input)
//         return node;
//     if (node->key < input) {
//         return next(input, node->rhs);
//     } else {
//         auto find_res = next(input, node->lhs);
//         return find_res ? find_res : node;
//     }
// }

// void print(node_ptr node) {
//     if (!node) return;
//     print(node->lhs);
//     std::cout << node->index << " ";
//     print(node->rhs);
// }


// int index_counter = 0;
// void set_index(node_ptr node) {
//     if (!node) return;
//     set_index(node->lhs);
//     node->index = index_counter++;
//     set_index(node->rhs);
// }

// void set_key(node_ptr node) {
//     if (!node) return;
//     set_index(node->lhs);
//     node->key = index_counter++;
//     set_index(node->rhs);
// }
// int main() {
//     srand (time(NULL));
//     node_ptr tr;
//     int fst, lst, numbers, requests;
//     //char ch;

//     std::cin >> numbers >> requests;
//     for (int i = 0; i < numbers; i++) {
//         auto t = new item(i, rand());

//         insert(tr, t);
//     }
//     std::cout << "end input" << std::endl;
//     index_counter = 0;
//     set_index(tr);

//     for (int counter = 0; counter < requests; ++counter) {
//         std::cin >> fst >> lst;
//         --fst;
//         --lst;
//         node_ptr less = NULL, tt = NULL, eq = NULL, more = NULL;
//         split(tr, fst, less, tt);
//         split(tt, lst, eq, more);
        
//         print(less);
//         std::cout << std::endl;
//         print(eq);
//         std::cout << std::endl;
//         print(more);
//         std::cout << std::endl;
//         index_counter = 0;
//         set_key(less);
//         set_key(eq);
//         merge(tt, eq, less);
//         merge(tr, tt, more);
//         print(tr);
//         std::cout << std::endl;
//     }
//     print(tr);
// }
