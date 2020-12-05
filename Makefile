all: golclear golrandom golstep

golclear: golclear.c gol.h
	cc $< -o $@

golrandom: golrandom.c gol.h random.h
	cc $< -o $@

golstep: golstep.c gol.h
	cc $< -o $@

.PHONY: clean
clean:
	rm -f golclear golrandom golstep
