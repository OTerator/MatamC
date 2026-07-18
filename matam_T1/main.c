#include <stdio.h>
#include <stdlib.h>
#define     ASCII_TABLE_SIZE  256



// 1
void swap(int* p1, int* p2) {
   int temp = *p1;
   *p1 = *p2;
   *p2 = temp;
}


// 2
void arrange3(int* pa, int* pb, int* pc) {

   if (*pa > *pb) {     // will send all values to: G = {a<b<c, a<c<b, c<a<b} , narrowing the problem to less options.
      swap(pa, pb);
   }

   if (*pa > *pc) {     // sending values from G to H = {a<b<c, a<c<b} , narrowing down the problem
      swap(pa, pc);     //    ( ועל אל המקרה הרצוי)   
   }
   
   if (*pb > *pc) {     // sending the two remaining values from H to just: {a<b<c}, thus we always get our desired order.
      swap(pb, pc);
   }

}


// 3
void cycle1(int arr[], unsigned int size) {

   if (arr == NULL) {
      printf("Error in function %s, aborting\n", __func__);
      exit(1);
   }

   for (unsigned int i = size-1; i>0; i--) {    
      swap(&arr[i], &arr[i-1]);
   }
}


// 4
void cyclen(int* arr, unsigned int size, unsigned int n) {

   if (size <= 0 || arr == NULL) {
      printf("Error in function %s, aborting\n", __func__);
      exit(1);
   }

   int temp[size];

   for (unsigned int i = 0; i < size; i++) {
      *(temp + (i + n)%size) = *(arr + i);
   }

   for (unsigned int i = 0; i < size; i++) {
      *(arr+i) = *(temp+i);
   } 
}


// // 5
void sortp(int arr[], unsigned int n) {

   if (arr == NULL) {
      printf("Error in function %s, aborting\n", __func__);
      exit(1);
   }


   for (int* i = &arr[n-1]; i > &arr[0]; --i) {    // pointer running down from [n-1] to [0]. determines the size of the inner frame and its last position.
      
      int* max = i;    // pointer to the greatest int value in the array; its value is determined iterating through the inner frame.

      for (int* p = i; p >= &arr[0]; --p) {   // p-pointer running down through this currently i-sized frame from pointer i to 0;
         max = (*p > *max) ? p : max;         // recieves the address of the pointer to the greatest value in the array 
         // printf("%d > %d\t", *p, *i);      // bakara
         // printf("max = %d\n", *max);
      }
      
      swap(i, max);     // moving the pointer of our max int to the end of the array, swapped with its previous value.
      // for (unsigned int i = 0; i<10; i++) { printf("%d", arr[i]); if (i<9) { printf(", "); } } printf("\n");  // testing
   }
}


// 6
unsigned int longest_unique_substr() {

   char c;
   unsigned int frame = 0;    // size of the current frame
   unsigned int maxFrame = 0; // highest record, returned. if no iterations were made, 0 is returned for an empty string.
   unsigned int start = 1;
   unsigned int current = 1;
   unsigned int tracker[ASCII_TABLE_SIZE] = {};   // will track the position of each char in the string, (its ascii is the array index).
   
   // printf("Enter chars: \n");
   while ((c = getchar()) != '\n' && c != EOF) {}  // apparently the buffer already has '\n' or EOF from scanf at main, therefor we must discard it somehow...
   while ((c = getchar()) != '\n' && c != EOF) {

      frame++;         // and expanding the frame accordingy.
      
      if (tracker[c] != 0) {      // char already in frame
         start = tracker[c];       // update new starting position
         frame = current - start;    // discard all previous positions from start to the repeated char.
         tracker[c] = current;      // will the previous frame-discarded position
         for (unsigned int i = 0; i<ASCII_TABLE_SIZE; i++) {
            if (tracker[i] < start) {   // reset values outside frame.
               tracker[i] = 0;
            }
         }
      }

      tracker[c] = current;      // will override 0 (or the previous frame-discarded position)
      
      if (frame > maxFrame) {
         maxFrame = frame;
      }
      
      current++;       // moving to the next char...
   }
   return maxFrame;
}


