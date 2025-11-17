CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -Llib -lSDL2main -lSDL2 

SRC = main.c
OUT = game.exe

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(LDFLAGS)