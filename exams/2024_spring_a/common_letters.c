

unsigned int common_letters(const char* s1, const char* s2) {
	
	unsigned int count = 0;
	char table[26] = {0};	// [a ; z] indexed with [0 ; 25]
	unsigned int difference=0;
	
	for (; *s1; s1++) {
		// it is mentioned that both strings will σnly contain uppercase/lowercase letters 
		difference = (*s1 > 'Z') ? 'a'-'A' : 0;
		table[*s1 -'A' -difference]++;	// count char.
	}
	
	for (; *s2; s2++) {
		difference = (*s2 > 'Z') ? 'a'-'A' : 0;
		unsigned int index = *s2 - 'A' - difference;
		if (table[index] > 0) {
			table[index]--;
			count++;
		} 
	}
	
	return count;
}



unsigned int common_letters(const char* s1, const char* s2) {
	
	unsigned int count = 0;
	int table[26] = {0};
	unsigned int diff = 0;
	
	for (; *s1; s1++) {
		diff = (*s1 >= 'a') ? 'a' : 'A';
		table[*s1 - diff]++;
	}
	
	for (; *s2; s2++) {
		diff = (*s2 >= 'a') ? 'a' : 'A';
		unsigned int index = *s2 - diff;
		if (table[index] > 0) {
			table[index]--;
			count++;
		}
	}
	
	return count;
}



unsigned int common_letters(const char* s1, const char* s2) {
	
	unsigned int count = 0;
	int table[26] = {0};
	unsigned int diff = 0;
	
	
	for (unsigned int index; *s1; s1++) {
		index = (*s1 >= 'a') ? (*s1-'a') : (*s1-'A');
		table[index]++;
	}
	
	for (unsigned int index; *s2; s2++) {
		index = (*s2 >= 'a') ? (*s2-'a') : (*s2-'A');
		if (table[index] > 0) {
			table[index]--;
			count++;
		}
	}
	
	return count;
}