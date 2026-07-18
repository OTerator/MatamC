#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int count(const char* s, char c) {
   unsigned int counter = 0;

   while(*s != '\0') {
      
      if (*s == c) {
         counter++;
      }

      s++;
   }

   return counter;
}


unsigned int startswith(const char* s1, const char* s2) {

   while (*s2 != '\0' && *s1 != '\0') {
      
      if (*s2 != *s1) {
         return 0;
      }
      
      s2++;
      s1++;
   }
   
   return 1;  
}


unsigned int endswith(const char* s1, const char* s2) {
   
   int gap = strlen(s1) - strlen(s2);

   if (gap == 0) {
      return *s1 == *s2;
   }
   else if(gap < 0) {
      return 0;
   }
   else {
      s1+=gap;

      while (*s1 != '\0') {
         if (*s1 != *s2){
            return 0;
         }
         
         s1++;
         s2++;
      }
   }

   return 1;
}


int find(char* s1, char* s2) {
   
   int i = 0;

   while (*s1 != '\0') {

      if (startswith(s1, s2)) {
         return i;
      }
      s1++;
      i++;
   }

   return -1;
}


void flip(char* s) {
   char *left = s;
   char *right = s + strlen(s) - 1;

   while (left < right) {
      char temp = *left;
      *left = *right;
      *right = temp;

      left++;
      right--;
   }   
}


unsigned int getline(char **buff, unsigned int *buff_size, FILE* stream) {

   if (*buff == NULL) {
      *buff_size = 10;
      *buff = malloc(*buff_size);
      if (*buff == NULL) {
         printf("malloc failed to allocate memory.\n");
         return 0;
      }
   }
   
   unsigned int counter = 0;
   
   int ch;
   while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
      
      if(counter == *buff_size - 1) {
         *buff_size += 10;
         *buff = realloc(*buff, *buff_size);
         
         if (*buff == NULL) {
            printf("realloc failed to allocate memory.\n");
            return counter;
         }         
      }

      (*buff)[counter] = (char) ch;
      counter++;
   }

   if (ch == EOF && counter == 0)
      return 0;

   (*buff)[counter] = '\0';

   return counter;
}


int main() {
   char* buff = NULL;
   unsigned int buff_size = 0, n;

   for(int i=0; i<5; i++) {
      printf("Enter line %d: ", i);
      n = getline(&buff, &buff_size, stdin);
      printf("Read %u characters, buff_size=%u, line is\n%s\n", n, buff_size, buff);
   }

   free(buff);


   char s[] = "Hello World";
   char s1[] = "Hello";
   char s2[] = "World";
   char str[] = "HelloHello"; // Copies "HelloHello" into a modifiable array 'str'  

   printf("count('l' in \"%s\") = %d\n", s, count(s, 'l'));
   printf("count('o' in \"%s\") = %d\n", s, count(s, 'o'));
   printf("count('H' in \"%s\") = %d\n", s, count(s, 'H'));

   printf("startswith(\"%s\", \"%s\") = %d\n", s, s1, startswith(s, s1));
   printf("startswith(\"%s\", \"%s\") = %d\n", s, s2, startswith(s, s2));

   printf("endswith(\"%s\", \"%s\") = %d\n", s, s2, endswith(s, s2));
   printf("endswith(\"%s\", \"%s\") = %d\n", s, s1, endswith(s, s1));

   printf("find(\"%s\", \"%s\") = %d\n", s, "World", find(s, "World"));
   printf("find(\"%s\", \"%s\") = %d\n", s, "lo", find(s, "lo"));
   printf("find(\"%s\", \"%s\") = %d\n", s, "xyz", find(s, "xyz"));


   printf("Before flip: \"%s\"\n", str);
   flip(str);
   printf("After  flip: \"%s\"\n", str);
   
   return 0;
}