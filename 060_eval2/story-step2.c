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

  /*  READ FILE */
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  catarray_t * catArr = malloc(sizeof(*catArr));
  //init catArr
  catArr->n = 0;
  catArr->arr = NULL;
  while ((len = getline(&line, &sz, f)) >= 0) {
    readWords(line, len, catArr);
  }

  printWords(catArr);

  freeCatarry(catArr);
  free(line);

  if (fclose(f) != 0) {
    printError("Cannot close file.");
    EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
