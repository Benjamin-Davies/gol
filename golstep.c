#include <stdio.h>
#include <unistd.h>

#include "gol.h"

int count_neighboors(grid_t grid, int col, int row) {
  int count;
  count = 0;
  if (get_grid_cell(grid, col+1, row  ) != ' ') count++;
  if (get_grid_cell(grid, col+1, row+1) != ' ') count++;
  if (get_grid_cell(grid, col  , row+1) != ' ') count++;
  if (get_grid_cell(grid, col-1, row+1) != ' ') count++;
  if (get_grid_cell(grid, col-1, row  ) != ' ') count++;
  if (get_grid_cell(grid, col-1, row-1) != ' ') count++;
  if (get_grid_cell(grid, col  , row-1) != ' ') count++;
  if (get_grid_cell(grid, col+1, row-1) != ' ') count++;
  return count;
}

void step_grid(grid_t source_grid, grid_t dest_grid) {
  char value;
  int i, j, neighboors, self;

  for (i = 0; i < source_grid.size.rows; i++) {
    for (j = 0; j < source_grid.size.cols; j++) {
      neighboors = count_neighboors(source_grid, j, i);
      self = get_grid_cell(source_grid, j, i) != ' ';
      if (self)
        value = (neighboors == 2 || neighboors == 3)
          ? 'x' : ' ';
      else
        value = neighboors == 3
          ? 'x' : ' ';
      set_grid_cell(dest_grid, j, i, value);
    }
  }
}

int main(int argc, char **argv) {
  grid_t source_grid, dest_grid, temp;

  if (argc != 1) {
    fprintf(stderr, "usage: %s", argv[0]);
    exit(1);
  }

  source_grid = read_grid();
  dest_grid = new_grid(source_grid.size);

  while (1) {
    printf("\x1b[H\x1b[J");
    fill_grid(dest_grid, ' ');
    step_grid(source_grid, dest_grid);

    print_grid(dest_grid);

    temp = source_grid;
    source_grid = dest_grid;
    dest_grid = temp;
    usleep(200000);
  }

  dispose_grid(source_grid);
  dispose_grid(dest_grid);
}
