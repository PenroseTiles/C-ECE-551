#include "utils.h"

void showpage(std::ifstream & is) {
  Page p(is);
  is.close();
  std::stringstream ss;
  p.toString(ss);

  std::cout << ss.str() << std::flush;
  p.getchoices().clear();
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "invalid usage" << std::endl;
    exit(EXIT_FAILURE);
  }
  // std::string s("1:this is a very lovely day\n");
  // std::pair<std::string, long> ret = parse_navigation(s);
  // std::cout << ret << std::endl;
  std::ifstream is(argv[1], std::ifstream::in);
  if (!is.good()) {
    std::cerr << " invalid page name" << std::endl;
    exit(EXIT_FAILURE);
  }
  showpage(is);
  //check if page number is a positive integer, check if file exists
  exit(EXIT_SUCCESS);
}
