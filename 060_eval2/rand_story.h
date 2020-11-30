#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"
#include "provided.h"

//any functions you want your main to use
typedef struct found_t {
  char * lindex;
  char * rindex;
  char * cat_name;
} found_t;

typedef struct found_array_t {
  found_t * farray;
  size_t size;
} found_array_t;

void free_found_t(found_t * found);
found_array_t * create_foundarray();
void free_foundarray(found_array_t * foundarr);
found_array_t * parse_line(char * line);
void add_found(found_array_t * foundarr, char * lindex, char * rindex);
void print_cat2(char * line);
category_t * create_stack();
catarray_t * invertMapping(pairarray_t * pairs);
void free_catarray(catarray_t * catarray);
void print_catarray(catarray_t * catarray);
char * substitute_cat(char * line,
                      catarray_t * catarray,
                      category_t * word_stack,
                      int delete,
                      size_t longest);
void substitute_file(FILE * f, catarray_t * catarray, int delete);

#endif
