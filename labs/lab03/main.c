#include <stdio.h>

char my_toupper(char c) {

   if (c >= 'a' && c <= 'z') { 
      return c - ('a' - 'A');
   }
   return c;
}


int main() {
   unsigned int arr[26] = {0};
   char c;

   printf("Enter text: ");

   while ((c = getchar()) != '\n' && c != EOF) {
      c = my_toupper(c);
      if(c >= 'A' && c <= 'Z'){
         arr[c - 'A']++;
      }
   }
      
   for (int i=0; i<26; i++) { 
      printf("%c\t%d\n", 'A' + i, arr[i]);
   }



   return 0;
}

