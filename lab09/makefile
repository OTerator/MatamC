prog:	main.o Graph.o
			gcc -Wall -Werror -g -std=c99 -o prog main.o Graph.o

main.o:	main.c Graph.h
			gcc -c main.c

Graph.o: Graph.c Graph.h
			gcc -c Graph.c