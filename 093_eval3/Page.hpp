#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <iostream>
#include <string>

#include "NavSection.hpp"
class Page {
 private:
  NavSection * navSecPtr;
  std::string text;

 public:
  Page() : navSecPtr(new NavSection()), text(""){};
  ~Page() { delete navSecPtr; };
  bool readPage(std::string);
  void readNavSec(int, std::vector<std::string>, size_t);
  void readTextSec(const std::vector<std::string> & str_buffer, size_t sharpIdx);
  void printPage();
};

#endif
