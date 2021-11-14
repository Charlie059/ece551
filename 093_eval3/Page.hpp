#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <iostream>
#include <string>

#include "NavSection.hpp"

std::string intToStr(int toStr);
int strToInt(std::string toInt);

class Page {
 private:
  NavSection navSec;
  std::string text;

 public:
  Page() : navSec(), text(""){};
  ~Page(){};
  bool readPage(std::string);
  void readNavSec(int, std::vector<std::string>, size_t);
  void readTextSec(const std::vector<std::string> & str_buffer, size_t sharpIdx);
  void printPage();
  NavSection getNavSec() const;
};

#endif