#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

void initTracker(category_t * tracker);

// Print some error and exit the program
void printError(const char * error);
void readWordFile(FILE * f, catarray_t * catArr);
void readStoryFile(FILE * f, catarray_t * catArr, category_t * tracker, int mode);
char * parseHelper(char * line,
                   size_t len,
                   catarray_t * catArr,
                   category_t * tracker,
                   int mode);
int * checkStory(const char * line, size_t length);
char * parseStory(char * line,
                  size_t len,
                  int * idx,
                  catarray_t * catArr,
                  category_t * tracker,
                  int mode);
char * getStory(const char * line, int * idx);
// change name to the story TODO

void readWords(char * line, size_t len, catarray_t * currentCatArr);
int readCategory(char * name, catarray_t * currentCatArr);
void freeCatarry(catarray_t * catArr, size_t * n_wordsArr);
void freeTrackerArr(category_t * tracker);

void rmCatArr(char * myWord, const char * word, catarray_t * currentCatArr);
#endif
