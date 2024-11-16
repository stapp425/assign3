CC = gcc

all: assign3

assign3: part1 part2

part1: part1.c
	$(CC) part1.c -o part1

part2: part2.c phypages.c phypages.h pagetable.c pagetable.h
	$(CC) part2.c phypages.c pagetable.c -o part2

clean: rm part1 part1-output