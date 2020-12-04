#include <stdlib.h>
#include <time.h>
#include <math.h>

void seed_random() {
  srandom(time(NULL));
}

double random_double() {
  long value = random();
  return value / pow(2, 31);
}
