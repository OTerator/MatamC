#include <stdio.h>

void printBits(unsigned int n) {
	
	for (int i=31; i>=0; i--) {
		unsigned int curr = (n >> i) & 1;
		printf("%u", curr);
	}
}

void printBits(unsigned int n) {
	int i;
	for(i=8*sizeof(n)-1; i>=0; i--) {
		putchar((n & (1 << i))? ‘1’ : ‘0’);
	}
}
