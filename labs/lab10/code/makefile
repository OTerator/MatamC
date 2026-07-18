# Define compiler flags
CC = gcc
CFLAGS = -Wall -Werror -g -std=c99

# Main Program
prog: main.o BST.o
	$(CC) $(CFLAGS) -o prog main.o BST.o

main.o: main.c BST.h
	$(CC) $(CFLAGS) -c main.c

BST.o: BST.c BST.h 
	$(CC) $(CFLAGS) -c BST.c

# Test Suite (Task 5)
tests: test_BST.o BST.o unity.o
	$(CC) $(CFLAGS) -o tests test_BST.o BST.o unity.o
	./tests

test_BST.o: test_BST.c BST.h unity.h
	$(CC) $(CFLAGS) -c test_BST.c

unity.o: unity.c unity.h unity_internals.h
	$(CC) $(CFLAGS) -c unity.c

# Clean
clean:
	rm -f *.o prog tests