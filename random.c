#include <stdlib.h>
#include <stdbool.h>
#include "random.h"

int generate_int(int minimum, int maximum) {
  int rand_number = random() % (minimum + maximum + 1);
  rand_number += minimum;

  return rand_number;
}

_Bool probability_select(int percent) {
  int new_percent = percent;
  if ((percent < 0) || (percent > 100))
    new_percent = 20;

  int temp = generate_int(0, 100);
  if (temp <= new_percent)
    return true;

  return false;
}
