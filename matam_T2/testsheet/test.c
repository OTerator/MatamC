#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>


char *strdup(const char *s) {    // will require: alloc_tester() + free() after use
   if (s == NULL) {
      return NULL;
   }

   size_t len = strlen(s) + 1;   // +1 for '/0'
   char *new_s = (char*)malloc(len);

   if (new_s == NULL) {
      return NULL;
   }

   memccpy(new_s, s, len, len);
   return new_s;
}


size_t my_getline(char **lineptr, size_t *n, FILE *stream) {

   printf("hi from getline");

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


int main() {

   printf("hi from main");

   FILE *song_file = fopen("dontwanttospoiltheparty.txt", "r");

   char* buffer = NULL;
   size_t buffer_size = 0;
   
   size_t first_size = my_getline(&buffer, &buffer_size, song_file);

   if (first_size > 0 && buffer[first_size - 1] == '\n') {    //   for a non empty first line, we replace '\n' with '\0' for a clean string 
      buffer[first_size - 1] = '\0';     //  example: "Here Comes The Sun\n" → "Here Comes The Sun" .
   }

   char* sName = strdup(buffer);
   printf("%s", sName);

   
   fclose(song_file);
   free(buffer);
   free(sName);

   return 0;
}
