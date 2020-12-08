PREFIX ?= /usr/local

PROGRAMS = golclear golrandom golstep golrun

all: $(PROGRAMS)

golclear: golclear.c gol.h
	cc $< -o $@

golrandom: golrandom.c gol.h random.h
	cc $< -o $@

golstep: golstep.c gol.h
	cc $< -o $@

golrun: golrun.c gol.h
	cc $< -o $@

gol.1: README.md
	pandoc --standalone --to man README.md -o gol.1

clean:
	rm -f $(PROGRAMS) gol.1

install: all gol.1
	install -D -m 644 gol.1 $(PREFIX)/share/man/man1/gol.1
	for prog in $(PROGRAMS); do \
		install -D $$prog $(PREFIX)/bin/$$prog; \
		ln -sf gol.1 $(PREFIX)/share/man/man1/$$prog.1; \
	done

uninstall:
	for prog in $(PROGRAMS); do \
		rm -f $(PREFIX)/bin/$$prog; \
		rm -f $(PREFIX)/man/man1/$$prog.1; \
	done
	rm -f $(PREFIX)/man/man1/gol.1

.PHONY: clean install uninstall
