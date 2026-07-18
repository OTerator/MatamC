

// isPalindrome
bool creepy(const char* s)
{
const char* t = s+strlen(s)-1;
while(t > s) {
if(*(s++) != *(t--))
return false;
}
return true;
}



unsigned int max_inarr(void* arr[], unsigned int size, bool(*is_larger)(void*, void*)) {
	
	unsigned int max=0; i;
	
	for (i=1; i<size; i++) {
		if (is_larger(arr[max], arr[i])) max = i;		
	}
	
	return max;
}

void swap(void** a, void** b) {
	void* temp = *a;
	*a = *b;
	*b = temp;
}


void sort(void* arr[], unsigned int size, bool(*is_larger)(void*, void*)) {
	
	if (size == 1) return;
	
	unsigned int j = 0;
	
	for (unsigned int i = 0; i<size; i++) {
		j = max_inarr(arr+i, size-i, is_larger);
		if (
	}
}