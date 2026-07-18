

unsigned int switch_pairs(unsigned int n) {
	
	unsigned int even_pairs = 0xCCCCCCCC;
	unsigned int odd_pairs = 0x33333333;
	
	even_pairs &= n;
	odd_pairs &= n;
	
	even_pairs >>= 2;
	odd_pairs <<= 2;
	
	return (even_pairs | odd_pairs);
}


unsigned int switch_ends(unsigned int num, unsigned int m) {
	
	// mask setup
	unsigned int start = (1 << m) -1;
	unsigned int end = ~((1 << (32-m))-1);
	unsigned int clean = ~(start | end);
	
	start &= num;
	end &= num;
	
	// apply
	num &= clean;
	num |= (start << (32-m));
	num |= (end >> (32-m));
	
	return num;
}


void print_octal(unsigned int n) {
	for (int i=30; i>=0; i-=3) {
		unsigned int m = (n >> i) & 0x7;
		printf("%u", m);
	}
	printf("\n");
}