#include <stdio.h>

#include "gol.h"

int main(int argc, char **argv) {
  grid_size_t size;
  grid_t grid;
  
  if (!(argc == 2 && read_grid_size(argv[1], &size))) {
    printf("usage: %s WIDTHxHEIGHT\n", argv[0]);
    return 1;
  }

  grid = new_grid(size);

  fill_grid(grid, ' ');
  print_grid(grid);

  dispose_grid(grid);
}
