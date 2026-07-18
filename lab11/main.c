#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//#define  MAX_UNS_CHAR   256            // 2^ 1*8 = 2^8
//#define  MAX_UNS_INT    4294967296     // 2^ 4*8 = 2^32

/* 1. 
   true if bit at index is 1 else false.
   */ 
bool check_bit(unsigned int n, unsigned int index) { 
   // printf("%u & %u\t", n, index);
   return (n & (1 << index)) != 0;
}

/* 2. 
   turns off a bit at a given index.
   11010110, 3 ->  11010010 = n & 11111011 = n & ~(1 << index)
*/ 
unsigned int turnoff_bit(unsigned int n, unsigned int index) {
   return n & ~(1 << index);
}


/* 3. 
   counts 1's in the binary form.
   10001110 -> 10001110 & 
   00100110 >> 00010011 >>= 00001001 >>= ...
                  0           1  ... 
*/
unsigned int turnedon_bits(unsigned int n) {
   unsigned int count = 0;
   for (; n > 0; n >>= 1) {
      if (n & 1 == 1) {
         count++;
      }
   }
   return count;
}


/* 4. 
   74 -> 0b01001010;
*/ 
void print_bits(unsigned char n) {
   //printf("%08b\n", n); // nice but cheating. bonus: %o - octal, %x - hex.
   for (unsigned int i = 8; i > 0; i--) {
      printf("%u", check_bit(n, i-1));
   }
   printf("\n");
}


/* 5. 
*/ 
unsigned char reverse_bits(unsigned char n) {
   unsigned char r = 0;  // result
   unsigned char c;  // carry
   // while (n > 0) {
   for (unsigned char    i = 0; i < 8; i++) {
      c = (n & 1);
      r += c;
      if (i==7) {break;}

      n >>= 1;
      r <<= 1;
   }

   return r;
}


/* 6. 
*/ 
unsigned int num_with_bits(unsigned int indexes[], unsigned int n) {
   
   unsigned int c = 0;
   while (n > 0) {
      c |= 1 << indexes[n-1];
      n--;
   }

   return c;
}


/* 7. 
   true if n is negative else false.
*/ 
bool is_negative(int n) {
   return (n & (1 << 31)) != 0; // 8*sizeof(int); bits. (-1 to pause before ovf). (10000....0)
}


/* 8. 
   true if n is even else false
*/ 
bool is_even(unsigned int n)  {
   return (n & 1) == 0;
}

/* 9. 
*/ 
int main() {

   // printf("\n");

   srand(1913);

   unsigned int choice;
   scanf("%u", &choice);
   
   switch (choice) {
   case 1:
      unsigned int n = rand();
      unsigned int index = rand() % 32;
      printf("%x\n", check_bit(n, index));
      break;
   
   case 2:
      unsigned int n2 = rand();
      unsigned int index2 = rand() % 32;
      printf("%x\n", turnoff_bit(n2, index2));
      // printf("%x\n", turnoff_bit(rand(), rand()%32));
      break;
   
   case 3:
      printf("%x\n", turnedon_bits(rand()));
      break;
   
   case 4:
      print_bits(rand()%256);
      break;
   
   case 5:
      printf("%x\n", reverse_bits(rand()%256));
      break;
   
   case 6:
      unsigned int arr[4];
      for (int i = 0; i < 4; i++) {
         arr[i] = rand() % 32;
      }
      printf("%x\n", num_with_bits(arr, 4));
      break;
   
   case 7:
      printf("%x\n", is_negative(rand()));
      break;
   
   case 8:
      printf("%x\n", is_even(rand()));
      break;
   
   default:
      break;
   }

   // unsigned char c = 5;
   // printf("%u\n", check_bit(5, 2));
   // printf("%u, ", c);
   // print_bits(c); // 00000101 
   // printf("%u\n", (5&128) != 0);
   // printf("%u\n", (5&64) != 0);
   // printf("%u\n", (5&32) != 0);
   // printf("%u\n", (5&16) != 0);
   // printf("%u\n", (5&8) != 0);
   // printf("%u\n", (5&4) != 0);
   // printf("%u\n", (5&2) != 0);
   // printf("%u\n", (5&1) != 0);

   // 3.
   // print_bits(turnoff_bit(c, 0)); //   assert 4 
   // print_bits(turnoff_bit(c, 2)); //   assert 1
   
   // 4.
   // printf("%u", turnedon_bits(c));  // asserrt 2
   // print_bits(c);

   // 5.
   // unsigned char d = reverse_bits(c);
   // printf("%u, ", d);
   // print_bits(d);

   // 6.
   // unsigned int n = 4;
   // unsigned int arr[5] = {1, 7, 3, 0};
   // print_bits(num_with_bits(arr, n));

   // 7.
   // printf("%d", is_negative(0));
   // printf("%d", is_negative(5));
   // printf("%d", is_negative(-9));
   
   // 8.
   // printf("%d", is_even(9));
   // printf("%d", is_even(484847621));
   // printf("%d", is_even(0));
   // printf("%d", is_even(173197352));


   return 0;
}