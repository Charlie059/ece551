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

bool Story::readStory(char ** argv) {
  std::ifstream file;

  // Open the page1
  file.open(genFileName(argv, 1).c_str());
  std::cout << genFileName(argv, 1) << std::endl;
  if (file.is_open() == false)
    throw InvaildInput("Cannot find page0.\n");

  // Open other pages
  int i = 2;
  while (file.is_open()) {
    file.close();  //close the current file
    file.open(genFileName(argv, i).c_str());
    std::cout << genFileName(argv, i) << std::endl;
    i++;
  }

  return true;
}
