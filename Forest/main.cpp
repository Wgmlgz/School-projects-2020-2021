#include  "Treap.h"

const bool DEBUG = false;

int main() {
  auto tr = Treap<int>();
  int input = 0, numbers = 10, last = -1;
  char ch;

  std::cin >> numbers;
  for (int i = 0; i < numbers; ++i) {
    std::cin >> ch >> input;
    if (ch == '+') {
      if (last != -1)
        tr.insert(input + last);
      else
        tr.insert(input);
      last = -1;
    }
    else {
      auto res = tr.next(input);
      if (res) {
        std::cout << res->data << std::endl;
        last = res->data;
      }
      else {
        std::cout << -1 << std::endl;
      }
    }
    if (DEBUG) tr.root->print();
  }
}
