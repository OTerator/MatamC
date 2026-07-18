# Simple Makefile - lecture Date version
# Layout assumed:
#   src/DNASeq.h
#   src/DNASeq.c
#   test/TestDNASeq.c
#   unity/unity.c
#   unity/unity.h
#   unity/unity_internals.h

CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -g -O0 -Isrc -Iunity

TEST_BIN := build/test

SRC      := src/DNASeq.c
TEST_SRC := test/TestDNASeq.c unity/unity.c

.PHONY: all test run clean valgrind

all: $(TEST_BIN)

$(TEST_BIN): $(SRC) $(TEST_SRC) src/DNASeq.h unity/unity.h unity/unity_internals.h
	$(CC) $(CFLAGS) -o $@ $(SRC) $(TEST_SRC)

test: $(TEST_BIN)

run: $(TEST_BIN)
	./$(TEST_BIN)

valgrind: $(TEST_BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)