#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
#include "string.h"

int main(int argc, char ** argv) {
  //Reject when imput argc not as 3 or 4
  if (!(argc == 3 || argc == 4)) {
    printError("Expect three or four arg (including name).");
  }

  FILE * f_word = NULL;
  FILE * f_story = NULL;
  int optionFlag = 0;

  if (argc == 3) {
    f_word = fopen(argv[1], "r");
    f_story = fopen(argv[2], "r");
  }
  else if (argc == 4) {
    // compare the option to '-n' if not return error
    if (strcmp("-n", argv[1]) != 0) {
      printError("Expect -n for option.");
    }
    // if yes, set option flag to 1
    optionFlag = 1;
    f_word = fopen(argv[2], "r");
    f_story = fopen(argv[3], "r");
  }

  if (f_word == NULL || f_story == NULL) {
    printError("Cannot open the file");
  }

  /*Declear and init a tracker to track we perivous use*/
  category_t * tracker = malloc(sizeof(*tracker));
  initTracker(tracker);

  /*READ WORD FILE*/
  catarray_t * catArr = malloc(sizeof(*catArr));
  readWordFile(f_word, catArr);

  //Record the n_words array, becasue when we delete something, the n_words will be changed
  size_t * n_wordsArr = malloc(catArr->n * sizeof(*n_wordsArr));
  for (size_t i = 0; i < catArr->n; i++) {
    n_wordsArr[i] = catArr->arr[i].n_words;
  }

  /*READ STORY FILE*/
  readStoryFile(f_story, catArr, tracker, optionFlag);

  /*Free*/
  freeCatarry(catArr, n_wordsArr);
  freeTrackerArr(tracker);
  free(tracker);
  free(n_wordsArr);
  if (fclose(f_story) != 0) {
    printError("Cannot close file.");
    EXIT_FAILURE;
  }
  if (fclose(f_word) != 0) {
    printError("Cannot close file.");
    EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
