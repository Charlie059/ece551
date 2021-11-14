#ifndef __STORY_HPP__
#define __STORY_HPP__
#include <vector>

#include "Page.hpp"
class Story {
 private:
  std::vector<Page> story;

 public:
  Story() : story(){};
  ~Story(){};
  bool readStory(char ** argv);
};
#endif
