
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
  class Node {
   public:
    Node *left, *right;
    T key;
    Node(T k) : left(NULL), right(NULL), key(k) {}
    ~Node() {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}

  void add(const T & key) {
    if (root == NULL) {
      root = new Node(key);
      return;
    }
    Node ** current = &root;
    while (*current) {
      if ((*current)->key == key) {
        return;
      }
      else if ((*current)->key > key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    *current = new Node(key);
    return;
  }

  bool contains(const T & key) const {
    const Node * current = root;
    while (current) {
      if (current->key == key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
  }

  void remove(const T & key) {
    Node ** current = &root;
    Node * temp;
    while (*current) {
      if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else if (key > (*current)->key) {
        current = &(*current)->right;
      }
      else {
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
          return;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
          return;
        }
        else {
          Node ** substitute = current;
          //go right
          substitute = &(*substitute)->right;
          //keep going left
          while ((*substitute)->left) {
            substitute = &(*substitute)->left;
          }
          temp = (*substitute)->right;
          (*current)->key = (*substitute)->key;
          delete *substitute;
          *substitute = temp;
          return;
        }
      }
    }
  }

  void destroy(Node * node) {
    if (node->left) {
      destroy(node->left);
      delete node->left;
    }
    if (node->right) {
      destroy(node->right);
      delete node->right;
    }
  }

  Node * copy(Node * node) {
    if (node == NULL) {
      return NULL;
    }
    Node * ret = new Node(node->key);
    ret->left = copy(node->left);
    ret->right = copy(node->right);
    return ret;
  }

  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destroy(root);
      delete root;
      root = copy(rhs.root);
    }
    return *this;
  }

  ~BstSet() {
    //std::cout << "In destructor" << std::endl;
    if (root) {
      //std::cout << (root == NULL) << std::endl;
      destroy(root);

      delete root;
      root = NULL;
    }
    //std::cout << "finished destructing " << std::endl;
  }

  void inorder(Node * node) {
    if (node->left) {
      inorder(node->left);
    }
    std::cout << node->key << std::endl;
    if (node->right) {
      inorder(node->right);
    }
    return;
  }

  void inorder_bst() {
    if (root) {
      inorder(root);
    }
    else {
      std::cout << "empty set " << std::endl;
    }
  }
};
