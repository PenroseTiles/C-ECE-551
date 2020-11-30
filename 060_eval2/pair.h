#ifndef __KV_H__
#define __KV_H__
#include <stdlib.h>

// pair structure for story-step1
struct _pair_t {
  char * key;
  char * value;
};
typedef struct _pair_t pair_t;

struct _pairarray_t {
  pair_t * pairs;
  size_t length;
};
typedef struct _pairarray_t pairarray_t;

pairarray_t * readpairs(const char * fname);

void freepairs(pairarray_t * pairs);

// void printpairs(pairarray_t * pairs);

// char * lookupValue(pairarray_t * pairs, const char * key);

#endif
