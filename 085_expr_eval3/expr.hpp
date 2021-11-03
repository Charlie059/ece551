#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual long evaluate() const = 0;
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

  virtual long evaluate() const { return this->num; }

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
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
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
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
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
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
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

  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};

#endif
