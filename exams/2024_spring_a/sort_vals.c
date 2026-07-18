
void sort_vals(unsigned int* arr, unsigned int n) {
	
	// 200 * 8 = 1600 bits for 1600 possible unsigned integers (
	unsigned char helper[200] = {};
	unsigned int i, j;
	
	for (i=0; i<n; i++) {
		helper[arr[i]/8] |= 1 << (arr[i] % 8);	// 7 6 5 4 3 2 1 0, 15 14 13...9 8,...
	}
	
	for (i=0, j=0; i<1600; i++) {
		if (helper[i/8] & (1 << i%8)) arr[j++] = i;
	}
}