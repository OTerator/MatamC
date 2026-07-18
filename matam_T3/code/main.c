#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "misc.h"

int main(int argc, char** argv) {
    if(argc != 5) {
        fprintf(stderr, "Usage: %s <hash_function_number> <bucket-array-size> <seed> <n>\n", argv[0]);
        fprintf(stderr, "  hash_function_number: 1, 2, or 3\n");
        fprintf(stderr, "  bucket-array-size: positive integer\n");
        fprintf(stderr, "  seed: positive integer\n");
        fprintf(stderr, "  n: number of random items to insert\n");
        return 2;
    }

    return 0;
}
