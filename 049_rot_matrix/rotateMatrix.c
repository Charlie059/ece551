#include "stdio.h"
#include "stdlib.h"

void rotate(FILE * f) {
  int c;
  char matrix[10][10] = {{0}};
  size_t i = 0;
  size_t j = 0;
  while ((c = fgetc(f)) != EOF) {
    if (c != '\n') {
      if (i < 10 && j < 10) {
        matrix[i][j] = c;
        j++;
      }
      else {
        return exit(EXIT_FAILURE);
      }
    }
    else {
      if (j != 10 || i > 9) {
        return exit(EXIT_FAILURE);
      }
      else {
        j = 0;  //reset j
        i++;    // new row
      }
    }
  }

  char rotateMatrix[10][10] = {{0}};
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 9; j++) {
      rotateMatrix[j][9 - i] = matrix[i][j];
    }
  }

  for (int i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%c", rotateMatrix[i][j]);
    }
    printf("\n");
  }
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Check your argc\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  rotate(f);

  return EXIT_SUCCESS;
}
