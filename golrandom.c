#include <stdio.h>

#include "gol.h"
#include "random.h"

int main(int argc, char **argv) {
  grid_size_t size;
  grid_t grid;
  double threshold = 0.5;
  char value;
  
  if (!(argc == 2 && read_grid_size(argv[1], &size)) &&
      !(argc == 3 && read_grid_size(argv[1], &size) &&
        sscanf(argv[2], "%lf", &threshold))) {
    fprintf(stderr, "usage: %s WIDTHxHEIGHT [THRESHOLD]\n", argv[0]);
    exit(1);
  }

  grid = new_grid(size);

  seed_random();
  for (int i = 0; i < grid.size.rows; i++) {
    for (int j = 0; j < grid.size.cols; j++) {
      value = random_double() < threshold ? 'x' : ' ';
      set_grid_cell(grid, j, i, value);
    }
  }
  print_grid(grid);

  dispose_grid(grid);
}
