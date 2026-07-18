#include <stdbool.h>

bool is_periodic(int* arr, unsigned int n) {
   if (!arr || n<1) return false;
   if (n==1) return true;
   
   //	assume it is periodic
   unsigned int order = 1;
   unsigned int j = 0;
   for (order=1; order<n; order++) {
	   
	   for (j=0; j<=order; j++) {
		   if (arr[j] == arr[order]) break;
	   }
	   
	   if (j != order) break;	// unique sequence broken. (order++ won't occur for the end of this iteration).
   }
   
   // at this point we know what is the order of the sequence o(seq) = len(seq). 
   
   for (unsigned int i = 0; i<n; i++) {
	   if (arr[i] != arr[i%order]) return false;
   }
   
   if (order == n) return false;	/// questionable case... I think it should still be true.
   
   return true;
}

bool is_periodic(int* arr, unsigned int n) {
   if (!arr || n<1) return false;
   //if (n==1) return true;
   
   unsigned int order = -1;
   
   for (unsigned int i=1; i<n; i++) {
	   if (arr[i] == arr[0]) {
		   order = i;
		   break;
	   }
   }
   
   if (order == -1) return false;
   
   for (unsigned int i=order; i<n; i++) {
	   if (arr[i] != arr[i%order]) return false;
   }
   
   return true;
}