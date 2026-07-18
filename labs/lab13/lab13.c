#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**   1.
 * I chose to implement this with an arr for simplicity (which was still challenging enough for me to be honest),
 * and examined it is also possible with a Linked List, or for better searching: with a Binary Tree.
*/
void find_unique(const char* file_name) {

   unsigned int nums_size = 32; //arbitrary choice of size, realloc later if needed.
   unsigned int* nums = (unsigned int*)malloc(nums_size*sizeof(unsigned int));
   unsigned int num_count = 0; // count of nums in arr.

   FILE* fp = fopen(file_name, "r");
   if (!fp) 
      return;

   unsigned int curr;
   while (fscanf(fp, "%u", &curr) != EOF) {  // EOF = -1;

      bool exists = false;

      for (unsigned int i = 0; i < num_count; i++) {
         if (nums[i] == curr) {
            exists = true;
            break;
         }
      }

      if (!exists) {

         if (nums_size <= num_count) {
            nums_size <<= 1;   // *=2
            nums = (unsigned int*)realloc(nums, nums_size*sizeof(unsigned int));
         }

         nums[num_count++] = curr;
         printf("%u\n", curr);
      }
   }

   free(nums);
   fclose(fp);
}

/**   2.
 * Helper function for reverse_fours.
 * recieves two pointers and swaps each four accordingly: (1001,0110; 1010,0010) → (0010,1010; 0110,1001).
 * for a certain n=n from reverse_fours --> j = n-i: pointers are closing in towards the middle until 
 */
void fours_swap(unsigned char* a_i, unsigned char* a_j) {
   //   let:  *a_i = abcdefgh , *a_j = stuvwxyz
   unsigned char mask = 15; //(1 << 4) - 1 = 00001111 = 15 = 0x0F
   unsigned char tempi = (*a_i & ~(mask)) >> 4;    // abcd0000 >> 4 → 0000abcd
   unsigned char tempj = (*a_j & mask) << 4;       // 0000wxyz << 4 → wxyz0000
   *a_i &= mask;     // 0000efgh
   *a_j &= ~mask;    // stuv0000
   *a_i |= tempj;    // wxyzefgh
   *a_j |= tempi;    // stuvabcd
   // first swap done.
   
   // The second swap won't execute if the last iteration is at the middle of an odd n-sized array.
   // hence: *a_i = *a_j = abcdwxyz → wxyzabcd is already job's done.
   if (a_i != a_j) {
      tempi = (*a_i & mask) << 4;      // 0000efgh << 4 → efgh0000
      tempj = (*a_j & ~(mask)) >> 4;   // stuv0000 >> 4 → 0000stuv
      *a_i &= ~mask;    // wxyz0000
      *a_j &= mask;     // 0000abcd
      *a_i |= tempj;    // wxyz,stuv
      *a_j |= tempi;    // efgh,abcd   done //
   }
}

void reverse_fours(unsigned char* arr, unsigned int n) {

   if (!arr || n < 1) return;

   unsigned char* a_n = (arr + n-1);

   for(; arr <= a_n; arr++, a_n--) {
      fours_swap(arr, a_n);
   }
}


/**   3.
 * 
 */



/*********************************************************/
// testing funcions for Q-2.
void print_bits(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i == 4) printf(" ");
    }
}
void print_array_bits(unsigned char* arr, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        print_bits(arr[i]);
        printf(i == n - 1 ? "" : "  ");
    }
    printf("\n");
}

int main() {
   
   // 1.
   // find_unique("sample.txt");

   
   // 2.
   // unsigned char test_arr[] = {0x9C, 0xF3, 0x0A};
   // unsigned int n = 3;

   // printf("Original bits:\n");
   // print_array_bits(test_arr, n);

   // reverse_fours(test_arr, n);

   // printf("\nReversed bits:\n");
   // print_array_bits(test_arr, n);

   // unsigned char test_even[] = {0xAB, 0xCD}; // [1010][1011] [1100][1101]
   // printf("\nTesting even length (2 bytes):\n");
   // print_array_bits(test_even, 2);
   // reverse_fours(test_even, 2);
   // print_array_bits(test_even, 2);


   // 3.
}