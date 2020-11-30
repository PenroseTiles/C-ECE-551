#ifndef __UTILS__
#define __UTILS__
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

bool is_valid_navigation(std::string & str) {
  //str better have a :
  if (str.find(':', 0) < 0) {
    return false;
  }
  return true;
}

template<typename T>
bool contains(std::set<T> & container, T x) {
  //check if set contains x
  return container.find(x) != container.end();
}

bool checkequals(long arg1, size_t arg2) {
  //returns false if input was negative or arg1!=arg2
  std::stringstream ss1;
  std::stringstream ss2;
  ss1 << arg1;
  ss2 << arg2;

  return ss1.str().compare(ss2.str()) == 0;
}

std::pair<std::string, size_t> parse_navigation(const std::string & str) {
  size_t index = str.find(':', 0);

  std::stringstream ss;
  std::stringstream ss2;

  size_t page_number;
  //get page number
  ss << str.substr(0, index).c_str();
  ss >> page_number;

  //check if page_number was was negative
  long test_page_number;
  ss2 << str.substr(0, index).c_str();
  ss2 >> test_page_number;
  char c;

  //std::cout << ss.str() << "   " << page_number << std::endl;
  //check if input was in good format
  if (ss.fail() || ss.get(c) || !checkequals(test_page_number, page_number)) {
    std::cout << "bad input " << std::endl;
    exit(EXIT_FAILURE);
  }

  //create choice object
  std::pair<std::string, size_t> ret(str.substr(index + 1, str.length() - index - 1),
                                     page_number);
  return ret;
}

void parse_text(std::istream & is, std::stringstream & ss) {
  //parse the text portion of a page
  std::string str;
  while (getline(is, str)) {
    ss << str << std::endl;
  }
  return;
}

class Page {
  //class for a Page
  bool win;   //is this a win page?
  bool lose;  //is this a lose page?
  std::vector<std::pair<std::string, size_t> >
      choices;  //vector of all possible choices, each pair contains the message and the page number we can go to
  std::string text;  //text portion of the page

 public:
  void parse_file(std::istream & is) {
    std::string str;
    std::stringstream ss1;
    std::pair<std::string, size_t> ret;
    //fetch first line of page
    getline(is, str);
    if (!is.good() || is.eof()) {
      std::cout << is.good() << " " << is.eof() << std::endl;
      std::cout << "Page ended prematurely" << std::endl;
      exit(EXIT_FAILURE);
    }
    //if winning page
    if (str.find("WIN", 0) == 0) {
      win = true;
    }
    //if losing page
    else if (str.find("LOSE", 0) == 0) {
      lose = true;
    }
    //if intermediate page
    else if (is_valid_navigation(str)) {
      ret = parse_navigation(str);
      choices.push_back(ret);
    }
    // if neither of the above
    else {
      std::cerr << "Invalid page format" << std::endl;
      exit(EXIT_FAILURE);
    }
    while (getline(is, str)) {
      //keep reading navigation instructions till a comment is found
      if (str.find("#", 0) == 0) {
        break;
      }
      ret = parse_navigation(str);
      choices.push_back(ret);
    }
    parse_text(is, ss1);
    text = ss1.str();
  }

  Page() :
      //default no-arg constructor
      win(false),
      lose(false),
      choices(std::vector<std::pair<std::string, size_t> >()),
      text("Uninitialized\n") {}

  Page(std::istream & is) : win(false), lose(false) {
    //construct Page from inputstream
    parse_file(is);
  }

  ~Page() {}

