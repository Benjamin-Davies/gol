#include <stdlib.h>
#include <time.h>
#include <math.h>

void seed_random() {
  srandom(time(NULL));
}

float random_float() {
  long value = random();
  return value / powf(2, 31);
}
