#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "No file exist!\n");
    exit(EXIT_FAILURE);
  }

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  // Create kv_array
  kvarray_t * kv = malloc(sizeof(*kv));
  size_t kv_len = 0;
  kv->pairs = NULL;

  while ((len = getline(&line, &sz, f)) >= 0) {
    char * first_equal = strstr(line, "=");
    if (first_equal == NULL) {
      fprintf(stderr, "No '=' symbol\n");
      exit(EXIT_FAILURE);
    }

    size_t key_len = first_equal - line;
    char key[key_len + 1];
    memset(key, '\0', key_len + 1);
    /* strncpy(key, line, key_len); */

    for (size_t i = 0; i < key_len; i++) {
      key[i] = line[i];
    }
    key[key_len] = '\0';

    if (line[len - 1] == '\n') {
      len--;
    }

    size_t value_len = len - key_len - 1;
    char value[value_len + 1];

    //    memset(value, '\0', key_len + 1);
    strncpy(value, first_equal + 1, value_len);

    kv->pairs = realloc(kv->pairs, (kv_len + 1) * sizeof(*kv->pairs));
    kv->pairs[kv_len] = malloc(sizeof(*kv->pairs[kv_len]));

    /* kv->pairs[kv_len]->key = malloc((key_len + 1) * sizeof((kv->pairs[kv_len]->key))); */
    /* memset(kv->pairs[kv_len]->key, '\0', key_len + 1); */
    /* kv->pairs[kv_len]->value = */
    /*     malloc((value_len + 1) * sizeof((kv->pairs[kv_len]->value))); */
    /* memset(kv->pairs[kv_len]->value, '\0', value_len + 1); */

    /* strncpy(kv->pairs[kv_len]->key, key, key_len); */
    /* strncpy(kv->pairs[kv_len]->value, value, value_len); */

    kv->pairs[kv_len]->key = strndup(key, key_len);
    kv->pairs[kv_len]->value = strndup(value, value_len);
    kv_len++;
  }

  free(line);
  kv->length = kv_len;

  if (fclose(f) != 0) {
    fprintf(stderr, "Close File Error.\n");
    return NULL;
  }

  return kv;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t len = pairs->length;
  for (size_t i = 0; i < len; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]->value);
    free(pairs->pairs[i]);
  }

  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs == NULL) {
    return;
  }

  size_t len = 0;
  len = pairs->length;
  for (size_t i = 0; i < len; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i]->key, pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t len = pairs->length;
  for (size_t i = 0; i < len; i++) {
    char * search_key = pairs->pairs[i]->key;
    if (strcmp(search_key, key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}
