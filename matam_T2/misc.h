#ifndef MISC_H
#define MISC_H
#include <stdio.h>
/*
    Exit error codes and messages (always printed to stderr):
    1   Failed to open file for reading     "Error in %s: failed to open file %s for reading, aborting\n", __func__, file_path
    2   Failed to open file for writing     "Error in %s: failed to open file %s for writing, aborting\n", __func__, file_path
    3   Failed to allocate memory           "Error in %s: failed to allocate %lu bytes, aborting\n", __func__, number-of-bytes-allocated
    4   NULL pointer received when otherwise expected       "Error in %s: NULL pointer found, aborting\n", __func__
    5   Failed to read a line from file_path using getline  "Error in %s: failed to read a line from %s using getline, aborting\n", __func__, file_path
    6   Corrupted file      "Error in %s: file %s is corrupted\n", __func__, file_path
    7   Library directory does not exist    "Error in %s: failed to open directory %s, aborting\n", __func__, directory_path 
    8   Wrong arguments     Proper usage message from main.c
*/


/* This function creates a new copy of s. If it fails for any reason it returns NULL */
char *strdup(const char *s);

/* Reads a line from stream, stores it in *lineptr. This buffer is dynamically allocated, its size is kept in *n.
    If the function fails for any reason (e.g., reached the end of file) it returns -1 */
size_t my_getline(char **lineptr, size_t *n, FILE *stream);

/* Takes a path of a directory and a pointer to an array of strings (which is assumed to be NULL when passed).
    Fills files with the complete paths of all the files in dir_path that end with .txt. Returns the size of files.
    Generates the proper error messages and exits with the proper error code if an error occurs  */
unsigned int glob_txt_files(const char *dir_path, char** files[]);

// ********* //
// My miscs:

/* recieves an element and checks wether it recieved an address - which means memory was successfully allocated, or is null. if null, exits the program saftely.*/
void alloc_tester(void* memory_element, size_t size, const char* foo);

/* recieves the return value of my_getline and tests wether it run successfully and if it didn't (returned -1) exits the program safetly. */
void getline_tester(size_t line, const char* file_path, const char* foo);

// ********* //


#endif