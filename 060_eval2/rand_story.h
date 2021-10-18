#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

#include "provided.h"

// Print some error and exit the program
void printError(const char * error);
char * parseHelper(char * line, size_t len);
int * checkStory(const char * line, size_t length);
char * parseStory(char * line, size_t len, int * idx);
char * getStory(const char * line, int * idx);
// change name to the story TODO

void readWords(char * line, size_t len, catarray_t * currentCatArr);
int readCategory(char * name, catarray_t * currentCatArr);
void freeCatarry(catarray_t * catArr);
#endif
