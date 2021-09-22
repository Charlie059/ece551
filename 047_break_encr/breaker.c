#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int breaker(FILE * f) {
  size_t counter[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      counter[c] += 1;
    }
  }

  size_t max_current = 0;
  size_t max_idx = 0;
  // Find the Top 1 Char
  for (size_t i = 0; i < 26; i++) {
    if (max_current <= counter[i]) {
      max_current = counter[i];
      max_idx = i;
    }
  }

  // rm the Top 1
  counter[max_idx] = 0;
  max_idx += 'a';

  int vote[3] = {0};

  vote[0] = max_idx - 'e';
  // Find the Top 2 Char

  max_current = 0;
  max_idx = 0;

  for (size_t i = 0; i < 26; i++) {
    if (max_current <= counter[i]) {
      max_current = counter[i];
      max_idx = i;
    }
  }

  counter[max_idx] = 0;
  max_idx += 'a';
  vote[1] = max_idx - 't';

  // Find the Top 3 Char

  max_current = 0;
  max_idx = 0;
  // Find the Top 1 Char
  for (size_t i = 0; i < 26; i++) {
    if (max_current <= counter[i]) {
      max_current = counter[i];
      max_idx = i;
    }
  }

  max_idx += 'a';
  vote[2] = max_idx - 'a';

  if (vote[0] == vote[1]) {
    return vote[0];
  }
  else if (vote[1] == vote[2]) {
    return vote[1];
  }
  else if (vote[0] == vote[2]) {
    return vote[0];
  }
  else {
    return vote[0];
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int result = breaker(f);
  fprintf(stdout, "%d\n", result);
  return EXIT_SUCCESS;
}
