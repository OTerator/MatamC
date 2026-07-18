
// problematic
unsigned int zero_ends(unsigned int n, unsigned int i, unsigned int j) {
	
	unsigned int mask = (1<<(32-j)) -1;
	mask |= (1<<(i+1))-1;
	mask = ~mask;	// 000...0..111..0...000
	
	return n & mask;	
}