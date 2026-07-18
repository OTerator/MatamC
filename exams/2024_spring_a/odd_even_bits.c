

// bad!
void odd_even_bits(unsigned int num) {
	
	unsigned int even=0, odd=0;
	unsigned int mask = 0x55555555	// 010101010101....01010101 is evens. 32/4 = 8 -> 
	
	even = num & mask;
	odd = num & (~mask);
	
	printf("%u, %u", odd, even);	// printed as: "odd, even" (print format not specified).
}


void odd_even_bits(unsigned int num) {
	
	unsigned int even=0, odd=0, mask;
	
	// sizeof(num)*8 - 1 = 31 : uint.
	for (int i = 31; i>=0; i--) {
		mask = 1 << i;
		
		if (i%2) { // if odd
			odd <<= 1;	// ready a new slot
			//odd |= ((num & mask) >> i);
			odd += ((num & mask) != 0);
		} else { // even
			even <<= 1;
			//even |= ((num & mask) >> i);
			even += ((num & mask) != 0);
		}
	}
	
	printf("%u, %u", odd, even);
}