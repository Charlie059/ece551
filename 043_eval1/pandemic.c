#include "pandemic.h"

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>

#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"

// Function which print the error message
void printError(char * error) {
  fprintf(stderr, "%s", error);
}

// Function which check population value is vaild
/* void checkVaild(size_t length, char temp[]) { */
/*   for (size_t i = 0; i < length; i++) { */
/*     if (isdigit(temp[i]) == 0 && i != 0) { */
/*       printError("Expect population is all digit.\n"); */
/*       exit(EXIT_FAILURE); */
/*     } */
/*     if (i == 0 && temp[0] != '-') { */
/*       if (isdigit(temp[0]) == 0) { */
/*         printError("Expect population is all digit.\n"); */
/*         exit(EXIT_FAILURE); */
/*       } */
/*     } */
/*   } */
/* } */
// Task 1
country_t parseLine(char * line) {
  country_t ans;
  const char * readLine = line;                       // Get the input String
  const char * ptr_comma = strchr(readLine, ',');     // Check the first comma occurance
  const char * ptr_newline = strchr(readLine, '\n');  // A pointer point to newline
  const char * ptr_nt = strchr(readLine, '\0');       // Define the null-terminated
  size_t popLen = ptr_nt - ptr_comma - 1;  // Define the length of population string
  char temp[21] = "";                      // temp to store the population value
  size_t countryLen = 0;                   // define the country name length

  if (ptr_comma == NULL) {  //If no comma found, return failure.
    printError("Expect comma, but nothing found.\n");
    exit(EXIT_FAILURE);
  }

  // Check the length of country name
  countryLen = ptr_comma - readLine;
  if (countryLen >= MAX_NAME_LEN) {
    printError("Expect country name size less than 64.\n");
    exit(EXIT_FAILURE);
  }

  //Copy the name part to the ans's name
  for (size_t i = 0; i < countryLen + 1; i++) {
    if (i != countryLen) {
      ans.name[i] = readLine[i];
    }
    else {
      ans.name[i] = '\0';
    }
  }

  // Check the length of population input string
  if (popLen > 21) {
    printError("Expect country population size less than or equal to MAX_U_INT_64.\n");
    exit(EXIT_FAILURE);
  }

  strncpy(temp, ptr_comma + 1, popLen);  // Copy the population to the temp string

  // Check the vaild population
  if (ptr_newline == NULL) {
    //    checkVaild(popLen, temp);  // Check if temp has non-value char after first digit
    if (popLen == 0) {  // Check if no population
      printError("Expect country population, but not found.\n");
      exit(EXIT_FAILURE);
    }
  }
  else {                              // If the input contains newline
    if (ptr_newline + 1 != ptr_nt) {  // If newline is not close to the non-terminal
      printError("Expect population is all digit, found newline is not last digit "
                 "(without nonterminal char).\n");
      exit(EXIT_FAILURE);
    }
    else {
      //     checkVaild(popLen - 1,
      //         temp);   // Check if temp has non-value char after first digit
      if (popLen == 1) {  // Check if no population
        printError("Expect country population, but not found.\n");
        exit(EXIT_FAILURE);
      }
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

//Task 2
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  // Check if n_days less than 7
  if (n_days < 7) {
    return;
  }

  // Calculate the avg
  for (size_t i = 0; i < n_days - 6; i++) {
    double sum = 0;
    for (size_t j = 0; j < 7; j++) {
      sum += data[i + j];
    }
    avg[i] = sum / 7;
  }
}

//Task 3
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  double cumulative_data = 0;
  for (size_t i = 0; i < n_days; i++) {
    cumulative_data += data[i];  //cumlative the daily data
    cum[i] = (cumulative_data / pop) * 100000;
  }
}

//Task 4
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned int max_daily_arr[n_countries];  //Def max daily case in each country
  int tie = 0;  // def if there are at least two max daily countries

  // get the max daily case in each country and store in max_daily_arr
  for (size_t i = 0; i < n_countries; i++) {
    unsigned int max_daily = 0;
    for (size_t j = 0; j < n_days; j++) {
      if (max_daily < data[i][j]) {
        max_daily = data[i][j];
      }
    }
    max_daily_arr[i] = max_daily;
  }

  // Find the max value by comparing each countries' max cases
  unsigned int max_daily_country = 0;
  size_t max_country_idx = 0;
  for (size_t i = 0; i < n_countries; i++) {
    if (max_daily_country < max_daily_arr[i]) {
      max_daily_country = max_daily_arr[i];
      max_country_idx = i;
    }
  }

  // Check if tie
  for (size_t i = 0; i < n_countries; i++) {
    if (i != max_country_idx && max_daily_arr[i] == max_daily_country) {
      tie = 1;
      break;
    }
  }

  // If no tie, printout max country
  if (tie == 0) {
    printf("%s has the most daily cases with %u\n",
           countries[max_country_idx].name,
           max_daily_country);
  }
  else {  //else print tie message
    printf("There is a tie between at least two countries");
  }
}
