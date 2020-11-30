#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
  class Node {
   public:
    Node *left, *right;
    K key;
    V value;

    Node(K k, V v) : left(NULL), right(NULL), key(k), value(v) {}
    Node(Node & rhs) : left(rhs.left), right(rhs.right), key(rhs.key), value(rhs.value) {}
    ~Node() {}
    //friend std::ostream & operator<<(std::ostream & os, Node & node);
  };

 public:
  Node * root;

  BstMap() : root(NULL) {}

  void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current) {
      if ((*current)->key > key) {
        current = &(*current)->left;
      }
      else if ((*current)->key == key) {
        (*current)->value = value;
        return;
      }
      else {
        current = &(*current)->right;
      }
    }
    if (*current == NULL) {
      *current = new Node(key, value);
    }
  }

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * current = &root;
    while (*current) {
      if ((*current)->key == key) {
        return (*current)->value;
      }
      else if ((*current)->key > key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
    throw std::invalid_argument("key not found");
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      remove(root);
      delete root;
      root = copy(rhs.root);
    }
    return *this;
  }

  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  void remove(const K & data) {
    Node ** current = &root;
    Node * temp;
    while (*current) {
      if ((*current)->key == data) {
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        else {
          Node ** del = &(*current)->right;
          while ((*del)->left != NULL) {
            del = &(*del)->left;
          }
          temp = (*del)->right;
          (*current)->key = (*del)->key;
          (*current)->value = (*del)->value;
          delete *del;
          *del = temp;
          return;
        }
      }
      else if ((*current)->key > data) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
    return;
  }

  void remove(Node * node) {
    if (node->left) {
      //remove left child
      remove(node->left);
      delete node->left;
    }
    //remove right child
    if (node->right) {
      remove(node->right);
      delete node->right;
    }
  }

  ~BstMap() {
    if (root) {
      remove(root);
      delete root;
      root = NULL;
    }
  }

  void inorder(Node * node) const {
    if (node == NULL) {
      return;
    }
    inorder(node->left);

    std::cout << "Key: " << node->key << "\t"
              << "Value: " << node->value << std::endl;
    inorder(node->right);
    return;
  }

  void inorderBst() const {
    if (root) {
      inorder(root);
    }
    else {
      std::cout << "empty map" << std::endl;
    }
    return;
  }
};
