#include <stdbool.h>

bool isdigit(const char* str) {
	if (!str) return false;
	
	for (; *str; str++) {	// *str != '\0'
		if (*str < '0' || *str > '9') return false;
	}
	
	return true;
}