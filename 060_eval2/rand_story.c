#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"
#include "provided.h"

found_array_t * create_foundarray() {
  found_array_t * foundarr = (found_array_t *)malloc(sizeof(*foundarr));
  foundarr->size = 0;
  foundarr->farray = NULL;
  return foundarr;
}

void free_found_t(found_t * found) {
  free(found->cat_name);
  return;
}

void free_foundarray(found_array_t * foundarr) {
  for (size_t i = 0; i < foundarr->size; i++) {
    free_found_t(&foundarr->farray[i]);
  }
  free(foundarr->farray);
  free(foundarr);
}

void add_found(found_array_t * foundarr, char * lindex, char * rindex) {
  foundarr->farray = (found_t *)realloc(foundarr->farray,
                                        (foundarr->size + 1) * sizeof(*foundarr->farray));

  found_t * found = &foundarr->farray[foundarr->size];
  found->lindex = lindex;
  found->rindex = rindex;
  found->cat_name = malloc(rindex - lindex);
  strncpy(found->cat_name, lindex + 1, rindex - lindex - 1);
  found->cat_name[rindex - lindex - 1] = '\0';
  foundarr->size++;
  return;
}

found_array_t * parse_line(char * line) {
  /*
    finds all occurences of _category_ in a line
   */
  found_array_t * foundarr = create_foundarray();
  char * temp = line;
  int line_length = strlen(line);
  char *lindex, *rindex;
  while (temp < line + line_length) {
    lindex = strchr(temp, '_');
    if (lindex == NULL) {
      break;
    }
    rindex = strchr(lindex + 1, '_');
    if (rindex == NULL) {
      fprintf(stderr, "unmatched underscore at %s\n", lindex);
      exit(EXIT_FAILURE);
    }
    add_found(foundarr, lindex, rindex);
    temp = rindex + 1;
  }
  return foundarr;
}

void print_cat2(char * line) {
  //for step1
  found_array_t * foundarr = parse_line(line);
  size_t line_length = strlen(line);

  //this length will always be enough, even if all category names are empty strings
  char buffer[line_length + foundarr->size + 1];
  size_t i = 0;
  size_t dist = 0;
  char * curr = line;
  size_t cum_dist = 0;
  const char * catstr = "cat";
  while ((i < foundarr->size) && (curr < line + line_length)) {
    dist = foundarr->farray[i].lindex - curr;

    strncpy(buffer + cum_dist, curr, dist);
    cum_dist += dist;
    strncpy(buffer + cum_dist, catstr, 3);

    cum_dist += 3;
    curr = foundarr->farray[i].rindex + 1;
    i++;
  }
  strncpy(buffer + cum_dist, curr, 1 + line_length - (curr - line));
  printf("%s", buffer);

  free_foundarray(foundarr);
}

void failWithMessage(const char * msg) {
  fprintf(stderr, "%s", msg);
  exit(EXIT_FAILURE);
}

pair_t * readLine(FILE * f) {
  //read one line of the form category:word for step2
  pair_t * pair = malloc(sizeof(*pair));
  char * line = NULL;
  size_t size = 0;
  char * colonptr = NULL;
  char * newlineptr = NULL;
  size_t keylength = 0;
  size_t valuelength = 0;
  if (f == NULL) {
    failWithMessage("couldn't open file");
  }

  if (getline(&line, &size, f) >= 0) {
    colonptr = strchr(line, ':');
    if (colonptr == NULL) {
      failWithMessage("no colon in the line\n");
    }
    newlineptr = strchr(line, '\n');
    if (newlineptr == NULL) {
      newlineptr = line + strlen(line);
    }

    keylength = (colonptr - line) / sizeof(char);
    valuelength = (newlineptr - colonptr) / sizeof(char);

    pair->key = malloc((keylength + 1) * sizeof(char));
    strncpy(pair->key, line, keylength);

    pair->value = malloc((valuelength) * sizeof(char));
    strncpy(pair->value, colonptr + 1, valuelength);

    pair->key[keylength] = '\0';
    pair->value[valuelength - 1] = '\0';
    free(line);
    return pair;
  }
  else {
    free(line);
    free(pair);
    return NULL;
  }
}

pairarray_t * readpairs(const char * fname) {
  //read category:word pairs for step2
  FILE * f = fopen(fname, "r");
  pairarray_t * dict = malloc(sizeof(*dict));
  dict->length = 0;
  dict->pairs = malloc(sizeof(*dict->pairs));
  pair_t * pair = NULL;

  while ((pair = readLine(f)) != NULL) {
    dict->pairs = realloc(dict->pairs, (dict->length + 1) * sizeof(*dict->pairs));
    dict->pairs[dict->length] = *pair;
    dict->length++;
    free(pair);
  }
  if (fclose(f) != 0) {
    failWithMessage("could not close file\n");
  }
  return dict;
}

