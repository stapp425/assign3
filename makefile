CC = gcc

all: assign3

assign3: part1.c
	$(CC) part1.c -o part1

clean: rm part1 part1-output