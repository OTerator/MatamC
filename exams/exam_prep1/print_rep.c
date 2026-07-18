#include <stdio.h>

void print_rep(unsigned char* arr, unsigned int size) {
	
	unsigned char mask = 3; //0x03;
	
	for (unsigned int i = 0; i < size; i++) {
		unsigned char current = arr[i];
		
		for (unsigned int j = 0; j<4; j++) {
			printf("%u\n", current & mask);
			current >>= 2;
		}
	}
}

int main() {

	unsigned char arr[] = {135, 128};
	print_rep(arr, 2);

	return 0;
}