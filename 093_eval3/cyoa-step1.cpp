/*******************************
 * File Name: cyoa-step1.cpp
 * Author: Xuhui Gong
 * Date: 2021/11/11
 *
 * This file takes the name
 * of one single page as an
 * input, check the errors,
 * if not error, print the
 * page out in the format.
 * If error occurs, print 
 * the error and exit.
 *******************************/
#include <cstdlib>

#include "InvaildInput.hpp"
#include "NavSection.hpp"
#include "Page.hpp"

int main(int argc, char ** argv) {
  bool EXITFLAG = EXIT_SUCCESS;
  // Exit if not only one file
  if (argc != 2) {
    std::cerr << "Expected only one input file." << std::endl;
    exit(EXIT_FAILURE);
  }

  try {
    Page page;
    if (page.readPage(argv) == false) {
      throw InvaildInput("Cannot read file.\n");
    }
    page.printPage();
  }
  catch (InvaildInput & e) {
    std::cerr << e.what();
    EXITFLAG = EXIT_FAILURE;
  }
  return EXITFLAG;
}
