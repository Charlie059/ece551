#ifndef __INVAILD_INPUT_HPP__
#define __INVAILD_INPUT_HPP__
#include <exception>
// Exception Class Based on the recitation class from TA: yz566
class InvaildInput : public std::exception {
 private:
  const char * error_msg;

 public:
  InvaildInput(const char * msg) : error_msg(msg) {}
  InvaildInput() : error_msg("Invaild input.") {}
  virtual const char * what() const throw();
};
#endif
