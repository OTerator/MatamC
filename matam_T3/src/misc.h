#ifndef MISC_H
#define MISC_H

#define MEM_ALLOCATION_ERROR 1

// Duplicate a string using malloc
char* strdup2(const char* s);

/******** Hash functions for unsigned int keys ********/
unsigned int hash1(void* v);
unsigned int hash2(void* v);
unsigned int hash3(void* v);

#endif