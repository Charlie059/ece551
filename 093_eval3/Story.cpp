#include "Story.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "InvaildInput.hpp"

// Generate the file name
// For example: page1.txt
std::string genFileName(char ** argv, int num) {
  std::stringstream ss;
  if (num <= 0)
    throw InvaildInput("File name must larger than 0\n");
  ss << argv[1] << "/"
     << "page" << num << ".txt";
  return ss.str();
}

// Check if file exist
bool isExist(std::ifstream & file, std::string fileName) {
  file.open(fileName.c_str());
  if (file.is_open() == false) {
    return false;
  }
  else
    return true;
}

bool Story::readStory(char ** argv) {
  std::ifstream file;

  std::vector<Page> storiesTemp;
  // Open the page1
  Page page1;
  page1.readPage(genFileName(argv, 1).c_str());
  // file.open(genFileName(argv, 1).c_str());
  std::cout << genFileName(argv, 1) << std::endl;
  if (isExist(file, genFileName(argv, 1)) == false)
    throw InvaildInput("Cannot find page0.\n");

  storiesTemp.push_back(page1);  // push the page1 to the vec
  // Open other pages
  int i = 2;
  while (isExist(file, genFileName(argv, i)) == true) {
    //  file.close();  //close the current file
    // if file no exist then break
    // if (isExist(file, genFileName(argv, i)) == false) {
    //   break;
    // }
    Page otherPage;
    otherPage.readPage(genFileName(argv, i).c_str());
    storiesTemp.push_back(otherPage);
    // file.open(genFileName(argv, i).c_str());
    std::cout << genFileName(argv, i) << std::endl;
    i++;
  }

  return true;
}
