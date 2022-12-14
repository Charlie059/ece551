/*******************************
 * File Name: cyoa-step3.cpp
 * Author: Xuhui Gong
 * Date: 2021/11/20
 *******************************/
#include <cstdlib>

#include "InvaildInput.hpp"
#include "NavSection.hpp"
#include "Page.hpp"
#include "Story.hpp"

int main(int argc, char ** argv) {
  bool EXITFLAG = EXIT_SUCCESS;
  // Exit if not only one file
  if (argc != 2) {
    std::cerr << "Expected only one input file." << std::endl;
    exit(EXIT_FAILURE);
  }

  try {
    Story story;
    if (story.readStory(argv) == false) {
      throw InvaildInput("Cannot read file.\n");
    }
    // Vaildate the stroy
    story.checkStory();
    story.getDepth();
    story.printDepth();
  }
  catch (InvaildInput & e) {
    std::cerr << e.what();
    EXITFLAG = EXIT_FAILURE;
  }
  return EXITFLAG;
}
