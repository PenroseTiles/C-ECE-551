#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  char * key = NULL;
  size_t sz = 0;
  size_t keylen = 0;
  counts_t * c = createCounts();
  char * value = NULL;
  while (getline(&key, &sz, f) >= 0) {
    keylen = strlen(key);
    key[keylen - 1] = '\0';
    value = lookupValue(kvPairs, key);
    addCount(c, value);
    sz = 0;
    free(key);
  }
  free(key);

  fclose(f);
  //should we free key?
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "proper usage is ./a.out kvfile keyfiles...");
    exit(EXIT_FAILURE);
  }
  char * kv = argv[1];
  kvarray_t * kvarray = readKVs(kv);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kvarray);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kvarray);
  return EXIT_SUCCESS;
}
