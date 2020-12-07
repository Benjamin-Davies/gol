#include <stdio.h>
#include <unistd.h>

#include "gol.h"

int main(int argc, char **argv) {
  grid_t source_grid, dest_grid;

  if (argc != 1) {
    fprintf(stderr, "usage: %s", argv[0]);
    exit(1);
  }

  source_grid = read_grid();
  dest_grid = new_grid(source_grid.size);

  step_grid(source_grid, dest_grid);
  print_grid(dest_grid);

  dispose_grid(source_grid);
  dispose_grid(dest_grid);
}
