#include <stdio.h>

int main() {

   char myString[] = "myString";
   printf("%d", myStrlen(myString));

   return 0;
}

int myStrlen(const char* str) {

   int n=0;
   for (; str[n]!= '\0'; n++);

   return n;
}