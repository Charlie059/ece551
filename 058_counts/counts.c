#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkRepeat(counts_t * c, const char * name) {
  if (c->one_count_arr != NULL && name != NULL) {
    for (size_t i = 0; i < c->size; i++) {
      char * value = c->one_count_arr[i]->value;
      if (strcmp(value, name) == 0) {
        return i;
      }
    }
  }

  if (name == NULL) {
    c->unknown++;

    return -1;
  }

  return -2;  // nothing matched
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * ans = malloc(sizeof(*ans));
  ans->size = 0;
  ans->unknown = 0;
  ans->one_count_arr = NULL;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME

  int isRepeat = checkRepeat(c, name);

  if (isRepeat == -2) {
    c->one_count_arr =
        realloc(c->one_count_arr, (c->size + 1) * sizeof(*c->one_count_arr));
    c->one_count_arr[c->size] = malloc(sizeof(*c->one_count_arr[c->size]));

    c->one_count_arr[c->size]->count = 1;
    c->one_count_arr[c->size]->value = strdup(name);
    c->size++;
  }
  else if (isRepeat == -1) {
  }
  else {
    c->one_count_arr[isRepeat]->count++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME

  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->one_count_arr[i]->value, c->one_count_arr[i]->count);
  }
  fprintf(outFile, "<unknown>: %d\n", c->unknown);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    free(c->one_count_arr[i]->value);
    free(c->one_count_arr[i]);
  }
  free(c->one_count_arr);
  free(c);
}
