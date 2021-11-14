
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
    }
    else if (str_buffer[0] == "LOSE") {
      navStatus = LOSE;
    }
  }
  else {
    for (size_t i = 0; i < sharpIdx; i++) {
      std::string temp = str_buffer[i];
      checkChoice(temp);
    }
    navStatus = CHOICES;
  }

  return navStatus;
}

bool Page::readPage(std::string fileName) {
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
      this->navSecPtr->setStatus(WIN);
      break;
    case LOSE:
      this->navSecPtr->setStatus(LOSE);
      break;
    default:
      this->navSecPtr->setStatus(CHOICES);
      for (size_t i = 0; i < sharpIdx; i++) {
        std::pair<int, std::string> choice = checkChoice(str_buffer[i]);
        this->navSecPtr->addChoice(choice);
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
  std::cout << this->text << std::endl;

  // Print the choices if NavStatus is CHOICES
  if (this->navSecPtr->getNavStatus() == CHOICES) {
    std::cout << "\nWhat would you like to do?" << std::endl;
    std::cout << "\n";

    std::vector<std::pair<int, std::string> > choices = this->navSecPtr->getChoices();
    for (size_t i = 0; i < choices.size(); i++) {
      std::cout << " " << i + 1 << ". " << choices[i].second << std::endl;
    }
  }
  else if (this->navSecPtr->getNavStatus() == WIN) {
    std::cout << "\n";
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }

  else if (this->navSecPtr->getNavStatus() == LOSE) {
    std::cout << "\n";
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
}
