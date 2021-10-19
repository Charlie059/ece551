#include "rand_story.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    printError("Expect two arg (including name).");
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cannot open this file");
    EXIT_FAILURE;
  }

  //category_t * tracker = malloc(sizeof(*tracker));
  readStoryFile(f, NULL, NULL);

  //free
  //freeTrackerArr(tracker);

  if (fclose(f) != 0) {
    printError("Cannot close file.");
    EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
