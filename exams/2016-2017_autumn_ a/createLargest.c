
unsigned int createLargest(unsigned int n) {
	int i, ones=0, res = 0;
	for (i = 8*sizeof(n) -1; i>=0; i--) {
		one += ((n & (1 << i)) != 0);
	}
	
	for (i=0; i<ones-1; i++) {
		res |= (1 << 31-i);
	}
	
	res |= 1;
	return res;
}