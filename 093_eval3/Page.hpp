//Please refer to the .CPP file for function descriptions
#ifndef __PAGE_HPP__
#define __PAGE_HPP__
#include <iostream>
#include <limits>
#include <stack>
#include <string>

#include "NavSection.hpp"

// Declear the int to Str and Str to int functions
std::string intToStr(int toStr);
int strToInt(std::string toInt);

class Page {
 private:
  NavSection navSec;
  std::string text;
  // Used to calculate the depth in STEP 2
  int depth;
  // Def the Prev used by BFS and DFS
  Page * prev;
  int prevIdx;
  std::stack<int>
      neigbor;  // Def the neigbor stack, when we use DFS, we may pop one of neigbor when we finish that path

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
  int getPrevIdx() const;
  int popNeigbor();
  void pushNeigbor(int toPush);
  bool emptyNeigbor();
  std::stack<int> getNeigbor() const;
};

#endif
