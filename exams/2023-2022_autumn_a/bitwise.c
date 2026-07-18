
unsigned int count_ones(unsigned int n) {
	
	unsigned int count = 0;
	
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	
	return count;
}


unsigned int create_largest(unsigned int n) {
	
	unsigned int ones = count_ones(n);
	
	if (!ones) return 0;
	if (ones==1) return 1;
	
	// sizeof(unsigned int)*8 + 1 = 33
	// (32-(ones-1)) = 33-ones : -1 to keep one bit, 32 moves to push the rest.
	unsigned int kuku = 1 << (33-ones);	// 00...001000.....0
	kuku--;	// 00..000111...111
	kuku = ~kuku;	// 11...111000...000
	kuku |= 1;		// 11...111000...001 done
	
	return kuku;
}


void turn_on_bits(unsigned char* arr, unsigned int pos, unsigned int n) {
	if (!arr || n==0) return;
	
	bool atPos = false
	// i count bits, while j is a modular count.
	for (unsigned int i=0; *arr; arr++) {
		for (unsigned int j=0; j<8; i++, j++) {
			if (i==pos) atPos = true;
			if (atPos) {
				*arr |= (1 << j);
				atPos = (--n) ? true : false;
			}
		}
	}
}


void turn_on_bits(unsigned char* arr, unsigned int pos, unsigned int n) {
	
	unsigned int byte = pos/8;
	unsigned int bit = pos%8;
	
	for (; n>0; n--) {
		arr[byte] << (1 << bit);
		bit++;
		if (bit == 8) {
			bit++;
			byte=0;
		}
	}
}


