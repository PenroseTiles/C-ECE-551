#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

typedef struct bio {
  int months;
  double balance;
} bio;

double monthly_update(double balance, double rate, double contribution) {
  double interest = balance * rate / 100;
  return balance + interest + contribution;
}

void print_bio(bio biodata) {
  int months = biodata.months % 12;
  int years = biodata.months / 12;
  printf("Age %3d month %2d you have $%.2lf\n", years, months, biodata.balance);
}

bio evaluate_period(bio biodata, retire_info information) {
  int currMonth = 0;
  while (currMonth < information.months) {
    print_bio(biodata);
    biodata.balance = monthly_update(
        biodata.balance, information.rate_of_return, information.contribution);
    currMonth++;
    biodata.months++;
  }
  return biodata;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  bio biodata;
  biodata.balance = initial;
  biodata.months = startAge;

  bio after_working = evaluate_period(biodata, working);
  evaluate_period(after_working, retired);
  return;
}

int main() {
  retire_info working;
  working.contribution = 1000;
  working.months = 489;
  working.rate_of_return = 4.5 / 12;

  retire_info retired;
  retired.contribution = -4000;
  retired.months = 384;
  retired.rate_of_return = 1.0 / 12;
  //printf("%f\n", retired.rate_of_return);
  int startAge = 327;
  double initial_savings = 21345;
  retirement(startAge, initial_savings, working, retired);
  return EXIT_SUCCESS;
}
