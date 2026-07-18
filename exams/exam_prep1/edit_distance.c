
unsigned int edit_distance(unsigned int a, unsigned int b) {
	
	unsigned int difference = a^b;
	
	unsigned int count = 0;
	while (difference != 0) {
		//if (difference & 1) count++;
		count += difference & 1;
		difference >>= 1;
	}
	
	return count;
}