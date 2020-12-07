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

char get_grid_cell(grid_t grid, int col, int row) {
  if (col < 0 || col >= grid.size.cols ||
      row < 0 || row >= grid.size.rows)
    return ' ';
  size_t index = grid_cell_index(grid.size, col, row);
  return grid.str[index];
}

void set_grid_cell(grid_t grid, int col, int row, char value) {
  if (col < 0 || col >= grid.size.cols ||
      row < 0 || row >= grid.size.rows)
    return;
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

void fprint_grid(grid_t grid, FILE *file) {
  fprintf(file, "%s", grid.str);
}

int grid_count_neighboors(grid_t grid, int col, int row) {
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
      neighboors = grid_count_neighboors(source_grid, j, i);
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

