CFLAGS=-O2 -Wall -Wextra -lX11 -lpci
PREFIX=$(HOME)/.local

all: stupidbar

stupidbar: stupidbar.c
	$(CC) stupidbar.c -o stupidbar $(CFLAGS)
	strip stupidbar

install: stupidbar
	mkdir -p $(PREFIX)/bin
	install ./stupidbar $(PREFIX)/bin/stupidbar
