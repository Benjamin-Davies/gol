#include <stdio.h>

#include "gol.h"

int main(int argc, char **argv) {
  grid_t grid;

  if (argc != 1) {
    fprintf(stderr, "usage: %s", argv[0]);
    exit(1);
  }

  grid = read_grid();

  print_grid(grid);

  dispose_grid(grid);
}
