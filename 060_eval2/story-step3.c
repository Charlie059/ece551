#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
#include "string.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    printError("Expect three arg (including name).");
  }

  FILE * f_word = fopen(argv[1], "r");
  FILE * f_story = fopen(argv[2], "r");
  if (f_word == NULL || f_story == NULL) {
    printError("Cannot open the file");
    EXIT_FAILURE;
  }

  category_t * tracker = malloc(sizeof(*tracker));
  // init tracker
  initTracker(tracker);

  /*  READ WORD FILE */
  catarray_t * catArr = malloc(sizeof(*catArr));
  readWordFile(f_word, catArr);

  /*  READ STORY FILE */
  readStoryFile(f_story, catArr, tracker);

  // free
  freeCatarry(catArr);
  freeTrackerArr(tracker);
  free(tracker);

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
