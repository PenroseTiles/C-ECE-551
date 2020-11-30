#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 public:
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream ret;
    ret << number;
    return ret.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 public:
  std::string rep;
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * l, Expression * r) : rep(" + "), lhs(l), rhs(r) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << lhs->toString() << rep << rhs->toString() << ")";
    return ss.str();
  }
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
