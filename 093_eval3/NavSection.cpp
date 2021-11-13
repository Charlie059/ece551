#include "NavSection.hpp"

int NavSection::getNavStatus() const {
  return this->navStatus;
}

std::vector<std::pair<int, std::string> > NavSection::getChoices() const {
  return this->choices;
}

void NavSection::setStatus(int navStatus) {
  this->navStatus = navStatus;
}

void NavSection::addChoice(std::pair<int, std::string> addChoice) {
  this->choices.push_back(addChoice);
}
