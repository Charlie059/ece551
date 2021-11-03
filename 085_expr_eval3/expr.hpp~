#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long setNum) : num(setNum){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << this->num;
    return ss.str();
  }

  virtual ~NumExpression(){};
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << this->lhs->toString() << " + " << this->rhs->toString() << ")";
    return ss.str();
  };
  virtual ~PlusExpression() {
    delete this->lhs;
    delete this->rhs;
  };
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << this->lhs->toString() << " - " << this->rhs->toString() << ")";
    return ss.str();
  };
  virtual ~MinusExpression() {
    delete this->lhs;
    delete this->rhs;
  };
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << this->lhs->toString() << " * " << this->rhs->toString() << ")";
    return ss.str();
  };
  virtual ~TimesExpression() {
    delete this->lhs;
    delete this->rhs;
  };
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs){};
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(" << this->lhs->toString() << " / " << this->rhs->toString() << ")";
    return ss.str();
  };
  virtual ~DivExpression() {
    delete this->lhs;
    delete this->rhs;
  };
};

#endif
