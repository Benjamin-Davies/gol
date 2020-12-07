#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#include "gol.h"

int stdin_fd;
struct termios orig_termios;
void reset_inputs() {
  tcsetattr(stdin_fd, TCSAFLUSH, &orig_termios);
}
void prepare_inputs() {
  struct termios raw;

  fclose(stdin);
  stdin = fdopen(2, "r");
  stdin_fd = fileno(stdin);

  tcgetattr(stdin_fd, &orig_termios);
  atexit(reset_inputs);

  raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(stdin_fd, TCSAFLUSH, &raw);

  fcntl(stdin_fd, F_SETFL, O_NONBLOCK);
}

long millis() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t);
  return t.tv_sec * 1000l + t.tv_nsec / 1000000l;
}

int main(int argc, char **argv) {
  grid_t source_grid, dest_grid, temp;
  int input, running, paused;
  long delay, frame_start;

  delay = 0;
  running = 1;
  paused = 0;

  if (!(argc == 1 ||
        argc == 2 && sscanf(argv[1], "%ld", &delay))) {
    fprintf(stderr, "usage: %s [delay_in_ms]", argv[0]);
    exit(1);
  }

  source_grid = read_grid();
  dest_grid = new_grid(source_grid.size);

  prepare_inputs();
  // Clear the terminal (same output as the clear command)
  fprintf(stderr, "\x1b[H\x1b[J");

  while (running) {
    frame_start = millis();
    step_grid(source_grid, dest_grid);

    // Move to top left and display the grid
    fprintf(stderr, "\x1b[H");
    fprint_grid(dest_grid, stderr);

    temp = source_grid;
    source_grid = dest_grid;
    dest_grid = temp;

    while (1) {
      input = getchar();
      // 0x1b is ESC
      if (input == 0x1b) {
        running = 0;
        break;
      }

      if (input == '\n')
        break;
      if (input == ' ')
        paused = !paused;
      if (delay > 0 && !paused &&
          millis() > delay + frame_start)
        break;

      usleep(500);
    }
  }

  print_grid(dest_grid);

  dispose_grid(source_grid);
  dispose_grid(dest_grid);
}
