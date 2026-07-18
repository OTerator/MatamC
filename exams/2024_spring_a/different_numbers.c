#include <stdlib.h>
#include <stdbool.h>

int* different_numbers(int* arr, unsigned int n) {
	// if (!arr || len<1) return NULL; we don't use stdio
	
	int* uniques = (int*) malloc(n*sizeof(int));
	uniques[0] = 1;
	
	if (n == 1 || arr[0] != arr[1]) {
		uniques[uniques[0]++] = arr[0];
	}
	
	bool isUnique=false;
	
	for (unsigned int i=1; i<n-1; i++) {	// n=0 -> [1] as loop won't execute.
		if (arr[i-1] != arr[i] && arr[i] != arr[i+1]) {
			uniques[uniques[0]++] = arr[i];
		}
	}
	
	if (n > 1 && arr[n-1] != arr[n-2]) {
		uniques[uniques[0]++] = arr[n-1];
	}
	
	uniques = (int*)realloc(uniques, uniques[0]*sizeof(int));	
	return uniques;
}


/*
	int len = 1;	// this int is there too, so we count from 1.
	for (unsigned int i=1; i<n; i++) {
		if (arr[i-1] != arr[i]) len++;
	}
	
	int* uniques = (int*) malloc(len*sizeof(int));
	*/