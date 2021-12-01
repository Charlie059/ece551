#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <iostream>
#include <limits>
#include <stack>
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
  int prevIdx;
  std::stack<int> neigbor;

 public:
  Page() :
      navSec(),
      text(""),
      depth(std::numeric_limits<int>::max()),
      prev(NULL),
      prevIdx(-1),
      neigbor(){};
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
  void setPrevIdx(int idx);
  int getPrevIdx();
  int popNeigbor();
  void pushNeigbor(int toPush);
  bool emptyNeigbor();
  std::stack<int> getNeigbor();
};

#endif
