#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "misc.h"


void* cpyUnsInt(void* e) {
    unsigned int* newUnsignedInt = (unsigned int*)malloc(sizeof(unsigned int));
    if (!newUnsignedInt) {
        fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n\n", __FILE__, __LINE__, sizeof(unsigned int));
        exit(MEM_ALLOCATION_ERROR);
    }
    *newUnsignedInt = *(unsigned int*)e;
    return newUnsignedInt;
}

int cmpUnsInt(void* e1, void* e2) {
    // casting:
    unsigned int n1 = *(unsigned int*)e1;
    unsigned int n2 = *(unsigned int*)e2;
    
    if (n1 == n2) {
        return 0;
    }
    return n1 > n2 ? 1 : -1;
}


int main(int argc, char** argv) {
    if(argc != 5) {
        fprintf(stderr, "Usage: %s <hash_function_number> <bucket-array-size> <seed> <n>\n", argv[0]);
        fprintf(stderr, "  hash_function_number: 1, 2, or 3\n");
        fprintf(stderr, "  bucket-array-size: positive integer\n");
        fprintf(stderr, "  seed: positive integer\n");
        fprintf(stderr, "  n: number of random items to insert\n");
        return 2;
    }

    int hash_num = atoi(argv[1]);
    unsigned int bucket_size = (unsigned int)atoi(argv[2]);
    unsigned int seed = (unsigned int)atoi(argv[3]);
    unsigned int n = (unsigned int)atoi(argv[4]);


    unsigned int (*selected_hash)(void*);
    switch (hash_num) {
        case 1: selected_hash = hash1; break;
        case 2: selected_hash = hash2; break;
        case 3: selected_hash = hash3; break;
        default:
            fprintf(stderr, "Error: Invalid hash function number (must be 1, 2, or 3)\n");
            return 2;
    }

    srand(seed);

    HashTable ht = HTCreate(bucket_size, selected_hash, cmpUnsInt, cpyUnsInt, cpyUnsInt, free, free);
    if (!ht) {
        fprintf(stderr, "Failed to create HashTable.\n");
        exit(MEM_ALLOCATION_ERROR);
    }


    unsigned int key, value;
    for (unsigned int i = 0; i < n; i++) {
        key = (unsigned int)rand();
        value = (unsigned int)rand();

        HTInsert(ht, &key, &value);
    }

    printf("%u\n", HTSize(ht));

    HTDestroy(ht);

    return 0;
}


/* Ansewrs to questions:

    1. After running a few tests on the server, seems like hash2 is usually the best performer with results like:
        
            time ./prog 2 83044 64250 70644
            70642

            real    0m0.064s
            user    0m0.055s
            sys     0m0.003s

        while all other functions always take longer and particularily with this input, were unable to complete the run in under 8 seconds (!)


    2.  most definitely yes, the time it takes for the program to complete depends on the ratio between buckets:n when n is the number of random items we're inserting. 
        since we're using LinkedLists, if we only had 1 bucket, all items would have to go there which makes every navigation through the LL o(n) for having to visit each node 
        at the worst case. alternatively, if we have an extremely high amount of buckets it will take a hot while for each element to find its bucket after hashing, so after more testing
        it may be possible to conclude about where the sweet spot of the this ratio is at for different ranges of numbers.


    3.  The function with the fastest runtime should have the complexity closest to o(1) out of all three hash functions. therefore, such luxuary may come at a different
        cost like more memory that it requires for storing cretain values in a wait that allows quick access, etc. 

*/