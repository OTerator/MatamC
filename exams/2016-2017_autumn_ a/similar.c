
bool similar(const char* s1, const char* s2, bool (*simc)(char a, char b)) {
	
	for (; *s1 || *s2; s1++, s2++) {
		
		// we have to check both because "exam please" != "exampl ease" != "example ace" (ace it!)
		for (; *s1 == ' ' || *s1 == '\t'; s1++)
			;
		for (; *s2 == ' ' || *s2 == '\t'; s2++)
			;
		
		if (!(*s1) || !(*s2) || !simc(*s1, *s2)) return false;
	}
	
	return true;
}


bool r_similar (const char* s1, const char* s2, bool (*simc)(char a, char b)) {
	
	if (!*s1 && !*s2) return true;

	if (!(*s1) || !(*s2) || !simc(*s1, *s2)) return false;
	
	if (*s1 == ' ' || *s1 == '\t')
		r_similar(s1+1, s2);
	
	if (*s2 == ' ' || *s2 == '\t')
		r_similar(s1, s2+1);
		

	return r_similar(s1+1, s2+1, simc);
}