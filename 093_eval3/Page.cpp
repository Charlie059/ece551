
#define CHOICES 0
#define WIN 1
#define LOSE 2
#define UNKNOWN -1

#include "Page.hpp"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "InvaildInput.hpp"
#include "NavSection.hpp"
// Find the Sharp # sign's line index
size_t findSharpIdx(const std::vector<std::string> & str_buffer) {
  for (size_t i = 0; i < str_buffer.size(); i++) {
    if (str_buffer[i][0] == '#') {
      return i;
    }
  }
  throw InvaildInput("Cannot find # sign.\n");
}

// Def the String to int: Based on my eval 2
int strToInt(std::string toInt) {
  int ans = strtol(toInt.c_str(), NULL, 10);
  if (errno == ERANGE)
    throw InvaildInput("Page number out of range.\n");
  return ans;
}

// Def the int to String: Based on the AOP's stringstream and https://www.cplusplus.com/reference/ios/ios/bad/ also https://www.cplusplus.com/reference/sstream/stringstream/str/
std::string intToStr(int toStr) {
  std::stringstream ss;
  ss << toStr;
  if (ss.fail())
    throw InvaildInput("Cannot convert int to string\n");
  return ss.str();
}

// Input string and parse the choice
std::pair<int, std::string> checkChoice(const std::string choice) {
  // find and substr method besed on the https://www.cplusplus.com/reference/string/string/substr/
  std::size_t pos = choice.find(':');
  if (pos == std::string::npos)
    throw InvaildInput("Invaild choice.\n");

  //Get page number string
  std::string pageNumStr = choice.substr(0, pos);
  std::string textChoice = choice.substr(pos + 1);
  int pageNum = strToInt(pageNumStr);
  if (pageNum <= 0)
    throw InvaildInput("Invaild choice: Page Number <= 0.\n");
  if (intToStr(pageNum) != pageNumStr)
    throw InvaildInput("Invaild choice: Page Number contains non-int value.\n");
  // std::cout << textChoice << std::endl;
  return std::make_pair(pageNum, textChoice);
}

// Check if Naviagtion section is vaild, if vaild, return CHOICES 0 or WIN 1 or LOSE 2
int checkNavSec(const std::vector<std::string> & str_buffer, size_t sharpIdx) {
  int navStatus = UNKNOWN;
  if (sharpIdx == 0) {
    throw InvaildInput("Sharp # cannot in the first line");
  }
  else if (sharpIdx == 1) {  // If nav section only one line and is WIN or LOSE
    if (str_buffer[0] == "WIN") {
      navStatus = WIN;
      return navStatus;
    }
    else if (str_buffer[0] == "LOSE") {
      navStatus = LOSE;
      return navStatus;
    }
  }

  // Choice
  for (size_t i = 0; i < sharpIdx; i++) {
    std::string temp = str_buffer[i];
    checkChoice(temp);
  }
  navStatus = CHOICES;

  return navStatus;
}

// Vaild file name "page%"
void vaildFileName(std::string fileName) {
  // Find the last /: based on https://www.cplusplus.com/reference/string/string/find_last_of/
  std::size_t found = fileName.find_last_of("/");

  std::string name;
  std::string num;
  std::string extend;

  // if found not return string::npos
  if (found != std::string::npos) {
    fileName = fileName.substr(found + 1);
  }
  name = fileName.substr(0, 4);
  num = fileName.substr(4, fileName.size() - 8);
  extend = fileName.substr(fileName.size() - 4, 4);

  // Check Page
  if (name != "page") {
    throw InvaildInput("Excepted to match page.\n");
  }

  // Check num
  int numInt = strToInt(num);
  if (numInt < 1) {
    throw InvaildInput("Excepted to match page%d which %d >= 1, but %d < 1.\n");
  }

  // Check extend
  if (extend != ".txt") {
    throw InvaildInput("Excepted to match .txt File");
  }

  // Check All
  if (name + intToStr(numInt) + extend != fileName) {
    throw InvaildInput("Excepted to match page%d which %d >= 1.\n");
  }
}

// Read each page
bool Page::readPage(std::string fileName) {
  vaildFileName(fileName);
  std::ifstream file(fileName.c_str());
  size_t sharpIdx = 0;
  int navStatus = UNKNOWN;
  //File read and open based on
  //the https://www.cplusplus.com/reference/fstream/ifstream/is_open/
  if (file.is_open()) {
    std::string line;
    std::vector<std::string> str_buffer;
    while (getline(file, line)) {
      str_buffer.push_back(line);
    }

    sharpIdx = findSharpIdx(str_buffer);            //Find #
    navStatus = checkNavSec(str_buffer, sharpIdx);  //Vaildate the Nav Section
    if (navStatus == -1)
      throw InvaildInput("Navigation section cannot UNKNOWN.\n");
    readNavSec(navStatus, str_buffer, sharpIdx);
    readTextSec(str_buffer, sharpIdx);
    return true;
  }
  //ifs.close();
  return false;
}

//Read the Navigation section into Page
void Page::readNavSec(int navStatus,
                      std::vector<std::string> str_buffer,
                      size_t sharpIdx) {
  switch (navStatus) {
    case WIN:
      this->navSec.setStatus(WIN);
      break;
    case LOSE:
      this->navSec.setStatus(LOSE);
      break;
    default:
      this->navSec.setStatus(CHOICES);
      for (size_t i = 0; i < sharpIdx; i++) {
        std::pair<int, std::string> choice = checkChoice(str_buffer[i]);
        this->navSec.addChoice(choice);
      }
  }
}

void Page::readTextSec(const std::vector<std::string> & str_buffer, size_t sharpIdx) {
  std::stringstream ss;
  for (size_t i = sharpIdx + 1; i < str_buffer.size(); i++) {
    if (i != str_buffer.size() - 1) {
      ss << str_buffer[i] << std::endl;
    }
    else {
      ss << str_buffer[i];
    }
  }
  this->text = ss.str();
}

void Page::printPage() {
  // Print the text of page
  if (!this->text.empty()) {
    std::cout << this->text << std::endl;
  }

  // Print the choices if NavStatus is CHOICES
  if (this->navSec.getNavStatus() == CHOICES) {
    std::cout << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;

    std::vector<std::pair<int, std::string> > choices = this->navSec.getChoices();
    for (size_t i = 0; i < choices.size(); i++) {
      std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
    }
  }
  else if (this->navSec.getNavStatus() == WIN) {
    std::cout << std::endl;
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }

  else if (this->navSec.getNavStatus() == LOSE) {
    std::cout << std::endl;
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}

NavSection Page::getNavSec() const {
  return this->navSec;
}

int Page::getDepth() const {
  return this->depth;
}

void Page::setDepth(int depth) {
  this->depth = depth;
}

Page * Page::getPrev() const {
  return this->prev;
}

void Page::setPrev(Page * prev) {
  this->prev = prev;
}

int Page::popNeigbor() {
  if (!this->neigbor.empty()) {
    int ans = this->neigbor.top();
    this->neigbor.pop();
    return ans;
  }
  return -1;
}

void Page::pushNeigbor(int toPush) {
  this->neigbor.push(toPush);
}

bool Page::emptyNeigbor() {
  return neigbor.empty();
}

std::stack<int> Page::getNeigbor() const {
  return this->neigbor;
}

void Page::setPrevIdx(int idx) {
  this->prevIdx = idx;
}

int Page::getPrevIdx() const {
  return this->prevIdx;
}
