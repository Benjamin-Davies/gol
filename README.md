% GOL(1) Conway's Game of Life

# NAME

**golclear**, **golrandom**, **golstep**, **golrun** - implementation of
Conway's Game of Life in C

# SYNOPSIS

| **golclear** *width*x*height*
| **golrandom** *width*x*height* \[*threshold*]
| **golstep**
| **golrun** \[*delay_in_ms*]

# DESCRIPTION

**gol** is a collection of programs that allow users to simulate and play with
Conway's Game of Life. One thing that is special about this implementation is
that all grid state, both internal and external, is stored in plain-text. This
allows for the output of one command to be saved to a text file, edited in any
text editor, and then inputed into another command. Alive cells are stored as
lowercase **x**es, and dead ones as spaces.

While this makes it very easy to edit saved states, keep in mind that the
programs expect all lines (including the last) to end with a newline character,
and that all lines are the same length as the first line. Your text editor may
not automatically add a trailing newline, so you may need to add one yourself.
Do not hesitate to add an extra newline if you are unsure because the programs
will not simulate trailing characters if they are less than the length of the
first line. **VIM** is ideal for this task as it implicitly adds trailing
newlines, and it also supports single character replacement using **r**.

**golclear** is a program that takes the dimensions of the grid as an argument,
and outputs an empty grid of that size (full of spaces).

**golrandom** is a program that takes the dimensions of the grid and a theshold
value as arguments, and outputs an randomized grid of that size. The threshold
value is the probability that any given cell will be an **x**, so a threshold
of 0.5 will give a grid with ~50% **x**es and ~50% spaces.

**golstep** is a program that reads a grid from stdin, simulates one step of
the algorithm, and then outputs the resulting grid.

**golrun** is a program that reads a grid from stdin, and then repeatedly
simulates it, outputting the resulting grid when it finishes. The current grid
state is displayed on the terminal connected to stderr. By default, it will
only simulate a step when the user presses the **ENTER** key, but a
*delay_in_ms* argument may be specified to tell the program to automatically
simulate a step every *delay_in_ms* milliseconds. They user may also press the
**SPACEBAR** to pause the simulation, or the **ESC** key to end it. Exiting the
program using **Ctrl-C** will work, but the resulting grid will not be
outputted.

# EXIT STATUS

| **0** - success
| **1** - invalid arguments

# EXAMPLES

The command:

```
golrandom 20x20 | golrun 100
```

will generate a random 20 by 20 cell grid, and then simulate it with a delay
between steps of 100ms.

The command:

```
golstep < grid1 > grid 2
```

will read a grid from a file named **grid1**, run one step of the simulation,
then output the result to a file named **grid2**.

The command:

```
golclear 100x30 > grid
vim grid
golrun < grid
```

will generate an empty 100 by 30 grid in the file **grid**. It will then open
the file in **VIM**, allowing the user to edit it. Finally it will simulate
the grid, requiring the user to press **ENTER** for each step.

# AUTHOR

Benjamin Davies \<bentendavies at gmail dot com>

# SEE ALSO

vim(1)

https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
