#include <iostream>
#include <sstream>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long val) : num(val) {}
  std::string toString() const {
    std::stringstream ss;
    ss << num;
    return ss.str();
  }
  ~NumExpression() {}
  long evaluate() const { return num; }
};

class BinaryExpression : public Expression {
 protected:
  std::string repr;
  Expression * lhs;
  Expression * rhs;
  long (*f)(long, long);

 public:
  BinaryExpression(const char * str,
                   Expression * l,
                   Expression * r,
                   long (*fun)(long, long)) :
      repr(str),
      lhs(l),
      rhs(r),
      f(fun) {}
  std::string toString() const {
    std::stringstream ss;
    ss << "(" + lhs->toString() + " " + repr + " " + rhs->toString() + ")";
    return ss.str();
  }
  virtual long evaluate() const { return f(lhs->evaluate(), rhs->evaluate()); }
  ~BinaryExpression() {
    delete lhs;
    delete rhs;
  }
};

long plus(long a, long b) {
  return a + b;
}

long minus(long a, long b) {
  return a - b;
}

long times(long a, long b) {
  return a * b;
}

long divide(long a, long b) {
  return a / b;
}

class PlusExpression : public BinaryExpression {
 public:
  PlusExpression(Expression * l, Expression * r) : BinaryExpression("+", l, r, plus) {}
  // virtual long evaluate() const{
  //   return lhs->evaluate() + rhs->evaluate();
  // }
};

class TimesExpression : public BinaryExpression {
 public:
  TimesExpression(Expression * l, Expression * r) : BinaryExpression("*", l, r, times) {}
};

class DivExpression : public BinaryExpression {
 public:
  DivExpression(Expression * l, Expression * r) : BinaryExpression("/", l, r, divide) {}
};

class MinusExpression : public BinaryExpression {
 public:
  MinusExpression(Expression * l, Expression * r) : BinaryExpression("-", l, r, minus) {}
};
