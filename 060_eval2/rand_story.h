#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>

// Print some error and exit the program
void printError(const char * error);
char * parseHelper(char * line, size_t len);
int * checkWord(const char * line, size_t length);
char * parseWord(char * line, size_t len, int * idx);
char * getWord(const char * line, int * idx);
#endif
