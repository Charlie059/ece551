#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <iostream>
#include <limits>
#include <string>

#include "NavSection.hpp"

std::string intToStr(int toStr);
int strToInt(std::string toInt);

class Page {
 private:
  NavSection navSec;
  std::string text;
  int depth;
  Page * prev;

 public:
  Page() : navSec(), text(""), depth(std::numeric_limits<int>::max()), prev(NULL){};
  ~Page(){};
  bool readPage(std::string);
  void readNavSec(int, std::vector<std::string>, size_t);
  void readTextSec(const std::vector<std::string> & str_buffer, size_t sharpIdx);
  void printPage();
  NavSection getNavSec() const;

  int getDepth() const;
  void setDepth(int);
  Page * getPrev() const;
  void setPrev(Page *);
};

#endif
