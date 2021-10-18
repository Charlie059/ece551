#include "rand_story.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "string.h"

char * parseHelper(char * line, size_t len) {
  int * idx = NULL;
  while ((idx = checkStory(line, len)) != NULL) {
    line = parseStory(line, len, idx);
    free(idx);
  }
  return line;
}

/*Check if there exist a word to replace, if exist, return idx*/
int * checkStory(const char * line, size_t length) {
  const char * first_idx = strchr(line, '_');
  const char * second_idx = NULL;
  int first_idx_ = 0;
  int second_idx_ = 0;

  if (first_idx == NULL) {  // If cannot find 1st  '_', return NULL
    return NULL;
  }
  else {
    if ((size_t)(first_idx - line + 1) < length) {
      second_idx = strchr(first_idx + 1, '_');
    }
    if (second_idx == NULL) {  // If have 1st and not 2nd, return error
      printError("Expected word, but find non-paired '_'.");
    }

    // If have the line have word, return '_' idx of 1st and 2nd occurances
    first_idx_ = first_idx - line;
    second_idx_ = second_idx - line;
    int * ans = malloc(2 * sizeof(*ans));
    ans[0] = first_idx_;
    ans[1] = second_idx_;
    return ans;
  }
}

/*Parse one word in the current line*/
char * parseStory(char * line, size_t len, int * idx) {
  char * firstString = strndup(line, idx[0]);
  char * myWord = getStory(line, idx);
  const char * word = chooseWord(myWord, NULL);
  char * secondString = strndup(line + idx[1] + 1, len - idx[1] - 1);

  size_t first_str_len = strlen(firstString);
  size_t word_len = strlen(word);
  size_t second_str_len = strlen(secondString);
  size_t new_len = first_str_len + word_len + second_str_len;

  free(line);
  line = NULL;
  line = realloc(line, (new_len + 1) * sizeof(*line));

  for (size_t i = 0; i < new_len + 1; i++) {
    line[i] = '\0';
  }

  strcat(line, firstString);
  strcat(line, word);
  strcat(line, secondString);

  // free
  free(firstString);
  free(secondString);
  free(myWord);

  return line;
}
char * getStory(const char * line, int * idx) {
  int first_idx = idx[0];
  int second_idx = idx[1];
  size_t length = second_idx - first_idx;
  char * ans = malloc(length * sizeof(*ans));

  for (size_t i = 0; i < length - 1; i++) {
    ans[i] = line[first_idx + i + 1];
  }
  ans[length - 1] = '\0';
  return ans;
}

// Print some error and exit the program
void printError(const char * error) {
  fprintf(stderr, "%s\n", error);
  exit(EXIT_FAILURE);
}

// Read the words.txt
void readWords(char * line, size_t len, catarray_t * currentCatArr) {
  //Read the category and name
  char * colon = strchr(line, ':');
  assert(colon != NULL);
  size_t nameLen = colon - line;
  assert(nameLen < len);
  char * name = strndup(line, nameLen);

  char * nextLinePtr = strchr(colon + 1, '\n');
  assert(nextLinePtr != NULL);

  size_t wordLen = nextLinePtr - colon - 1;
  char * word = strndup(colon + 1, wordLen);

  int idx = readCategory(name, currentCatArr);
  //Check if the category is exist
  if (idx != -1) {
    //if exist, add to the current category

    currentCatArr->arr[idx].words = realloc(
        currentCatArr->arr[idx].words,
        (currentCatArr->arr[idx].n_words + 1) * sizeof(*currentCatArr->arr[idx].words));
    //add
    currentCatArr->arr[idx].words[currentCatArr->arr[idx].n_words] = word;
    //update
    currentCatArr->arr[idx].n_words++;
    free(name);
  }
  else {
    //if not, create a new category and link to the catarray_t
    currentCatArr->arr =
        realloc(currentCatArr->arr, (currentCatArr->n + 1) * sizeof(*currentCatArr->arr));

    //set name
    currentCatArr->arr[currentCatArr->n].name = name;
    //set words
    currentCatArr->arr[currentCatArr->n].words =
        malloc(sizeof(*currentCatArr->arr[currentCatArr->n].words));
    currentCatArr->arr[currentCatArr->n].words[0] = word;
    //set n_words
    currentCatArr->arr[currentCatArr->n].n_words = 1;

    //update n
    currentCatArr->n++;
  }
}

// Read the category from the line and check if this category exist
// then return the idx of category
int readCategory(char * name, catarray_t * currentCatArr) {
  for (size_t i = 0; i < currentCatArr->n; i++) {
    char * currentName = currentCatArr->arr[i].name;
    if (strcmp(currentName, name) == 0) {
      return i;  // return idx if find
    }
  }
  return -1;  //return -1 if not find
}

void freeCatarry(catarray_t * catArr) {
  for (size_t i = 0; i < catArr->n; i++) {
    for (size_t j = 0; j < catArr->arr[i].n_words; j++) {
      free(catArr->arr[i].words[j]);
    }
    free(catArr->arr[i].words);
    free(catArr->arr[i].name);
  }
  free(catArr->arr);

  free(catArr);
}
