#include "bstset.h"

int main() {
  BstSet<int> * s = new BstSet<int>();
  s->add(10);
  s->add(5);
  s->add(15);
  s->add(105);
  s->add(1);
  s->inorder_bst();
  s->remove(10);
  s->inorder_bst();
  BstSet<int> * b = new BstSet<int>(*s);
  b->add(40);
  b->add(30);
  b->add(20);
  b->add(50);
  b->add(45);
  b->add(25);
  b->add(35);
  b->add(55);

  b->remove(40);
  *s = *b;
  delete b;
  s->add(1111);
  delete s;
}
