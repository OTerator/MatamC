
#include <stdio.h>

int main() {
   
   int input;
   printf("Enter a number: ");
   if (scanf("%da", &input) != 1 || input < 0) {
      printf("Error, wrong input!\n");
      return 1;
   }
   printf("%d\n", input);

   int original = input;

   int lastDigit = input % 10;
   int palindrome = lastDigit;
   
   while(input >= 10) {
      input = input/10;
      lastDigit = input % 10;
      palindrome *= 10;
      palindrome += lastDigit;
   }

   if(original == palindrome) {
      printf("%d is a palindrome\n", original);
   } else {
      printf("%d is not a palindrome.\n", original);
   }

   return 0;
}