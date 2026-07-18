prog: main.o LinkedList.o
		gcc -Wall -Werror -g -std=c99 -o prog main.o LinkedList.o

main.o: main.c LinkedList.h
		gcc -c main.c

LinkedList.o: LinkedList.c LinkedList.h
		gcc -c LinkedList.c