#include <stdio.h>
#include <stdbool.h>

bool is_prime(unsigned int num) {

   if (num == 1) {
      return false; // for num=1 no iterations will be made
   } else if (num == 2) {
      return true;
   }

   unsigned int i = 2;
   for (; i<num; i++) {
      if (num%i == 0) {
         return false;
      }
   }

   return true;
}


int main() {

   unsigned int num=0;
   printf("Enter a positive number: ");
   if (scanf("%u", &num) != 1) {
      printf("Error: input is not a non-negative number\n");
      return 1;
   }
   if (num<1 || num>2000000) {
      printf("Error: number must be between 1 to 2000000\n");
      return 2;
   }

   printf("%d\n", num);

   if (is_prime(num)) {
      printf("%u is a prime number", num);
   }
   else {
      printf("%u is not a prime number", num);
   }



   return 0;
}