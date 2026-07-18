CC			:= gcc
CFLAGS	:= -Wall -Werror -Wextra -Wpedantic -g -std=c99 -O0 -Isrc -Iunity


UNITY_HEADERS	:=  unity/unity.h unity/unity_internals.h
UNITY		:= unity/unity.c

LL_BIN	:=	build/test_LL 								#	where to drop
LL_HEADERS := src/LinkedList.h  						#	what to test
LL_SRC	:=	src/LinkedList.c 
TEST_LL	:=	test/test_LinkedList.c $(UNITY)		#	what to use

HT_BIN	:=	build/test_HT
HT_HEADERS := src/HashTable.h $(LL_HEADERS)
HT_SRC	:= src/HashTable.c $(LL_SRC)
TEST_HT	:= test/test_HashTable.c $(UNITY)

TEST_BIN := build/prog
HEADERS	:= src/misc.h $(HT_HEADERS) $(UNITY_HEADERS) 
SRC		:= src/main.c
MISC_O	:= build/misc.o


.PHONY: all clean valgrind run


all: testLL testHT prog


testLL: $(LL_BIN)
			./$(LL_BIN)

$(LL_BIN): $(LL_SRC) $(TEST_LL) $(LL_HEADERS) $(UNITY_HEADERS)
		$(CC) $(CFLAGS) -o $(LL_BIN) $(LL_SRC) $(TEST_LL)


testHT: $(HT_BIN)
			./$(HT_BIN)

$(HT_BIN): $(HT_SRC) $(TEST_HT) $(HT_HEADERS) $(UNITY_HEADERS)
		$(CC) $(CFLAGS) -o $(HT_BIN) $(HT_SRC) $(TEST_HT)


prog: $(TEST_BIN)

$(TEST_BIN): $(SRC) $(HT_SRC) $(MISC_O) $(HEADERS)
		$(CC) $(CFLAGS) -o $(TEST_BIN) $(SRC) $(HT_SRC) $(MISC_O)
		



clean:
		rm -f $(LL_BIN) $(HT_BIN) $(TEST_BIN)
		
#clean: rm -rf build/tests