void freepairs(pairarray_t * pairs) {
  //free category:word pairs read in step2
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }

  free(pairs->pairs);
  free(pairs);
}
category_t * create_category_t(char * key, category_t * cat) {
  if (cat == NULL) {
    failWithMessage("empty cat in create_keytovals");
  }
  cat->n_words = 0;
  cat->name = malloc(strlen(key) + 1);
  strncpy(cat->name, key, strlen(key) + 1);
  cat->words = malloc(sizeof(*cat->words));
  return cat;
}

void free_category_t(category_t * cat) {
  //stack is a category which does not reside in catarray and must be freed separately
  for (size_t i = 0; i < cat->n_words; i++) {
    free(cat->words[i]);
  }
  free(cat->words);
  free(cat->name);
}

catarray_t * create_catarray() {
  //free every category and then free catarray itself
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->arr = NULL;
  catarray->n = 0;
  return catarray;
}

void free_catarray(catarray_t * catarray) {
  for (size_t i = 0; i < catarray->n; i++) {
    free_category_t(&catarray->arr[i]);
  }
  free(catarray->arr);
  free(catarray);
  return;
}

char * has_value(category_t * cat, char * value) {
  if (cat == NULL) {
    failWithMessage("empty k2vs in has_value");
  }
  for (size_t i = 0; i < cat->n_words; i++) {
    if (strcmp(cat->words[i], value) == 0) {
      return cat->words[i];
    }
  }
  return NULL;
}

void check_and_add_value(category_t * cat, char * value) {
  if (cat == NULL || value == NULL) {
    failWithMessage("empty k2vs in check and add value");
  }
  if (has_value(cat, value) != NULL) {
    return;
  }
  cat->words = realloc(cat->words, (1 + cat->n_words) * sizeof(*cat->words));
  cat->words[cat->n_words] = malloc(strlen(value) + 1);
  strncpy(cat->words[cat->n_words], value, strlen(value) + 1);
  cat->n_words++;
  return;
}

category_t * get_key(char * key, catarray_t * catarray) {
  //get category with name key in catarray
  if (catarray == NULL) {
    failWithMessage("empty catarray in get_key");
  }
  for (size_t i = 0; i < catarray->n; i++) {
    if (strcmp(catarray->arr[i].name, key) == 0) {
      return &catarray->arr[i];
    }
  }
  return NULL;
}

category_t * add_key(catarray_t * catarray, char * key) {
  //add category with name key to catarray and return pointer
  if (catarray == NULL) {
    fprintf(stderr, "catarray is null in add_key_value");
    exit(EXIT_FAILURE);
  }
  catarray->arr = realloc(catarray->arr, sizeof(*catarray->arr) * (1 + catarray->n));

  create_category_t(key, &catarray->arr[catarray->n]);
  catarray->n++;
  return &catarray->arr[catarray->n - 1];
}

catarray_t * invertMapping(pairarray_t * pairarray) {
  //from category->word mapping, get List[category->List[word]]
  //caller must free catarray
  if (pairarray == NULL) {
    failWithMessage("empty kvarray in invertMapping");
  }
  catarray_t * catarray = create_catarray();
  category_t * cat = NULL;
  for (size_t i = 0; i < pairarray->length; i++) {
    cat = get_key(pairarray->pairs[i].key, catarray);
    if (cat == NULL) {
      cat = add_key(catarray, pairarray->pairs[i].key);
    }

    check_and_add_value(cat, pairarray->pairs[i].value);
  }
  return catarray;
}

void print_catarray(catarray_t * catarray) {
  //print catarray for story-step2
  if (catarray == NULL) {
    failWithMessage("empty pairarray in print_pairarray");
  }
  for (size_t i = 0; i < catarray->n; i++) {
    printf("%s:\n", catarray->arr[i].name);
    for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
      printf("\t%s\n", catarray->arr[i].words[j]);
    }
  }
}

category_t * create_stack() {
  category_t * stack = malloc(sizeof(*stack));
  stack->name = NULL;
  stack->words = NULL;
  stack->n_words = 0;
  return stack;
}

void push(category_t * stack, const char * word) {
  //push onto stack
  stack->words = realloc(stack->words, (1 + stack->n_words) * sizeof(*stack->words));
  stack->words[stack->n_words] = malloc(strlen(word) + 1);
  strncpy(stack->words[stack->n_words], word, strlen(word) + 1);
  stack->n_words++;
}

char * getputindex(category_t * stack, size_t index) {
  //peek inside the stack and push the same element again
  if (index < 1) {
    failWithMessage("integer category must be at least 1\n");
  }
  if (index > stack->n_words) {
    failWithMessage("index is higher than the number of categories seen so far\n");
  }
  size_t ret_index = stack->n_words - index;
  char * ret = stack->words[ret_index];
  push(stack, ret);
  return ret;
}

