#ifndef __NAV_SECTION_HPP__
#define __NAV_SECTION_HPP__

#define CHOICES 0
#define WIN 1
#define LOSE 2
#define UNKNOWN -1

#include <string>
#include <utility>
#include <vector>

class NavSection {
 private:
  int navStatus;  // Define the Navigation section status: WIN 1, LOSE 2, CHOICE 0 or UNKNOWN -1
  std::vector<std::pair<int, std::string> >
      choices;  // Define the choices by vector which included pair: int pageNum, string option (If navStatus is 0 otherwise the vector is empty)

 public:
  NavSection() : navStatus(UNKNOWN), choices(){};
  explicit NavSection(int navStatus) : navStatus(navStatus){};
  ~NavSection(){};
  //Get the navStatus
  int getNavStatus() const;
  //Get the choices
  std::vector<std::pair<int, std::string> > getChoices() const;

  //Set the navStatus
  void setStatus(int);
  //Add choice
  void addChoice(std::pair<int, std::string>);
};
#endif