// 7
void stack_organization(char a, short b, int c, size_t d) {
   int arr[10];
   double e = 5;
   
   size_t stack_frame = (char*)&e > (char*)&a   ?   (char*)&e - (char*)&a   :   (char*)&a - (char*)&e;

   printf("Stack frame size for stack_organization:\t %ld\n", stack_frame);
   printf("a\t char\t %d\t %p\t %d\t %c\n", sizeof(char), &a, (char*)&a-(char*)__builtin_frame_address(0), a);
   printf("b\t short\t %d\t %p\t %d\t %hd\n", sizeof(short), &b, (char*)&b-(char*)__builtin_frame_address(0), b);
   printf("c\t int\t %d\t %p\t %d\t %d\n", sizeof(int), &c, (char*)&c-(char*)__builtin_frame_address(0), c);
   printf("d\t size_t\t %d\t %p\t %d\t %zu\n", sizeof(size_t), &d, (char*)&d-(char*)__builtin_frame_address(0), d);

   printf("e\t double\t %d\t %p\t %d\t %f\n", sizeof(double), &e, (char*)&e - (char*)__builtin_frame_address(0), e);
   printf("arr\t int[10] %d\t %p\t %d\t ", sizeof(arr), &arr, (char*)arr - (char*)__builtin_frame_address(0));
   printf("{");
   for (unsigned int i = 0; i<10; i++) {
         printf("%d", arr[i]);
         if (i<9) {
            printf(", ");
         }
      }
   printf("}\n");
   

   //assume arr
   // printf("e\t double\t %d\t %p\t %d\t %f", sizeof(int), &d, huh, d);

}




int main() {

   // 1
   printf("Enter your choice between 1 to 6: ");
   // 2
   unsigned int choice;
   if (scanf("%u", &choice) != 1) {
      printf("Error in function %s, aborting\n", __func__);
      exit(1);
   } else if (choice < 1 || choice > 6) {
      printf("Error in function %s, aborting\n", __func__);
      exit(1);
   }

   // 3
   if (choice >= 1 && choice <= 4) {
      unsigned int seed;
      printf("Enter seed: ");
      if (scanf("%u", &seed) != 1) {
         printf("\nFatal error occurred\n");
         printf("Error in function %s, aborting\n", __func__);
         exit(1);
      }
      srand(seed);
   }

   // 4
   if (choice == 1) {
      
      int a = rand();
      int b = rand();
      int c = rand();

      printf("a=%u, b=%u, c=%u\n", a, b, c);
      arrange3(&a, &b, &c);
      printf("a=%u, b=%u, c=%u\n", a, b, c);
   }

   // 5
   if (choice >= 2 && choice <= 4) {
      int arr[10]; // = {9,3,8,5,9,2,0,3,5,4};
      for (unsigned int j = 0; j < 10; j++) {   // filling up the array with numbers ranging between 1-100.
         arr[j] = (rand()%99) + 1;       //  0-99  ===>  1-100 ;
      }

      for (unsigned int i = 0; i<10; i++) {
         printf("%d", arr[i]);
         if (i<9) {
            printf(", ");
         }
      }
      printf("\n");

      // (choices 2, 3, 4):
      if (choice == 2) {
         cycle1(arr, 10);
      } else 
      if (choice == 3) {
         cyclen(arr, 10, arr[0]);  // cyclen(arr, 10, 3);
      } else {   // choice = 4;
         sortp(arr, 10);
      }

      for (unsigned int i = 0; i<10; i++) {
         printf("%d", arr[i]);
         if (i<9) {
            printf(", ");
         }
      }
      printf("\n");
   }


   // 6
   if (choice == 5) {
      unsigned int len = longest_unique_substr();
      printf("The longest non-repeating sequence of characters is %u\n", len);
   }

   // 7
   if (choice == 6) {
      stack_organization('1', 2, 3, 4);
   }

   return 0;
}                    