char * getindex(category_t * stack, size_t index) {
  //peek inside stack
  if (index < 1) {
    failWithMessage("integer category must be at least 1\n");
  }
  if (index > stack->n_words) {
    failWithMessage("index is higher than the number of categories seen so far\n");
  }
  size_t ret_index = stack->n_words - index;
  char * ret = stack->words[ret_index];
  return ret;
}

int check_string_type(char * cat_name, int (*f)(int)) {
  //check if all chars in string are a particular type
  size_t length = strlen(cat_name);
  for (size_t i = 0; i < length; i++) {
    if (!f(cat_name[i])) {
      return 0;
    }
  }
  return 1;
}

void cascade(category_t * cat, size_t index) {
  /*replace word at index with word at index+1 and
    so on, till the end of the array cat->words*/
  size_t length = 0;
  for (size_t i = index; i < cat->n_words - 1; i++) {
    free(cat->words[i]);
    length = strlen(cat->words[i + 1]) + 1;
    cat->words[i] = malloc(length);
    strncpy(cat->words[i], cat->words[i + 1], length);
  }
  free(cat->words[cat->n_words - 1]);
  return;
}

void delete_word(catarray_t * catarray, char * cat_name, const char * word) {
  /*
   in case of -n flag, remove words from catarray after usage here 
   */
  category_t * cat = NULL;
  for (size_t i = 0; i < catarray->n; i++) {
    if (strcmp(cat_name, catarray->arr[i].name) == 0) {
      cat = &catarray->arr[i];
      break;
    }
  }
  if (cat == NULL) {
    failWithMessage("This should not happen\n");
  }
  for (size_t i = 0; i < cat->n_words; i++) {
    if (strcmp(cat->words[i], word) == 0) {
      cascade(cat, i);
      break;
    }
  }
  cat->n_words--;
}

void print_category(category_t * cat) {
  //print category for story-step2
  printf("stack name is : %s\n", cat->name);
  for (size_t i = 0; i < cat->n_words; i++) {
    printf("\t%s\n", cat->words[i]);
  }
}

size_t get_maxlen(catarray_t * catarray) {
  size_t longest = 0;
  size_t curr_length = 0;
  for (size_t i = 0; i < catarray->n; i++) {
    for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
      curr_length = strlen(catarray->arr[i].words[j]);
      longest = longest > curr_length ? longest : curr_length;
    }
  }
  return longest;
}

void substitute_file(FILE * f, catarray_t * catarray, int delete) {
  // replace _cat_ with words for entire file
  char * line = NULL;
  size_t size = 0;
  category_t * word_stack = create_stack();
  char * subbed = NULL;
  size_t longest = get_maxlen(catarray);
  while (getline(&line, &size, f) >= 0) {
    subbed = substitute_cat(line, catarray, word_stack, delete, longest);
    printf("%s", subbed);
    free(subbed);
  }
  free(line);
  free_category_t(word_stack);
  free(word_stack);
}

char * substitute_cat(char * line,
                      catarray_t * catarray,
                      category_t * word_stack,
                      int delete,
                      size_t longest) {
  /*free buffer wherever this fn returns
    
    this function replaces _blank_ with words for a given line
   */
  found_array_t * foundarr = parse_line(line);
  size_t line_length = strlen(line);
  char * buffer;

  //TODO what is optimal size for buffer??
  buffer = malloc(line_length + (foundarr->size * longest) + 1);
  size_t i = 0;
  size_t dist = 0;
  char * curr = line;
  size_t cum_dist = 0;
  const char * replacement;

  while ((i < foundarr->size) && (curr < line + line_length)) {
    dist = foundarr->farray[i].lindex - curr;
    strncpy(buffer + cum_dist, curr, dist);
    cum_dist += dist;
    //if valid integer, get the word from the stack
    if (check_string_type(foundarr->farray[i].cat_name, isdigit) &&
        atoi(foundarr->farray[i].cat_name) > 0) {
      replacement = getindex(word_stack, atoi(foundarr->farray[i].cat_name));
    }
    //else get word from chooseWord
    else {
      replacement = chooseWord(foundarr->farray[i].cat_name, catarray);
    }
    //copy the chosen word into buffer and push on stack
    push(word_stack, replacement);
    strncpy(buffer + cum_dist, replacement, strlen(replacement));
    cum_dist += strlen(replacement);

    //check if word should be deleted
    if (!(check_string_type(foundarr->farray[i].cat_name, isdigit) &&
          atoi(foundarr->farray[i].cat_name) > 0) &&
        delete > 0) {
      delete_word(catarray, foundarr->farray[i].cat_name, replacement);
    }
    curr = foundarr->farray[i].rindex + 1;
    i++;
  }
  //copy remaining string into buffer
  strncpy(buffer + cum_dist, curr, 1 + line_length - (curr - line));
  free_foundarray(foundarr);
  return buffer;
}
