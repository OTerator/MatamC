#include <stdio.h>


int main() {

   printf("\nSize testing printer:\n");
   
   printf("unsigned char: %u bytes, %u bits\n", sizeof(unsigned char), 8*sizeof(unsigned char));
   printf("unsigned int: %u bytes, %u bits\n", sizeof(unsigned int), 8*sizeof(unsigned int));
   printf("size_t: %u bytes, %u bits\n\n", sizeof(size_t), 8*sizeof(size_t));
   
   printf("idea: each letter takes just 2 bits, so if we know the length of the sequence we can calculate the amount of bits/bytes needed like the following:\n");
   printf("number of bits needed: unsigned int num_bits = seqlen*2 ; because each letter needs to get 2 bits.\n");
   printf("now transfer that into bytes: 8 bits are 1 byte, therefore num_bits = num_bytes*8 so we divide by 8:\n");
   printf("unsigned int num_bytes = num_bits/8;\n");
   printf("finally, we can use that information to dynamically allocate the exact amount of bytes needed with malloc:\n");
   printf("unsigned char* mySeq = (unsigned char*)malloc(num_bytes);\n");
   


   return 0;
}