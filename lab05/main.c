#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void wc(const char* path) {

   char c;
   FILE* fp = fopen(path, "r");

   unsigned int lines = 0;
   unsigned int words = 0;
   unsigned int chars = 0;

   while((c = fgetc(fp)) != EOF) {

      if (c == '\n') {
         lines++;
      }

      if (c == ' ' || c == '\t' || c == '\n') {
         words++;
      }

      chars++;
   }

   fclose(fp); 


   printf("%u\t %u\t %u\n", lines, words, chars);

}


void head(const char* pathIn, const char* pathOut, int n) {

   char c;
   unsigned int line = 0;

   FILE* fp1 = fopen(pathIn, "r");
   FILE* fp2 = fopen(pathOut, "w");
   

   while ((c = fgetc(fp1)) != EOF) {

      if (line == n) {
         break;
      }

      fputc(c, fp2);

      if (c == '\n')
         line++;
   }
}



void letter_histogram(const char* path) {

   unsigned int arr[26] = {};
   char c;

   FILE* fp = fopen(path, "r");

   while((c = fgetc(fp)) != EOF) {

      if (isalpha(c)) {
         c = toupper(c);
         arr[c - 'A']++;
      }
   }

   fclose(fp);

   for (int i = 0; i < 26; i++) {
      printf("%c\t %d\n", 'a'+i, arr[i]);
   }

}



int main(int argc, const char* argv[]) {

   
   if (argc != 3 && argc != 5) {
      fprintf(stderr, "Usage: %s <function index> <file-name>\n", argv[0]);
      return 1;
   }


   if (strcmp(argv[1], "1") == 0) {
      if (argc != 3) {
         fprintf(stderr, "Usage: %s <1> <file-name>\n", argv[0]);
         return 1;
      }
      wc(argv[2]);
   } else
   if (strcmp(argv[1], "2") == 0) {
      if (argc != 5) {
         fprintf(stderr, "Usage: %s <2> <infile> [<outfile>] <lines>\n", argv[0]);
         return 1;
      }
      head(argv[2], argv[3], atoi(argv[4]));
      // printf("%d, %s, %c", argv[4], argv[4], argv[4]);

   } else
   if (strcmp(argv[1], "3") == 0) {
      if (argc != 3) {
         fprintf(stderr, "Usage: %s <3> <file-name>\n", argv[0]);
         return 1;
      }
      letter_histogram(argv[2]);
   } else {
      fprintf(stderr, "Error: wrong program %s, aborting. 1-wc, 2-head, 3-letter_histogram.\n", argv[1]);
   }
   
   
   // wc("Roxanne.txt");
   // head("Roxanne.txt", "Roxanne.out.txt", 10);
   // letter_histogram("Roxanne.txt");
   
   
   
   return 0;
}