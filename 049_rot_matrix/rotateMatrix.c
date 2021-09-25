#include "stdio.h"
#include "stdlib.h"

void rotate(FILE * f) {
  int c;
  char matrix[10][10] = {{0}};
  // size_t i = 0;
  // size_t j = 0;
  //while ((c = fgetc(f)) != EOF)
  //  printf("i= %zu, j = %zu", i, j);

  int counter = 0;
  char text[109];
  while ((c = fgetc(f)) != EOF) {
    if (counter < 109) {
      text[counter] = c;
      // printf("%c", text[counter]);
    }
    // else {
    // fprintf(stderr, "Invalid matrix: counter > 110 \n");
    //  exit(EXIT_FAILURE);
    //}
    counter++;
  }

  if (counter - 1 != 109) {  //if size not equal to 109
    fprintf(stderr, "Invalid matrix: 109\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 109; i++) {
    if (text[i] == '\n') {
      if ((i + 1) % 11 != 0) {
        fprintf(stderr, "Invalid matrix: not allow non-mod11 to new line\n");
        exit(EXIT_FAILURE);
      }
    }

    if ((i + 1) % 11 == 0) {
      if (text[i] != '\n') {
        fprintf(stderr, "Invalid matrix: mod11 must to new line\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  // fill the matrix
  counter = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      if ((counter + 1) % 11 != 0) {
        // printf("%c--", text[counter]);
        matrix[i][j] = text[counter];
      }
      counter++;
    }
  }

  //test
  // for (int i = 0; i < 10; i++) {
  // for (int j = 0; j < 10; j++) {
  // printf("%c", matrix[i][j]);
  // }
  // printf("\n");
  //}

  char rotateMatrix[10][10] = {{0}};

  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      rotateMatrix[j][9 - i] = matrix[i][j];
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
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