  void toString(std::stringstream & ss) const {
    //convert Page to string representation and stream into ss
    //text goes in first
    ss << text << std::endl << std::endl;
    //win or lose or choices
    if (win) {
      ss << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (lose) {
      ss << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else if (choices.size() > 0) {
      ss << "What would you like to do?" << std::endl << std::endl;
      std::vector<std::pair<std::string, size_t> >::const_iterator it = choices.begin();
      while (it != choices.end()) {
        ss << " " << it - choices.begin() + 1 << ". ";
        ss << it->first << std::endl;
        ++it;
      }
    }
    else {
      //if a page is not a win/lose/intermediate page, then error
      std::cerr << "Bad input" << std::endl;
      exit(EXIT_FAILURE);
    }
    return;
  }

  bool won() const { return win; }

  bool lost() const { return lose; }

  std::vector<std::pair<std::string, size_t> > & getchoices() { return choices; }

  const std::vector<std::pair<std::string, size_t> > & getchoices() const {
    return choices;
  }
};

std::ostream & operator<<(std::ostream & os, std::pair<std::string, size_t> pair) {
  os << " " << pair.second << ". " << pair.first;
  return os;
}

std::ostream & operator<<(std::ostream & os,
                          std::vector<std::pair<std::string, size_t> > & choices) {
  for (std::vector<std::pair<std::string, size_t> >::iterator it = choices.begin();
       it != choices.end();
       ++it) {
    os << *it << ", ";
  }
  return os;
}

class Book {
  //class for an entire story/book, contains a vector of pages
 private:
  std::vector<Page> pages;

 public:
  Book() {}

  Book(std::string & dirname) {
    //initialize a book from a given directory
    std::string prefix(dirname + "/page");
    size_t i = 0;
    //keep adding pages from page1.txt onwards
    while (true) {
      std::stringstream s;
      s << prefix << i + 1 << ".txt";
      //if file with name s.str() does not exist, throw exception
      std::ifstream is(s.str().c_str());
      if (!is.good()) {
        //if page{i+1}.txt does not exist, then we are done
        break;
      }
      //else read the file and add it to the book
      pages.push_back(Page(is));
      is.close();
      ++i;
    }
  }

  Book(std::vector<Page> p) : pages(p) {}

  size_t size() const { return pages.size(); }

  const Page & operator[](size_t i) const {
    if (i > pages.size()) {
      //check for index error
      std::cerr << " index error" << std::endl;
      exit(EXIT_FAILURE);
    }
    return pages[i];
  }

  bool validate_outgoing() const {
    //validate condition 4a of step2
    std::vector<Page>::const_iterator it;
    //for every page
    for (it = pages.begin(); it != pages.end(); ++it) {
      //for every choice in this page
      for (std::vector<std::pair<std::string, size_t> >::const_iterator branch_it =
               it->getchoices().begin();
           branch_it != it->getchoices().end();
           ++branch_it) {
        //return false if invalid page number
        if (branch_it->second > pages.size() || branch_it->second == 0) {
          return false;
        }
      }
    }

    return true;
  }

  bool validate_incoming() const {
    //validate condition 4b of step2
    //check every incoming reference is valid
    bool * incoming = new bool[pages.size()];
    for (size_t i = 0; i < pages.size(); i++) {
      incoming[i] = false;
    }
    //for every page
    for (size_t i = 0; i < pages.size(); i++) {
      const Page & p = pages[i];
      //for every incoming reference
      for (std::vector<std::pair<std::string, size_t> >::const_iterator it =
               p.getchoices().begin();
           it != p.getchoices().end();
           ++it) {
        incoming[it->second - 1] = true;
      }
    }
    incoming[0] = true;
    for (size_t i = 1; i < pages.size(); i++) {
      if (!incoming[i]) {
        delete[] incoming;

        return false;
      }
    }
    delete[] incoming;
    //std::cout << true << std::endl;
    return true;
  }

  bool validate_winlose() const {
    //validate condition 4c of step2
    std::vector<Page>::const_iterator it;
    bool win = false;
    bool lose = false;
    //at least one must be win and one must be lose
    for (it = pages.begin(); it != pages.end(); ++it) {
      win = win || it->won();
      lose = lose || it->lost();
    }
    //std::cout << "win = " << win << ", lose = " << lose << std::endl;
    return win && lose;
  }

  bool validate() const {
    //condition 4 of step2
    return validate_outgoing() && validate_incoming() && validate_winlose();
  }

  void read() const {
    //let the user interactively read the book in step2
    size_t current_page = 1;
    size_t choice = 0;
    std::string s;
    while (true) {
      //update page
      const Page & p = pages[current_page - 1];
      std::stringstream ss;
      //print current page
      p.toString(ss);
      std::cout << ss.str();
      if (p.won() || p.lost()) {
        break;
      }

      //input player's decision
      while (!(std::cin >> choice) || choice < 1 || choice > p.getchoices().size()) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }

      //update page number
      current_page = p.getchoices()[choice - 1].second;
    }
  }

  void bfs() const {
    //breadth first search to find reachable pages
    std::set<size_t> visited;  //set of visited pages
    std::queue<size_t> q;      //pages in the queue to be visited during bfs
    q.push(0);
    size_t curr;
    // the queue and set contains 0-indexed page numbers, but p.choices contains 1-indexed
    while (!q.empty()) {
      curr = q.front();
      q.pop();
      //std::cout << "In page " << curr + 1 << std::endl;
      if (!contains(visited, curr)) {
        visited.insert(curr);
      }
      else {
        continue;
      }
      const Page & p = pages[curr];
      //for every outgoing edge
      for (std::vector<std::pair<std::string, size_t> >::const_iterator it =
               p.getchoices().begin();
           it != p.getchoices().end();
           ++it) {
        size_t next = it->second - 1;
        //std::cout << next + 1 << " is after " << curr + 1 << std::endl;
        if (!contains(visited, next)) {
          q.push(next);
        }
      }
    }

    //print non-reachable nodes
    for (size_t i = 0; i < pages.size(); i++) {
      if (!contains(visited, i)) {
        std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
      }
    }
    return;
  }

  void play() {
    //solve the game for step4
    std::set<size_t> visited;       //set of visited pages
    std::stack<std::string> stack;  // this stack keeps the messages to be printed
    if (!recursive_bfs(0, visited, stack)) {
      std::cout << "There is no way to win" << std::endl;
    }
    else {
      while (!stack.empty()) {
        std::cout << stack.top();
        stack.pop();
      }
    }
  }

  bool recursive_bfs(const size_t node,
                     std::set<size_t> & visited,
                     std::stack<std::string> & stack) {
    //helper function for step4, another bfs implementation, just for completeness
    if (contains(visited, node)) {
      return false;
    }
    else {
      visited.insert(node);
    }
    if (pages[node].won()) {
      //winning reachable page found, traceback and print path
      std::stringstream ss;
      ss << "Page " << node + 1 << " WIN" << std::endl;
      stack.push(ss.str());
      return true;
    }
    size_t i = 1;
    Page & p = pages[node];
    for (std::vector<std::pair<std::string, size_t> >::const_iterator it =
             p.getchoices().begin();
         it != p.getchoices().end();
         ++it) {
      //the page number of each choice is 1-indexed, subtract 1
      if (!contains(visited, it->second - 1)) {
        if (recursive_bfs(it->second - 1, visited, stack)) {
          //this page is on the winning path, add current decision and return to parent page
          std::stringstream ss2;
          ss2 << "Page " << node + 1 << " choice " << i << std::endl;
          stack.push(ss2.str());

          return true;
        }
      }
      ++i;
    }
    //no winning strategies pass through this page
    return false;
  }
};

#endif
