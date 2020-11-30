#include "pandemic.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validateInputs(char * lindex,
                    char * rindex,
                    char * line,
                    country_t * ans,
                    size_t length_name,
                    size_t length_population) {
  /*
    Check that (1) every line of input has exactly one comma
    (2) name of the country isn't too long
    (3) population isn't large enough to cause stack smashing/segfault
   */
  if (lindex != rindex || lindex == NULL) {  //check that input has exactly one comma
    printf("Line entered by user is:\n %s\nCorrect format is country,population\n", line);
    exit(EXIT_FAILURE);
  }
  if (length_name >= sizeof(ans->name)) {  //checking for length of country's name
    printf("Name of country can be at most %ld characters long", sizeof(ans->name));
    exit(EXIT_FAILURE);
  }

  if (length_population > 20 ||
      (length_population == 20 && (strcmp("18446744073709551615", lindex + 1) <
                                   0))) {  //checking for possible overflow
    printf("population %s is above 18446744073709551615\n", lindex + 1);
    exit(EXIT_FAILURE);
  }
}

void validatePopulation(char * population_string, size_t size) {
  /*
    check that population is a numeric string, no whitespace or non-numeral characters
   */
  size_t i = 0;
  int c;
  size_t num_digits = 0;
  while ((c = population_string[i]) != '\0' && i < size) {
    if (c == '\n' && num_digits > 0) {
      return;
    }
    else if (c == '\n' && num_digits == 0) {
      printf("empty value entered for population\n");
      exit(EXIT_FAILURE);
    }

    if (isdigit(c)) {
      num_digits++;
    }
    else {
      printf("%s is not a valid population\n", population_string);
      printf("input format is name,population\n");
      printf("population can only have numerical characters, no whitespace\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }
  if (num_digits == 0) {
    printf("no number after comma, invalid population\n");
    exit(EXIT_FAILURE);
  }
}

country_t parseLine(char * line) {
  /*
    Step 1. Validate all inputs, split by comma and parse both fields
   */
  country_t ans;
  char * lindex = strchr(line, ',');
  char * rindex = strrchr(line, ',');

  size_t length_name = (lindex - line) / sizeof(char);
  size_t length_population = strlen(line) - length_name;
  validateInputs(lindex, rindex, line, &ans, length_name, length_population);
  strncpy(ans.name, line, length_name * sizeof(char));
  ans.name[length_name] = '\0';

  size_t max_population_length = 30;
  char population_string[max_population_length];
  strncpy(population_string, lindex + 1, max_population_length);
  validatePopulation(population_string, max_population_length);
  ans.population = atoi(population_string);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  /*
    Step 2. Calculate average for first 7 days, then update it in an online manner
   */
  if (n_days < 7 || data == NULL || avg == NULL) {
    printf("ILLEGAL INPUT TO calcRunningAvg, exiting with error");
    exit(EXIT_FAILURE);
  }
  double running_total = 0.0;
  size_t i = 0;
  for (; i < 7; i++) {
    running_total += 1.0 * data[i];
  }
  for (; i < n_days; i++) {
    avg[i - 7] = running_total / 7.0;
    //for every day from day 7, add the new cases and subtract cases before this week
    running_total += (1.0 * data[i] - 1.0 * data[i - 7]);
  }
  avg[i - 7] = running_total / 7.0;
  return;
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  /*
   Step 3. Calculate cumulative cases and multiply by 100k/population
   */
  double per100k = 1.0 * 100000 / pop;
  unsigned total = 0.0;
  if (n_days == 0 || data == NULL || cum == NULL) {
    printf("illegal input to calcCumulative, exit with error\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days; i++) {
    total += data[i];
    cum[i] = total * per100k;
  }
  return;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  /*
    Step 4. Loop over all countries and days, find the highest cases and corresponding country
   */
  if (n_countries == 0 || n_days == 0 || countries == NULL || data == NULL) {
    printf("Illegal input to printCountryWithmax, exit with error\n");
    exit(EXIT_FAILURE);
  }

  unsigned maxval = 0;
  country_t max_country;
  // loop over all countries
  for (size_t country_index = 0; country_index < n_countries; country_index++) {
    //loop over all days
    for (size_t day = 0; day < n_days; day++) {
      if (data[country_index][day] >= maxval) {
        max_country = countries[country_index];
        maxval = data[country_index][day];
      }
    }
  }
  printf("%s has the most daily cases with %u\n", max_country.name, maxval);
}
