CC=gcc
CFLAGS=-O3 -ansi -Wall -Wextra
FILES=SpaceInvaders.c alien_lista.c moveimprime.c
LIBS=-lncurses

SpaceInvaders: SpaceInvaders.c alien_lista.c alien_lista.h moveimprime.c moveimprime.h
	clear
	$(CC) $(CFLAGS) -o SpaceInvaders $(FILES) $(LIBS)

run: SpaceInvaders
	./SpaceInvaders
