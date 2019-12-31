all: a.out

a.out: src/fileParsing.c src/roomHandling.c src/events.c src/main.c
	gcc src/fileParsing.c src/roomHandling.c src/events.c src/main.c -std=c99 -Wall -lncurses -Iinclude
