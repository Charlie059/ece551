#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  // kvpairs: apple=red ban=blue
  // file: apple ban c
  // out: red: 1, blue: 1, unknown: 1

  FILE * f = fopen(filename, "r");
  char * line = NULL;
  size_t sz;
  ssize_t len = 0;

  counts_t * ans = createCounts();

  while ((len = getline(&line, &sz, f)) >= 0) {
    line[len - 1] = '\0';
    // printf("%s\n", line);

    addCount(ans, (lookupValue(kvPairs, line)));
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "argc error");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 0; i < argc; i++) {
    counts_t * count = countFile(argv[i], kv);
    char * out = computeOutputFileName(argv[i]);

    FILE * f = fopen(out, "w");
    printCounts(count, f);
    free(out);
    free(count);
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close the file");
    }
  }
  free(kv);
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
