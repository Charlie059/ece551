// +---------------------------------------+
// |Story.cpp                              |
// |Xuhui gong                             |
// |2021/12/3                              |
// |This file includes all functions       |
// |used by the story, including check     |
// |story, check user input, BFS, DFS      |
// |and other implementations.             |
// |                                       |
// |                                       |
// |                                       |
// |                                       |
// |                                       |
// |                                       |
// +---------------------------------------+

#include "Story.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>
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
  std::vector<bool> ref(stories.size(), false);

  // Add the pointedPages
  for (size_t i = 0; i < stories.size(); i++) {
    std::vector<std::pair<int, std::string> > choices =
        stories[i].getNavSec().getChoices();
    for (size_t j = 0; j < choices.size(); j++) {
      if (choices[j].first != (int)i + 1) {
        ref[choices[j].first - 1] = true;
      }
    }
  }
  // insert page1
  ref[0] = true;

  // Check if any page if not pointed by other except page1
  for (size_t i = 0; i < stories.size(); i++) {
    if (ref[i] == false) {
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

  if (findWin && findLose == false) {
    throw InvaildInput(
        "At least one page must be a WIN page and at least one page must be "
        "a LOSE page.\n");
  }
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

// Read Stroy based on the path
bool Story::readStory(char ** argv) {
  // Open the page1
  Page page1;
  page1.readPage(genFileName(argv[1], 1).c_str());
  if (isExist(genFileName(argv[1], 1)) == false)
    throw InvaildInput("Cannot find page0.\n");
  stories.push_back(page1);  // push the page1 to the vec

  // Open other pages
  int i = 2;
  while (isExist(genFileName(argv[1], i))) {
    Page otherPage;
    otherPage.readPage(genFileName(argv[1], i).c_str());
    stories.push_back(otherPage);
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
    currentPage = this->stories[dirPage - 1];
    currentPage.printPage();
  }
}

// Get each pages depth: Apply BFS
void Story::getDepth() {
  // Def the queue
  std::queue<Page *> queue;

  // Set page1 as depth 0
  this->stories[0].setDepth(0);

  // Push page1 into the queue
  queue.push(&this->stories[0]);

  while (!queue.empty()) {
    // Pop and set to the current
    Page * currentPage = queue.front();
    queue.pop();

    // Get current page choice
    std::vector<std::pair<int, std::string> > choice =
        currentPage->getNavSec().getChoices();

    // For the current page's neigbor
    for (size_t i = 0; i < choice.size(); i++) {
      // Check if the neigbor is not visited. ie. the depth is inf
      if (this->stories[choice[i].first - 1].getDepth() ==
          std::numeric_limits<int>::max()) {
        // Set the Depth to the currentPage's depth + 1
        this->stories[choice[i].first - 1].setDepth(currentPage->getDepth() + 1);
        // Push into the queue
        queue.push(&this->stories[choice[i].first - 1]);

        // Set the prev's page to the current
        this->stories[choice[i].first - 1].setPrev(currentPage);
      }
    }
  }
}
// Function to print the depth
void Story::printDepth() {
  for (size_t i = 0; i < this->stories.size(); i++) {
    if (this->stories[i].getDepth() == std::numeric_limits<int>::max()) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << ":" << this->stories[i].getDepth() << std::endl;
    }
  }
}

void diagnosisDFS(std::vector<int> & DFS_Stack) {
  std::cout << "DFS_Stack: " << std::endl;
  for (size_t i = 0; i < DFS_Stack.size(); ++i) {
    std::cout << DFS_Stack[i] + 1 << std::endl;
  }
}

// FIND all WIN ending pages
std::vector<int> Story::findWinPagesNum() {
  std::vector<int> ans;
  for (size_t i = 0; i < this->stories.size(); ++i) {
    if (this->stories[i].getNavSec().getNavStatus() == WIN) {
      ans.push_back(i + 1);
    }
  }
  return ans;
}

// visit curr Node's neibor
void visitNeighbor(std::vector<int> & DFS_Stack, std::vector<Page> & stories) {
  // get the top of DFS_Stack
  int currentPageIdx = DFS_Stack.back();
  // Get current page choice
  std::vector<std::pair<int, std::string> > choice =
      stories[currentPageIdx].getNavSec().getChoices();

  // Track the prev to the currPath
  int currIdx = currentPageIdx;
  std::vector<int> currPath;
  while (currIdx != -1) {
    currPath.push_back(currIdx);
    currIdx = stories[currIdx].getPrevIdx();
  }

  // Check if the path not in a loop and add to the Node's neigbor
  for (size_t i = 0; i < choice.size(); i++) {
    if (std::find(currPath.begin(), currPath.end(), choice[i].first - 1) ==
        currPath.end()) {
      stories[currentPageIdx].pushNeigbor(choice[i].first - 1);
    }
  }
}

// Helper function of DFS
void Story::DFSHelper(int src,
                      int dest,
                      std::vector<int> & DFS_Stack,
                      std::vector<std::vector<int> > & ans,
                      bool diagnosis) {
  // Push the src into the DFS_Stack
  DFS_Stack.push_back(src);

  // Visit the current node's Neighbor
  visitNeighbor(DFS_Stack, stories);

  // diagnosis
  if (diagnosis == true) {
    diagnosisDFS(DFS_Stack);
  }

  // While the DFS_Stack is not empty
  while (DFS_Stack.size() != 0) {
    // Get the current top of DFS_Stack
    int curr = DFS_Stack.back();

    // If the current Node have neigbor to visit
    if (!stories[curr].emptyNeigbor()) {
      // get one neigbor dir and move to the DFS_Stack
      int to_push = stories[curr].popNeigbor();
      DFS_Stack.push_back(to_push);

      // Mark Prev
      stories[to_push].setPrevIdx(curr);

      // Visit current node's Neighbor
      visitNeighbor(DFS_Stack, stories);
    }
    else {  // Else we have go through all the path of this node
      // If we reach to the dest
      if (DFS_Stack.size() != 0 && DFS_Stack.back() == dest) {
        // Track the prev to the ans
        int currIdx = dest;
        std::vector<int> ans_temp;
        while (currIdx != -1) {
          ans_temp.push_back(currIdx + 1);
          currIdx = stories[currIdx].getPrevIdx();
        }
        // Reverse the ans
        std::reverse(ans_temp.begin(), ans_temp.end());
        ans.push_back(ans_temp);
      }
      // Pop DFS_Stack becasue we have no path to go
      DFS_Stack.pop_back();
    }

    // diagnosis
    if (diagnosis == true) {
      diagnosisDFS(DFS_Stack);
    }
  }
}

// Check page selection which helps to win the game
std::string checkSelection(int currPageNum, int nextPageNum, std::vector<Page> stories) {
  // if nextPageNum not exist, return WIN
  if (nextPageNum == -1) {
    return "win";
  }

  // Get index
  int currPageIdx = currPageNum - 1;
  // Get current page choice
  std::vector<std::pair<int, std::string> > choice =
      stories[currPageIdx].getNavSec().getChoices();

  // Find the match choice
  for (size_t i = 0; i < choice.size(); ++i) {
    if (choice[i].first == nextPageNum) {
      return intToStr(i + 1);
    }
  }
  return "ERROR: NOT FOUND";
}
// Function of print win path
void printWinPath(std::vector<std::vector<int> > ans, std::vector<Page> stories) {
  for (size_t i = 0; i < ans.size(); i++) {
    for (size_t j = 0; j < ans[i].size(); j++) {
      // Check selection
      int currPageNum = ans[i][j];
      int nextPageNum;
      if (j + 1 < ans[i].size()) {
        nextPageNum = ans[i][j + 1];
      }
      else {
        nextPageNum = -1;
      }

      std::string choicenumber = checkSelection(currPageNum, nextPageNum, stories);
      std::cout << ans[i][j] << "(" << choicenumber << ")";
      if (j != ans[i].size() - 1) {
        std::cout << ",";
      }
    }
    std::cout << "\n";
  }
}
// This function is used for the STEP 4:
// which is implmented by the stack based DFS.
// The basic idea from AoP and we add a stack
// to each Node so that we can simluate how
// the DFS going on (which path has been visited
// and which not)
void Story::findWinPath() {
  std::vector<int> DFSStack;
  std::vector<int> winPageNum;
  std::vector<std::vector<int> > ans;

  // find WIN ending pages
  winPageNum = findWinPagesNum();
  // for each WIN page
  for (size_t i = 0; i < winPageNum.size(); ++i) {
    DFSHelper(0, winPageNum[i] - 1, DFSStack, ans, false);
  }

  // If unwinnable
  if (ans.size() == 0) {
    std::cout << "This story is unwinnable!" << std::endl;
    return;
  }
  // Print ans
  printWinPath(ans, stories);
}
