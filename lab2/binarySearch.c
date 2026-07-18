#include <stdio.h>
#include <stdbool.h>

int main() {

   int myArray[] = {1,6,3,25,87,3,0,1114,2};
   bool myBool = binarySearch(myArray, 10, 87);

   if(myBool == true) {
      printf("true");
   } else {
      printf("false");
   }

   return 0;
}


bool binarySearch(int* arr, int size, int num) {
   
   int bottom=0, top=size-1;
   while(top >= bottom) {
      int middle = (top+bottom)/2;
      if(arr[middle] == num) {
         return true;
      }
      else if(arr[middle] > num) {
         top = middle-1;
      }
      else {
         bottom = middle+1;
      }

      return false;
   }

}