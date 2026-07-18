#include "misc.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>


/* This function creates a new copy of s. If it fails for any reason it returns NULL 
 */
char *strdup(const char *s) {    // will require: alloc_tester() + free() after use
   if (s == NULL) {
      return NULL;
   }

   size_t len = strlen(s) + 1;   // +1 for '/0'
   char *new_s = (char*)malloc(len);

   if (new_s == NULL) {
      return NULL;
   }

   memcpy(new_s, s, len);
   return new_s;
}


/* Reads a line from stream, stores it in *lineptr. This buffer is dynamically allocated, its size is kept in *n.
 * If the function fails for any reason (e.g., reached the end of file) it returns -1 
 */
/* * Custom getline implementation.
 * Reads a line from stream into *lineptr. Resizes if necessary.
 * Returns -1 (casted to size_t) on failure.
 */
size_t my_getline(char **lineptr, size_t *n, FILE *stream) {
   if (lineptr == NULL || n == NULL || stream == NULL) {
      return (size_t) -1;     // failure
   }

   if (*lineptr == NULL) {
      *n = 128;
      *lineptr = (char*)malloc(*n);
      if (lineptr == NULL) {
         return (size_t) -1;     // failure of memory allocation
      }
   }

   size_t pos = 0;
   int c;
   while (1) {
      c = fgetc(stream);

      if (c == EOF) {   // End of File
         if (pos == 0) {
            return (size_t) -1;     // failure of reading a line.
         }
         break;  
      }


      if (pos + 1 >= *n) {
         size_t new_size = *n * 2;
         char *new_ptr = realloc(*lineptr, new_size);

         if (new_ptr == NULL) {
            return (size_t) -1;
         }

         *lineptr = new_ptr;
         *n = new_size;
      }

      (*lineptr)[pos++] = (char)c;  // appeding the current char into the buffer, then increment pos by 1 for the next char (or '\0')
      
      if (c == '\n') {  // End of Line
         break;
      }
   }

   (*lineptr)[pos] = '\0';    // end of the string, will come after \n unless its already EOF.
   return pos;    // essentially str length (without '\0').
}



/* Takes a path of a directory and a pointer to an array of strings (which is assumed to be NULL when passed).
 * Fills files with the complete paths of all the files in dir_path that end with .txt. Returns the size of files.
 * Generates the proper error messages and exits with the proper error code if an error occurs
 */ 
/* Summary:
 * -Scans a directory for .txt files.
 * -Populates files with full paths.
 * -Exits with specific error codes on failure.
 */
unsigned int glob_txt_files(const char *dir_path, char** files[]) {

   if (dir_path == NULL) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
      exit(4);
   }

   DIR *d = opendir(dir_path);
   if (d == NULL) {
      fprintf(stderr, "Error in %s: failed to open directory %s, aborting\n", __func__, dir_path);
      exit(7);
   }

   struct dirent *entry;
   unsigned int count = 0;
   size_t capacity = 10;

   *files = (char**)malloc(capacity * sizeof(char *));    // so initially that'd be 10 * 8 = 80 bytes, and later if we * 2 for more memory (to store pointers) that is sets of 2^n * 80 in bytes and now n = 0.
   if (*files == NULL) {
      fprintf(stderr, "Error in %s: failed to allocate %lu bytes, aborting\n",
          __func__, capacity * sizeof(char*));
      exit(3);
   }

   while ((entry = readdir(d)) != NULL) {

      // checking if file is .txt, otherwise skip:  ||  I'm surprised that it didn't just test for the opposite and break; instead of nesting like this but ig we'll just take it.
      size_t name_len = strlen(entry->d_name);
      if (name_len > 4 && strcmp(entry->d_name + name_len - 4, ".txt") == 0) {

         if (count >= capacity) {   // arr resize
            // Multiply by 2 rule-of-thumb with realloc;
            while (count >= capacity) {
               capacity *=2;
            }

            char **temp = (char**)realloc(*files, capacity * sizeof(char*));
            if (temp == NULL) {
               fprintf(stderr, "Error in %s: failed to allocate %lu bytes, aborting\n", 
                  __func__, capacity * sizeof(char *));
               exit(3);
            }
            *files = temp;
         }

         // path construction:
         size_t path_len = strlen(dir_path) + 1 + name_len + 1;   // AI says: +1 for slash, +1 for null  
         char *full_path = (char*)malloc(path_len);                                            //   ↑   * check what is being refered to by null ? *
         if (full_path == NULL) {
            fprintf(stderr, "Error in %s: failed to allocate %lu bytes, aborting\n", __func__, path_len);
            exit(3);
         }

         /* Handle slash logic */
         if (dir_path[strlen(dir_path) - 1] == '/') {
            snprintf(full_path, path_len, "%s%s", dir_path, entry->d_name);
         } else {
            snprintf(full_path, path_len, "%s/%s", dir_path, entry->d_name);
         }

         (*files)[count] = full_path;
         count++;
      }
   }

   closedir(d);
   return count;
}


// ********* //
// My miscs:

void alloc_tester(void* memory_element, size_t size, const char* foo) {
   if (!memory_element) {
      fprintf(stderr, "Error in %s: failed to allocate %lu bytes, aborting\n", foo, size);
      exit(3);
   }
}

void getline_tester(size_t line, const char* file_path, const char* foo) {    // if getline returns -1, we assume the file is corrupt.
   if (line == (size_t)(-1)) {    // casting -1 to unsigned (size_t) by the 2's complement method therefore it'll be: 1111111...1 (base 2)
      fprintf(stderr, "Error in %s: failed to read a line from %s using getline, aborting\n", foo, file_path);
      exit(5);
   }
}

// ********* //