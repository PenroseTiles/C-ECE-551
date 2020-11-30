#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  std::ifstream reader;
  reader.open(inFile);
  if (reader.fail()) {
    std::cerr << "Can not open file" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::map<unsigned, BitString>::const_iterator it;
  int c = 0;
  while ((c = reader.get()) != EOF) {
    it = theMap.find(c);
    if (it == theMap.end()) {
      std::cerr << "cannot find the correct character" << std::endl;
      exit(EXIT_FAILURE);
    }
    bfw.writeBitString(it->second);
  }

  it = theMap.find(256);
  bfw.writeBitString(it->second);

  reader.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * arr = readFrequencies(argv[1]);
  Node * mytree = buildTree(arr);
  delete[] arr;
  std::map<unsigned, BitString> mymap;
  BitString b;
  mytree->buildMap(b, mymap);
  writeCompressedOutput(argv[1], argv[2], mymap);
  delete mytree;

  return EXIT_SUCCESS;
}
