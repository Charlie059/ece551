#include "stdio.h"
#include "stdlib.h"

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double month_calculator(double current, double contribution, double rate_year) {
  current = current * (1 + rate_year / 1200) + contribution;
  return current;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int age = startAge;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, initial);
    initial = month_calculator(initial, working.contribution, working.rate_of_return);
    age++;
  }

  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, initial);
    initial = month_calculator(initial, retired.contribution, retired.rate_of_return);
    age++;
  }
}

int main() {
  retire_info working = {489, 1000, 4.5};
  retire_info retired = {384, -4000, 1};

  retirement(327, 21345, working, retired);
  return 0;
}
