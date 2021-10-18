#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "string.h"

char * parseHelper(char * line, size_t len) {
  int * idx = NULL;
  while ((idx = checkWord(line, len)) != NULL) {
    line = parseWord(line, len, idx);
    free(idx);
  }
  return line;
}

/*Check if there exist a word to replace, if exist, return idx*/
int * checkWord(const char * line, size_t length) {
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
char * parseWord(char * line, size_t len, int * idx) {
  char * firstString = strndup(line, idx[0]);
  char * myWord = getWord(line, idx);
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
char * getWord(const char * line, int * idx) {
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
