all: golclear golrandom

gol%: gol%.c %.h
	gcc $< -o $@
