#include <stdlib.h>
#include <string.h>

typedef struct {
  int cols;
  int rows;
} grid_size_t;

typedef struct {
  grid_size_t size;
  char *str;
} grid_t;

int read_grid_size(char *input, grid_size_t *size) {
  return sscanf(input, "%dx%d", &size->cols, &size->rows) == 2;
}

size_t grid_str_len(grid_size_t size) {
  return size.rows * (size.cols + 1);
}

size_t grid_cell_index(grid_size_t size, int col, int row) {
  return col + row * (size.cols + 1);
}

grid_t new_grid(grid_size_t size) {
  size_t len;
  grid_t grid;

  len = grid_str_len(size);
  grid.size = size;
  grid.str = malloc(len + 1);

  for (size_t i = size.cols; i < len; i += size.cols + 1) {
    grid.str[i] = '\n';
  }
  grid.str[len] = 0;

  return grid;
}

char *read_all_stdin() {
  char *str;
  size_t read, len, allocated;
  len = 0;
  allocated = 1024;
  str = malloc(allocated);

  while ((read = fread(&str[len], 1, allocated - len, stdin))) {
    len += read;
    if (len + 1 < allocated) break;

    allocated *= 2;
    str = realloc(str, allocated);
  }

  str[len] = 0;
  str = realloc(str, len + 1);
  return str;
}

grid_size_t guess_grid_size(char *str) {
  grid_size_t size;
  size_t len;
  int i;

  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (str[i] == '\n')
      break;
  }
  size.cols = i;
  size.rows = len / (i + 1);

  return size;
}

grid_t read_grid() {
  grid_t grid;
  char *str;
  grid_size_t size;

  str = read_all_stdin();
  size = guess_grid_size(str);

  grid.size = size;
  grid.str = str;
  return grid;
}

void dispose_grid(grid_t grid) {
  free(grid.str);
}

void set_grid_cell(grid_t grid, int col, int row, char value) {
  size_t index = grid_cell_index(grid.size, col, row);
  grid.str[index] = value;
}

void fill_grid(grid_t grid, char value) {
  for (int i = 0; i < grid.size.rows; i++) {
    for (int j = 0; j < grid.size.cols; j++) {
      set_grid_cell(grid, j, i, value);
    }
  }
}

void print_grid(grid_t grid) {
  printf("%s", grid.str);
}
