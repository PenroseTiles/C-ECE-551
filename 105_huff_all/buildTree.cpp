#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t q;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] == 0) {
      continue;
    }
    q.push(new Node(i, counts[i]));
  }
  if (q.size() == 0) {
    return NULL;
  }

  while (q.size() > 1) {
    Node * first = q.top();
    q.pop();
    Node * second = q.top();
    q.pop();
    Node * toadd = new Node(first, second);
    q.push(toadd);
  }
  return q.top();
}
