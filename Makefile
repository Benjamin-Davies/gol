RES = golclear golrandom golstep golrun

all: $(RES)

golclear: golclear.c gol.h
	cc $< -o $@

golrandom: golrandom.c gol.h random.h
	cc $< -o $@

golstep: golstep.c gol.h
	cc $< -o $@

golrun: golrun.c gol.h
	cc $< -o $@

gol.1: gol.1.md
	pandoc --standalone --to man gol.1.md -o gol.1

clean:
	rm -f $(RES) gol.1

install-home: all gol.1
	mkdir -p $(HOME)/.local/bin
	cp $(RES) $(HOME)/.local/bin/
	mkdir -p $(HOME)/.local/share/man/man1
	cp gol.1 $(HOME)/.local/share/man/man1/gol.1

.PHONY: clean install-local
