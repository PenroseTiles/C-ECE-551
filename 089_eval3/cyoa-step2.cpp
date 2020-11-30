#include "utils.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Usage ./cyoa-step2 directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string s(argv[1]);
  Book g(s);
  if (!g.validate()) {
    std::cout << "validation of book failed" << std::endl;
    exit(EXIT_FAILURE);
  }
  /*
  for (size_t i = 0; i < g.size(); i++) {
    std::cout << g[i].toString() << std::endl;
    }
  */
  g.read();
  //g.bfs();
}
