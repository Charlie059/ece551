#include "Story.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include "InvaildInput.hpp"
#include "Page.hpp"

// Generate the file name
// For example: page1.txt
std::string genFileName(std::string name, int num) {
  std::stringstream ss;
  if (num <= 0)
    throw InvaildInput("File name must larger than 0\n");
  ss << name << "/"
     << "page" << num << ".txt";
  return ss.str();
}

// Every page that is referenced by a choice is valid
void Story::vaildRefChoice() {
  int maxStoryNum = this->stories.size() + 1;

  // Check if any page's choice beyond the maxStoryNum
  for (size_t i = 0; i < stories.size(); i++) {
    std::vector<std::pair<int, std::string> > choices =
        stories[i].getNavSec().getChoices();
    for (size_t j = 0; j < choices.size(); j++) {
      if (choices[j].first > maxStoryNum) {
        throw InvaildInput("Every page that is referenced by a choice failure: page's "
                           "choice beyond the maxStoryNum.\n");
      }
    }
  }
}

// Every page (except page 1) is referenced by at least one *other* page's choices.
void Story::vaildRefByPage() {
  //http://www.cplusplus.com/reference/set/set/insert/
  std::set<int> pointedPages;

  // Add the pointedPages
  for (size_t i = 0; i < stories.size(); i++) {
    std::vector<std::pair<int, std::string> > choices =
        stories[i].getNavSec().getChoices();
    for (size_t j = 0; j < choices.size(); j++) {
      pointedPages.insert(choices[j].first);
    }
  }
  // insert page1
  pointedPages.insert(1);

  // Check if any page if not pointed by other except page0
  for (size_t i = 0; i < stories.size(); i++) {
    //http://www.cplusplus.com/reference/set/set/find/
    std::set<int>::iterator it;
    it = pointedPages.find(i + 1);
    // If not find
    if (it == pointedPages.end()) {
      throw InvaildInput("Every page (except page 1) is referenced by at least one "
                         "*other* page's choices check failure.\n");
    }
  }
}

// At least one page must be a WIN page and at least one page must be a LOSE page.
void Story::vaildWinLose() {
  bool findWin = false;
  bool findLose = false;

  for (size_t i = 0; i < stories.size(); i++) {
    int navStatus = stories[i].getNavSec().getNavStatus();
    if (findWin && findLose) {
      return;
    }
    if (navStatus == WIN) {
      findWin = true;
    }
    else if (navStatus == LOSE) {
      findLose = true;
    }
  }

  throw InvaildInput("At least one page must be a WIN page and at least one page must be "
                     "a LOSE page.\n");
}

// Check if file exist
bool isExist(std::string fileName) {
  std::ifstream file;
  file.open(fileName.c_str());
  if (file.is_open() == false) {
    return false;
  }
  else
    return true;
}

bool Story::readStory(char ** argv) {
  // Open the page1
  Page page1;
  page1.readPage(genFileName(argv[1], 1).c_str());
  //std::cout << genFileName(argv[1], 1) << std::endl;
  if (isExist(genFileName(argv[1], 1)) == false)
    throw InvaildInput("Cannot find page0.\n");
  stories.push_back(page1);  // push the page1 to the vec

  // Open other pages
  int i = 2;
  while (isExist(genFileName(argv[1], i))) {
    Page otherPage;
    otherPage.readPage(genFileName(argv[1], i).c_str());
    stories.push_back(otherPage);
    //std::cout << genFileName(argv[1], i) << std::endl;
    i++;
  }
  return true;
}

// Check if story is vaild
void Story::checkStory() {
  vaildRefChoice();
  vaildRefByPage();
  vaildWinLose();
}

// Get user input
int getUserInput(Page currentPage) {
  bool accept = false;
  do {
    std::string selectionStr;
    std::cin >> selectionStr;
    int selectionInt = strToInt(selectionStr);
    int choiceMaxNum = currentPage.getNavSec().getChoices().size();
    bool isInt = intToStr(selectionInt) == selectionStr;

    // If user inpt a number and between 1 to choiceMaxNum
    if (isInt && selectionInt <= choiceMaxNum && selectionInt > 0) {
      accept = true;
      return selectionInt;
    }
    else {
      std::cout << "That is not a valid choice, please try again\n";
      std::cin.clear();
    }
  } while (accept == false);
  return -1;
}

// Play the story after vaildate
void Story::play() {
  // Start from the page0
  Page currentPage = this->stories[0];
  currentPage.printPage();

  while (currentPage.getNavSec().getNavStatus() == CHOICES) {
    int userSelection = -1;
    if ((userSelection = getUserInput(currentPage)) == -1) {
      throw InvaildInput("Cannot accept INVAILD input\n");
    }

    int dirPage = currentPage.getNavSec().getChoices()[userSelection - 1].first;
    //std::cout << dirPage << std::endl;
    currentPage = this->stories[dirPage - 1];
    currentPage.printPage();
  }
}
