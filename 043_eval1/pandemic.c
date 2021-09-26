#include "pandemic.h"

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>  //?

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
// Function which print the error message
void printError(char * error) {
  fprintf(stderr, "%s", error);
}

country_t parseLine(char * line) {
  const char * readLine = line;  // Get the input String

  const char * ptr_comma = strchr(readLine, ',');  // Check the first comma occurance
  if (ptr_comma == NULL) {                         //If no comma found, return failure.
    printError("Expect comma, but nothing found.\n");
    exit(EXIT_FAILURE);
  }

  // Check the length of country name
  size_t countryLen = 0;
  countryLen = ptr_comma - readLine;
  if (countryLen > MAX_NAME_LEN) {  //63?
    printError("Expect country name size less than 64.\n");
    exit(EXIT_FAILURE);
  }

  // Treat all Strings before the comma (first occurance) as country names
  country_t ans;

  //Copy the name part to the ans's name

  for (size_t i = 0; i < countryLen + 1; i++) {
    if (i != countryLen) {
      ans.name[i] = readLine[i];
    }
    else {
      ans.name[i] = '\0';
    }
  }

  // Work on the population

  const char * ptr_nt = strchr(readLine, '\0');  // Define the null-terminated
  size_t popLen = ptr_nt - ptr_comma - 1;        // Define the length of population string

  char temp[21] = "";
  if (popLen > 21) {
    printError(
        "Expect country population size less than or equal to 18446744073709551615.\n");
    exit(EXIT_FAILURE);
  }
  //  strncpy(temp, ptr_comma + 1, popLen);  // Copy the population to the temp string

  for (size_t i = 0; i < popLen + 1; i++) {
    if (i != popLen) {
      temp[i] = readLine[i + countryLen + 1];
    }
    else {
      temp[i] = '\0';
    }
  }

  // Convert temp to uint_64_t
  uint64_t population = strtoumax(temp, NULL, 10);
  if (errno == ERANGE) {  // cite man ?
    printError("Expect population is less than MAX uint_64_t.\n");
    exit(EXIT_FAILURE);
  }

  ans.population = population;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
