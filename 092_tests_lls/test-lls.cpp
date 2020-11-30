#include <cassert>
#include <iostream>

#include "il.h"

void fail(bool x) {
  if (!x) {
    std::cerr << "failed" << std::endl;
    exit(EXIT_FAILURE);
  }
}

void testList(const IntList & l) {
  fail(l.tail != NULL);
  fail(l.tail->next == NULL);
}

void testList2(const IntList & l) {
  fail(l.tail == NULL);
}

void testList3(const IntList & l) {
  fail(l.tail->data != 66);
  fail(l.head->data == 1);
}

void test(const IntList & l) {
  IntList::Node * curr = l.head;
  fail(curr->data == 2);
  fail(curr->prev == NULL);
  curr = curr->next;
  fail(curr->prev->next == curr);
  fail(curr->next->prev == curr);
  fail(curr->data == 11);
  curr = curr->next;
  fail(curr->data == 55);
  fail(curr->next == NULL);
  fail(curr == l.tail);
  return;
}

void testheadtail(const IntList & l) {
  fail(l.head == NULL);
  fail(l.tail == NULL);
}

int main() {
  IntList l;
  testList2(l);
  l.addFront(10);
  l.addFront(2);
  l.addBack(11);
  // l is [2, 10, 11]
  fail(l.getSize() == 3);
  fail(l[2] == 11);
  //removing from the middle
  l.remove(10);
  // l is [2, 11]
  fail(l.getSize() == 2);
  fail(l[1] == 11);
  //remving something not in list
  fail(!l.remove(5));
  fail(l.find(2) == 0);
  //TODO check that 10 is not in the list anymore
  fail(l.find(10) < 0);
  IntList l2(l);
  IntList l3;
  l3 = l;
  //repeat tests for copied and assigned list
  fail(l3.getSize() == 2);
  fail(l3[1] == 11);
  fail(!l3.remove(5));
  fail(l3.find(2) == 0);
  fail(l2.getSize() == 2);
  fail(l2[1] == 11);
  fail(!l2.remove(5));
  fail(l2.find(2) == 0);

  l.addBack(55);
  l.addBack(66);
  l3 = l;
  fail(l3.getSize() == 4);
  fail(l3[1] == 11);
  fail(!l3.remove(5));
  fail(l3.find(2) == 0);
  testList(l);
  testList(l2);
  testList(l3);
  std::cout << l.getSize() << std::endl;
  //delete from end of list
  fail(l.remove(66));
  std::cout << l.getSize() << std::endl;
  fail(l.find(66) < 0);
  //try to remove somthing twice
  fail(!l.remove(66));
  std::cout << l.getSize() << std::endl;
  l.addFront(1);
  testList3(l);
  IntList l5;
  //delete from empty list
  fail(!l5.remove(1));
  l5.addBack(2);
  l5.addBack(4);
  l5.addBack(11);
  l5.addBack(44);
  l5.addBack(55);
  l5.addBack(66);
  l5.remove(4);
  l5.remove(44);
  l5.remove(66);
  test(l5);
  l5.remove(2);
  l5.remove(11);
  l5.remove(55);
  testheadtail(l5);
}
