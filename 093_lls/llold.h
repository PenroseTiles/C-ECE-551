#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList {
  class Node {
   public:
    Node * prev;
    Node * next;
    T data;
    Node() : prev(NULL), next(NULL) {}
    Node(T value) : prev(NULL), next(NULL), data(value) {}
    Node(Node * p, Node * n, T value) : prev(NULL), next(NULL), data(value) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  class IndexOutOfBoundsException : std::exception {
    const char * what() { return "Index is out of bounds\n"; }
  };

  int getSize() const { return size; }

  void addFront(const T & item) {
    Node * node = new Node(NULL, head, item);
    if (head) {
      head->prev = node;
    }
    head = node;
    if (!tail) {
      tail = head;
    }
    ++size;
  }

  void addBack(const T & item) {
    Node * node = new Node(tail, NULL, item);
    if (tail) {
      tail->next = node;
    }
    tail = node;
    if (!head) {
      head = node;
    }
    ++size;
  }

  bool remove(const T & item) {
    Node * p = head;
    while (p) {
      if (p->data == item) {
        if (p->next) {
          p->next->prev = p->prev;
        }
        if (p->prev) {
          p->prev->next = p->next;
        }
        --size;
        delete p;
        return true;
      }
    }
    return false;
  }

  T & operator[](int index) {
    Node * p;
    for (p = head; p != NULL && index > 0; p = p->next) {
      --index;
    }
    if (p == NULL) {
      throw IndexOutOfBoundsException();
    }
    return p->data;
  }

  const T & operator[](int index) const {
    Node * p;
    for (p = head; p != NULL && index > 0; p = p->next) {
      --index;
    }
    if (p == NULL) {
      throw IndexOutOfBoundsException();
    }
    return p->data;
  }

  int find(const T & item) {
    Node * p = head;
    int i = 0;
    while (p) {
      if (p->data == item) {
        return i;
      }
      p = p->next;
      ++i;
    }
    return -1;
  }

  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) {
    if (!rhs.head) {
      head = NULL;
      tail = NULL;
      size = 0;
      return;
    }
    head = new Node(NULL, NULL, rhs.head->data);

    Node * curr = head;
    Node * p = rhs.head->next;
    while (p) {
      curr->next = new Node(curr, NULL, p->data);
      curr = curr->next;
      p = p->next;
    }
    tail = curr;
  }

  LinkedList & operator=(const LinkedList & rhs) {
    Node * curr = head;
    while (curr) {
      if (curr->prev) {
        delete curr->prev;
      }
      if (curr->next) {
        curr = curr->next;
      }
      else {
        delete curr;
      }
    }

    size = rhs.size;
    if (!rhs.head) {
      head = NULL;
      tail = NULL;
      return *this;
    }

    head = new Node(NULL, NULL, rhs.head->data);

    curr = head;
    Node * p = rhs.head->next;
    while (p) {
      curr->next = new Node(curr, NULL, p->data);
      curr = curr->next;
      p = p->next;
    }
    tail = curr;
    return *this;
  }

  ~LinkedList() {
    Node * curr = head;
    while (curr) {
      if (curr->prev) {
        delete curr->prev;
      }
      if (curr->next) {
        curr = curr->next;
      }
      else {
        delete curr;
      }
    }
  }
};

#endif
