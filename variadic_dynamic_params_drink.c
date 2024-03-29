#include <stdio.h>
#include <stdarg.h>

enum drink { MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE};

double price(enum drink d)
{
  switch (d) {
    case MUDSLIDE:
      return 6.79;
    case FUZZY_NAVEL:
      return 5.31;
    case MONKEY_GLAND:
      return 4.81;
    case ZOMBIE:
      return 5.89;
  }
}
double total(int args, ...)
{
  double total = 0;

  va_list drinks;
  va_start(drinks, args);

  int i;
  for (i = 0; i < args; ++i) {
    total += price(va_arg(drinks, double));
  }
  va_end(drinks);

  return total;
}

int main(int argc, char **argv) {
  double total_price = total(3, MUDSLIDE, MONKEY_GLAND, ZOMBIE);

  printf("Total price is %f\n", total_price);
}
