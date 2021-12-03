#include "NavSection.hpp"

// Nav Status can be WIN LOSE or CHOICE
int NavSection::getNavStatus() const {
  return this->navStatus;
}
// Get the Choices of page
std::vector<std::pair<int, std::string> > NavSection::getChoices() const {
  return this->choices;
}

void NavSection::setStatus(int navStatus) {
  this->navStatus = navStatus;
}
// Add a new choice when we read the curr page
void NavSection::addChoice(std::pair<int, std::string> addChoice) {
  this->choices.push_back(addChoice);
}
