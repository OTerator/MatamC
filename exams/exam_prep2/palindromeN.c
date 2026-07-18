#include <stdbool.h>

//	Helper:
bool isPalindrome(const char* str, unsigned int len) {
	if (!str || len < 1) return false;
	
	for (unsigned int i=0; i<len/2; i++) {
		if (str[i] != str[len-1-i]) return false;
	}
	
	return true;
}


bool palindromeN(const char* str, unsigned int n) {
	if (!str || n < 1) return false;

	// no check if n < strlen.
	for (; *(str+n-1); str++) {
		if (isPalindrome(str, n)) return true;
	}
	
	return false;
}


bool palindromeN(const char* str, unsigned int n) {
	if (!str || n<1) return false;
	
	const char* end = str;
	for (unsigned int i=0; i<n; i++, end++) {
		if (*end == '\0') return false;	// n must be shorter than or equal to the str len.
	}
	
	for (; *(str+n-1); str++) {
		if (isPalindrome(str, n)) return true;
	}
	
	return false;
}