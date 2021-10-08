#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME

  const char * extension = ".counts";

  char * new = NULL;
  new = malloc(strlen(inputName) + 1 + 7);

  strcpy(new, inputName);
  strcat(new, extension);
  return new;
}
