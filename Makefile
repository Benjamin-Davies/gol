all: golclear golrandom

gol%: gol%.c gol.h
	gcc $< -o $@
