#ifndef __STORY_HPP__
#define __STORY_HPP__
#include <vector>

#include "Page.hpp"
class Story {
 private:
  std::vector<Page> stories;

 public:
  Story() : stories(){};
  ~Story(){};
  bool readStory(char ** argv);
  void checkStory();
  void vaildRefChoice();
  void vaildRefByPage();
  void vaildWinLose();
  void play();
  void getDepth();
  void printDepth();
  void findWinPath();
  std::vector<int> findWinPagesNum();
  void DFSHelper(int src,
                 int dest,
                 std::vector<int> & stack,
                 std::vector<std::vector<int> > & ans,
                 bool diagnosis);
};
#endif
