
#include <stdbool.h>

// Good
bool startswith(const char* s1, const char* s2, unsigned int pos) {
	
	const char* p1 = s1;
	unsigned int len1 = 0;
	for (; *p1; p1++, len1++)	// *p1 != '\0'
		;
	
	if (pos > len1) return false;	// index out of range.
	
	s1+= pos;
	
	for (; *s2; s1++, s2++) {
		if (!(*s1)) return false;
		if (*s1 != *s2) return false;
	}
	
	return true;
}



//	Bad
bool startswith(const char* s1, const char* s2, unsigned int pos) {
	pos++;
	for (; pos!=0; pos--, s1++) {
		if (!*s1) return false;
	}
	
	for (; *s2; s1++, s2++) {
		if (!(*s1)) return false;
		if (*s1 != *s2) return false;
	}
	
	return true;
}


//	OK
bool startwith(const char* s1, const char* s2, unsigned int pos) {
	
	unsigned int len1 = 0;
	for (; s1[len1]; len1++)
		;
	
	if (len1 < pos) return false;
	
	for (unsigned int i = 0; s2[i]; i++) {
		if (s1[pos+i] == '\0') return false;
		if (s1[pos+i] != s2[i]) return false;
	}
	
	return true;
}


// Best!
bool startswith_optimized(const char* s1, const char* s2, unsigned int pos) {
	
	for (unsigned int i=0; i<pos; i++, s1++) {
		if (!*s1) return false;
	}
	
	for (; *s2; s1++, s2++) {
		if (*s1 != *s2) return false;
	}
	
	return true;
}