#include <string>

#include "bstmap.h"
//class bst : BstMap<int, int> {};

int main() {
  BstMap<int, std::string> * tree = new BstMap<int, std::string>();
  tree->add(10, std::string("ten"));
  tree->add(5, std::string("five"));
  tree->add(15, std::string("fifteen"));
  tree->add(1, std::string("one"));
  tree->add(101, std::string("hundred and one"));
  tree->inorderBst();
  tree->lookup(10);
  tree->lookup(15);
  tree->remove(10);
  tree->inorderBst();
  std::cout << tree->root->key << std::endl;
  return 0;
}
