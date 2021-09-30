#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortLines(void * f) {
  if (f == NULL) {
    fprintf(stderr, "No lines!");
    exit(EXIT_FAILURE);
  }

  ssize_t len = 0;
  size_t sz = 0;
  char * line = NULL;
  char ** strArray = NULL;
  size_t counter = 0;
  while ((len = getline(&line, &sz, f)) >= 0) {
    char * str = malloc((len + 1) * sizeof(*str));
    strncpy(str, line, len + 1);

    strArray = realloc(strArray, (counter + 1) * sizeof(*strArray));
    strArray[counter] = str;
    counter++;
  }

  //sort
  sortData(strArray, counter);
  // print
  for (size_t i = 0; i < counter; i++) {
    printf("%s", strArray[i]);
  }

  // Free
  for (size_t i = 0; i < counter; i++) {
    free(strArray[i]);
  }
  free(strArray);
  free(line);
}

void openFiles(int argc, char ** argv) {
  for (int i = 0; i < argc - 1; i++) {
    FILE * f = fopen(argv[i + 1], "r");
    sortLines(f);
    fclose(f);
  }
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  if (argc == 1) {
    sortLines(stdin);
  }
  else {
    openFiles(argc, argv);
  }
  return EXIT_SUCCESS;
}
